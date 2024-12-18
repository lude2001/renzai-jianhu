inherit NPC;

string ask_sell_gem();
string ask_buy_gem();

void create()
{
	set_name("宝石商人", ({ "baoshi shangren" }));
	set("long", "宝石商人。\n");
	set("gender", "男性");
	set("combat_exp", 100000);

	set("inquiry", ([
		"出售宝石" : (: ask_sell_gem :),
		"购买宝石" : (: ask_buy_gem :),
		]));

	setup();
}

string ask_sell_gem()
{
	object who = this_player();

	who->force_me("sell_gem");

	return "";
}

string ask_buy_gem()
{
	object who = this_player();

	who->force_me("buy_gem");

	return "";
}

void init()
{
	add_action("do_buy_gem", "buy_gem");
	add_action("do_sell_gem", "sell_gem");
}

int do_sell_gem(string arg)
{
	object who = this_player();
	object * gem_list;
	object temp;
	string str;
	string gem_object;
	object gem;
	int amount;
	string sign;

	if (!arg || arg == "")
	{
		gem_list = filter_array(all_inventory(who), (: ($1)->query("can_be_inlay") :));

		if (!sizeof(gem_list))
		{
			tell_object(who, "你的身上没有宝石啊。\n");
			return 1;
		}
		else
		{
			str = ZJOBLONG + "你想卖出什么宝石？\n" + ZJOBACTS2;
			foreach(temp in gem_list)
			{
				str += temp->query("name") + ":sell_gem " + file_name(temp) + ZJSEP;
			}

			tell_object(who, str + "\n");
			return 1;
		}
	}

	if (sscanf(arg, "%s %d %s", gem_object, amount, sign) == 3)
	{
		if ("y" != sign)
		{
			tell_object(who, "参数输入错误，请重新输入。\n");
			return 1;
		}

		if (!objectp(gem = find_object(gem_object)) && environment(gem) == who)
		{
			tell_object(who, "结算步骤出错，请联系管理员处理。\n");
			return 1;
		}

		if (!gem->query("can_be_inlay"))
		{
			tell_object(who, "这东西不是宝石啊。\n");
			return 1;
		}

		if (amount > gem->query_amount())
		{
			tell_object(who, "你没有那么多的" + gem->query("name") + "啊。\n");
			return 1;
		}

		tell_object(who, "你出售了" + amount + "个" + gem->query("name") + "\n");
		log_file("gem/sell", ctime(time()) + who->query("name") + "(" + who->query("id") + ")出售了" + amount + "个" + gem->query("name") + "。\n");
		gem->add_amount(-amount);
		who->add("gem_duihuan", amount);

		return 1;
	}

	if (sscanf(arg, "%s %s", gem_object, sign) == 2 && "piliang" == sign)
	{
		if (!objectp(gem = find_object(gem_object)) && environment(gem) == who)
		{
			tell_object(who, "批量出售出错，请联系管理员处理。\n");
			return 1;
		}

		tell_object(who, INPUTTXT("你要出售多少个" + gem->query("name") + "？", "sell_gem " + gem_object + " $txt#") + "\n");
		return 1;
	}

	if (sscanf(arg, "%s %d", gem_object, amount) == 2)
	{
		if (!objectp(gem = find_object(gem_object)) && environment(gem) == who)
		{
			tell_object(who, "确认步骤出错，请联系管理员处理。\n");
			return 1;
		}

		if (amount < 1)
		{
			tell_object(who, "请输入一个大于一的数。\n");
			return 1;
		}

		tell_object(who, ZJOBLONG + "你确定要出售" + amount + "个" + gem->query("name") + "吗？\n" + ZJOBACTS2 + "确认:sell_gem " + gem_object + " " + amount + " y\n");
		return 1;
	}

	if (sscanf(arg, "%s", gem_object) == 1)
	{
		if (!objectp(gem = find_object(gem_object)) && environment(gem) == who)
		{
			tell_object(who, "出错，请联系管理员处理。\n");
			return 1;
		}

		tell_object(who, ZJOBLONG + "你现在拥有" + gem->query_amount() + "个" + gem->query("name") + "。\n" + ZJOBACTS2 + 
						"出售一个:sell_gem " + gem_object + " 1" + ZJSEP + "批量出售:sell_gem " + gem_object + " piliang\n");
		return 1;
	}

	return 1;
}

int do_buy_gem(string arg)
{
	object who = this_player();
	string * gem_list;
	string temp;
	string gem_file;
	string sign;
	object gem;
	string str;

	if (!arg || arg == "")
	{
		str = ZJOBLONG + "你现在有" + who->query("gem_duihuan") + "宝石兑换卷，你要兑换什么宝石？\n" + ZJOBACTS2;

		gem_list = list_dirs("/clone/gem/*.c");
		foreach(temp in gem_list)
		{
			str += load_object("/clone/gem/" + temp)->query("name") + ":buy_gem /clone/gem/" + temp + ZJSEP;
		}

		tell_object(who, str + "\n");
		return 1;
	}

	if (sscanf(arg, "%s %s", gem_file, sign) != 2)
	{
		tell_object(who, ZJOBLONG + "你确定要兑换" + load_object(arg)->query("name") + "吗？\n" + ZJOBACTS2 + "确定:buy_gem " + arg + " y\n");
		return 1;
	}
	else
	{
		if (sign != "y")
		{
			tell_object(who, "输入参数错误，请重试。\n");
			return 1;
		}

		if (who->query("gem_duihuan") < 5)
		{
			tell_object(who, "你的宝石兑换卷不足五张。\n");
			return 1;
		}

		if (!objectp(gem = new(gem_file)))
		{
			tell_object(who, "复制宝石出错，请联系管理员处理。\n");
			return 1;
		}

		if (!gem->query("can_be_inlay"))
		{
			tell_object(who, "这东西不是宝石啊。\n");
			destruct(gem);
			return 1;
		}

		tell_object(who, "你用五个宝石兑换卷和宝石商人兑换了" + gem->query("name") + "。\n");
		log_file("gem/buy", ctime(time()) + who->query("name") + "(" + who->query("id") + ")兑换了" + gem->query("name") + "。\n");
		who->add("gem_duihuan", -5);
		gem->move(who);
	}

	return 1;
}