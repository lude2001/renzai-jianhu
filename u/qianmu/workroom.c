inherit ROOM;

void create()
{
	set("short", "工作室");
	set("long", "工作室\n");

	set("action_list", ([
		"测试" : "test",
		]));

	set("item_desc", ([
		"公告栏" : "这是悬赏公告栏，你可以在这里查看悬赏信息。\n"
					"可以花金子悬赏玩家，包括自己。\n" 
					"只有在线的玩家才可以被悬赏。\n" + 
					ZJOBACTS2 + "悬赏信息:look_board" + ZJSEP + "悬赏玩家:xuanshang\n",
		]));

	set("objects", ([
		__DIR__"/xuanshang/board" : 1,
		]));
	
	setup();
}

void init()
{
	add_action("do_test", "test");
	add_action("do_dest_item", "dest_item");
	add_action("do_xuanshang", "xuanshang");
	add_action("do_look_board", "look_board");
	add_action("do_jiebang", "jiebang");
}

#define XUANSHANGD "/adm/daemons/xuanshangd"
#define ORDER "/clone/xuanshang/xuanshang_order"

// void init()
// {
// 	add_action("do_xuanshang", "xuanshang");
// 	add_action("do_look_board", "look_board");
// 	add_action("do_jiebang", "jiebang");
// }

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
			tell_object(who, "这个人目前不在江湖之中。\n");
			return 1;
		}
		else
		{
			tell_object(who, INPUTTXT("你目前有" + (who->query("balance") / 10000) + "两黄金存款，你要悬赏" + target->query("name") + "多少金子?", "xuanshang " + arg + " $txt#") + "\n");
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

		if (who->query("balance") < amount * 10000)
		{
			tell_object(who, "你的存款不足" + amount + "两黄金。\n");
			return 1;
		}

		target = find_player(arg);
		if (!target || !userp(target))
		{
			tell_object(who, "这个人目前不在江湖之中。\n");
			return 1;
		}
		else
		{
			who->add("balance", -amount * 10000);
			if (XUANSHANGD->add_xuanshang(target->query("id"), amount))
			{
				log_file("xuanshang/pay", ctime(time()) + who->query("name") + "(" + who->query("id") + ")花费" + amount + "金子悬赏" + target->query("name") + 
					"(" + target->query("id") + ")，目前总计" + XUANSHANGD->get_xuanshang()[target->query("id")][1] + "黄金。\n");
				tell_object(who, "你花费" + amount + "金子悬赏" + target->query("name") + "。\n");
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

		if (present(id + "-order", who))
		{
			tell_object(who, "你的身上已经有这个悬赏令了。\n");
			return 1;
		}

		if (!objectp(order = new(ORDER)))
		{
			tell_object(who, "出错，请联系管理员处理。\n");
			return 1;
		}

		order->set("xuanshang_id", id);
		order->set("xuanshang_name", xuanshang[id][0]);
		order->set_name(xuanshang[id][0] + "悬赏令", ({ id + "-order" }));
		order->move(who);
		tell_object(who, "你揭下了" + xuanshang[id][0] + "的悬赏令。\n");

		return 1;
	}
}

















int do_test(string arg)
{
	object who = this_player();
    object room;

mapping id = ([

"1账号" : "micen",
"2账号" : "dysy2123",
"3账号" : "qlili",
"4账号" : "yeluo1435",
"5账号" : "jijiu3279465885",
"6账号" : "apollo",
"7账号" : "sorryo",
"8账号" : "q929733198",
"9账号" : "qq3522246229",
"10账号" : "whz520",
"11账号" : "array",
"12账号" : "wana",
"13账号" : "a947456225",
"14账号" : "a15112695790",
"15账号" : "tashuone",
"16账号" : "zxc2580",
"17账号" : "wjxzw12345",
"18账号" : "lza0823",
"19账号" : "qwouvst",
"20账号" : "zxc555",
"21账号" : "li812939754",
"22账号" : "pppppppppppp",
"23账号" : "xxxxxx",
"24账号" : "momo5201314",
]);
    string temp;

    foreach(temp in values(id))
    {
        log_file("id_buchang", "\"" + temp + "\",\n");
    }


    
	// who->start_busy((: call_other, __FILE__, "start" :),
	// 				(: call_other, __FILE__, "end" :));
    //room = new("/d/jingjichang/room");
    //who->move(room);
	//"/d/fuben_huanjing/huanjing"->start_fuben(who);
	return 1;
}

int start()
{
	return 1;
}

int end()
{
	write("你停止了。\n");
	return 1;
}

int do_dest_item(string arg)
{
    object * obs;
    object temp;
    
    obs = children(arg);
    foreach(temp in obs)
    {
        log_file("xxxxxxxxx", "你清除了" + sprintf("%O\n",all_inventory(temp)) + "。\n");
        
        //temp->end_fuben_moku();
        //destruct(temp);
    }
}