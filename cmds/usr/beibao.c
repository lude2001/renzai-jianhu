// inventory.c

#include <ansi.h>

inherit F_CLEAN_UP;

string* zj_map(string str);
//string json_encode(mixed data);

int main(object me, string arg)
{
	int i, j, all, page;
	object *inv, bao, ob;
	mapping count;
	mapping equiped;
	mapping unit;
	mapping ids;
	mapping itype;
	string *text, pops, short_name;

	string str = "", sss;
	string *dk = ({});

	string title;

	mapping data = ([]);


	if (!arg)
	{
		page = 1;
	}
	else if (sscanf(arg, "%d %s", page, arg) != 2)
	{
		page = 1;
	}

	if (wizardp(me) && arg)
	{
		ob = find_player(arg);
		if (!ob)
			ob = find_living(arg);
		if (!ob)
			ob = present(arg, environment(me));
		if (!ob)
			return notify_fail("没有这个玩家。\n");
	}

	if (!ob)
		ob = me;

	inv = all_inventory(ob);

	if (!sizeof(inv))
	{
		write(ZJOBLONG + ((ob == me) ? "你共有" HIY + ob->query("yuanbao") + "元宝" NOR "。目前你身上没有任何东西。\n" : ob->query("yuanbao") + "身上没有携带任何东西。\n"));
		return 1;
	}
	for (i = 0; i < sizeof(inv); i++)
	{
		short_name = inv[i]->query("name");

		if (inv[i]->query_amount())
		short_name = inv[i]->query_amount() + "--" + inv[i]->query("base_unit") + "--"+ short_name;
		else
		short_name =  "1--" + inv[i]->query("unit") + "--" + short_name;

		sss = short_name;
		if (inv[i]->query("equipped"))
			sss = HIG "■" NOR + sss;
		else
			sss = " " + sss;

		dk += ({sss + ":look " + file_name(inv[i])});
	}
	text = sort_array(dk, 1);

	title = sprintf("%s共有" HIY "%d元宝。" NOR + ZJBR "身上带著下列这些东西(%d件，负重 %d%%)：",
					(ob == me) ? "你" : ob->name(), ob->query("yuanbao"), sizeof(text),
					(int)ob->query_encumbrance() * 100 / (int)ob->query_max_encumbrance());

	all = sizeof(text) / 40;
	if (sizeof(text) % 40)
		all += 1;
	if (page < 1)
		page = 1;
	if (page > all)
		page = all;
	j = (page - 1) * 40;
	i = page * 40;
	if (i >= sizeof(text))
		i = sizeof(text);
	i--;
	if (all > 1)
		str += "上一页:beibao " + (page - 1) + " " + ob->query("id") + ZJSEP "下一页:beibao " + (page + 1) + " " + ob->query("id") + ZJSEP;
	str += implode(text[j..i], ZJSEP);
	
	data["title"] = title;
	data["page"] = page;
	data["userid"] = ob->query("id");

	data["data"] = zj_map(str);

	str  = ESA + "501" + json_encode(data);
	write(str + "\n");
	return 1;
}

string* zj_map(string str)
{
	string *singleData, *allData = ({ });

	foreach (string arg in explode(str,ZJSEP))
	{

		singleData = explode(arg, ":");

		if (strsrch(singleData[0], "--") == -1)
		{
			allData += ({ ([ "name" : singleData[0],"cmd" : singleData[1] ]) });
		}
		else
		{
			string *singleDataTwo;

			singleDataTwo = explode(singleData[0],"--");
			allData += ({ ([ "number" : singleDataTwo[0],"unit" : singleDataTwo[1],"name" : singleDataTwo[2],"cmd" : singleData[1] ]) });
		}
	}

	return allData;
}


