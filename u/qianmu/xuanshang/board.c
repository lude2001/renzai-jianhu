#define XUANSHANGD "/u/qianmu/xuanshang/xuanshangd"

void init()
{
	add_action("do_xuanshang", "xuanshang");
	add_action("do_look_board", "look_board");
	add_action("do_jiebang", "jiebang");
}

int do_xuanshang(string arg)
{
	object who = this_player();
	object target;
	int amount;

	if (arg == "" || !arg)
	{
		tell_object(who, INPUTTXT("你要悬赏谁？(输入ID)", "xuanshang $txt#") + "\n");
		return 1;
	}

	if (sscanf(arg, "%s %d", arg, amount) != 2)
	{
		target = find_player(arg);
		if (!target || !userp(target))
		{
			tell_object(who, "这个人目前已暂时离开江湖。\n");
			return 1;
		}
		else
		{
			tell_object(who, INPUTTXT("你要悬赏" + target->query("name") + "多少金子?", "xuanshang " + arg + " $txt#") + "\n");
			return 1;
		}
	}
	else
	{
		if (amount <= 0)
		{
			tell_object(who, "请输入大于零的数。\n");
			return 1;
		}

		target = find_player(arg);
		if (!target || !userp(target))
		{
			tell_object(who, "这个人目前已暂时离开江湖。\n");
			return 1;
		}
		else
		{

			if (XUANSHANGD->add_xuanshang(target->query("id"), amount))
			{
				tell_object(who, "你花费" + amount + "金子悬赏" + target->query("name") + "\n");
				return 1;
			}
			else
			{
				tell_object(who, "悬赏出错，请联系管理员处理。\n");
				return 1;
			}

			return 1;
		}
	}

	return 1;
}

int do_look_board(string arg)
{
	object who = this_player();
	string temp;
	string str = "";
	mapping xuanshang;

	if (!sizeof(xuanshang = XUANSHANGD->get_xuanshang()))
	{
		tell_object(who, "目前江湖中没有被悬赏的人。\n");
		return 1;
	}

	foreach (temp in keys(xuanshang))
	{
		str += xuanshang[temp][0] + "(" + xuanshang[temp][1] + ")" + ":jiebang " + temp + ZJSEP;
	}

	if (str == "")
		tell_object(who, ZJOBLONG + "目前江湖中没有被悬赏的人。\n");
	else
		tell_object(who, ZJOBLONG + "目前江湖中被悬赏的人有：\n" + ZJOBACTS2 + str + "\n");

	return 1;
}

int do_jiebang(string arg)
{
	object who = this_player();

	string id;
	string sign;
	object order;
	mapping xuanshang;

	xuanshang = XUANSHANGD->get_xuanshang();
	
	if (sscanf(arg, "%s %s", id, sign) != 2)
	{
		if (undefinedp(xuanshang[arg]))
		{
			tell_object("目前没有这个悬赏令啊。\n");
			return 1;
		}

		tell_object(who, ZJOBLONG + "你要揭下" + xuanshang[arg][0] + "的悬赏令吗？\n" + ZJOBACTS2 + "确定:jiebang " + arg + " y\n");
		return 1;
	}
	else
	{
		if (sign != "y")
		{
			tell_object(who, "输入参数错误，请重新输入。\n");
			return 1;
		}

		if (undefinedp(xuanshang[id]))
		{
			tell_object("目前没有这个悬赏令啊。\n");
			return 1;
		}

		if (!objectp(order = new(__DIR__"xuanshang_order")))
		{
			tell_object(who, "出错，请联系管理员处理。\n");
			return 1;
		}

		order->set("xuanshang", id);
		order->set_name(xuanshang[id][0] + "悬赏令", ({ id + "-order" }));
		order->move(who);
		tell_object(who, "你揭下了" + xuanshang[id][0] + "的悬赏令。\n");

		return 1;
	}
}