
inherit ROOM;

void create()
{
	set("short", "秘技阁");
	set("long", "这里是帮内众兄弟研究秘技的地方。");
	set("exits", ([
		"north" : __DIR__"liangong",
	]));
	set("bangpai_room","1");
	set("no_fight","1");
	set("action_list", ([
		HIG"研究秘技"NOR:"miji_uplv",
	]));
	setup();
}

void init()
{
	add_action("do_miji_uplv", "miji_uplv");
}

int do_miji_uplv(string arg)
{
	object me = this_player();
	int money,gongxian,potential;
	string short;

	short = me->query("banghui/name");

	if (!arg)
	{
		string msg = ZJOBLONG + "你要升级那一个秘技？\n";
		msg += ZJOBACTS2;
		msg += "五禽戏:miji_uplv wu"ZJSEP;
		msg += "八段锦:miji_uplv ba"ZJSEP;
		msg += "六字诀:miji_uplv liu\n";
		write(msg);
		return 1;
	}

	if (arg != "wu" && arg != "ba" && arg != "liu")
	{
		return notify_fail("你只能升级指定秘技。\n");
	}

    if (me->query("miji/" + arg) < 20)
    {
	money = (me->query("miji/" + arg) * me->query("miji/" + arg) + 500) * 10000;
	gongxian = money / 10000;
    }
    else
    {
        if (me->query("miji/" + arg) >= 500)
              return notify_fail("等级满了。\n");
              
        gongxian = me->query("miji/" + arg) * 2;
        money =  (me->query("miji/" + arg) + 100) * 10000;
        potential =  me->query("miji/" + arg) * 300;
        
        if (me->query("potential") - me->query("learned_points") < potential)
        return notify_fail("潜能不足。\n");
        
    }

	if (!BANGHUI_D->query_banghui(short + "/mijige"))
	return notify_fail("你的帮派秘籍阁尚未建设完成。\n");

	if (me->query("balance") < money)
	return notify_fail("你的钱庄存款不够。\n");

	if (BANGHUI_D->query_banghui (short+"/gongxian/"+me->query("id")) < gongxian)
	return notify_fail("你的帮派贡献不够。\n");
	
	me->add("balance",-money);
	BANGHUI_D->set_banghui(short+"/gongxian/"+me->query("id"), BANGHUI_D->query_banghui (short+"/gongxian/"+me->query("id"))-gongxian);
	me->add("miji/" + arg,1);
	
	if (!undefinedp(potential)||potential)
	me->add("potential",-potential);
	
	CHAR_D->setup_char(me);

	tell_object(me,"升级成功！\n");

	return 1;
}
