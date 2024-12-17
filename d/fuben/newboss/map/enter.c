// Room: /city/beidajie2.c

inherit ROOM;

void create()
{
	set("short", "刀剑归墟入口");
	set("long", @LONG
这是刀剑归墟的入口。
LONG );
	set("outdoors", "city");
	set("exits", ([



		"south":"/d/guanwai/beicheng",
	]));
	set("action_list", ([
		"报名" : "choose_target",
		"进入" : "enter_fuben",
	]));
	setup();
}

void init()
{
	add_action("do_choose_target", "choose_target");
	add_action("do_enter_fuben", "enter_fuben");
}

int do_choose_target(string arg)
{
	object me = this_player();
	mixed* timeDispose;

	timeDispose = localtime(time() - 360);
	//({秒, 分, 时, 日, 月, 年, 星期, 天, 时差, 时区, 夏令时})

	//每天下午6点到晚上11点开启副本,并且是整点,报名提取十分钟
	if (timeDispose[1]<50||(timeDispose[2] < 17 || timeDispose[2] > 23))
	return notify_fail("现在不是报名时间！\n");

	if (me->query("combat_exp") < 1000000)
	return notify_fail("武艺不精还是别去里面送死了吧，现在的你，还没有资格！\n");

	if (time() < me->query_temp("daojian_fuben/time") && me->query_temp("daojian_fuben/time"))
	{
		return notify_fail("你已经选择" + me->query_temp("daojian_fuben/name") +"阵容了!\n");
	}

	// if (!arg)
	// {
	// 	// string msg = "你选择护卫那一方？选择谁则护卫谁，并尽全力击败另一方！\n";
	// 	// msg = ZJOBLONG + msg;

	// 	// msg += ZJOBACTS2;
	// 	// msg += "胡一刀:choose_target hu"ZJSEP;
	// 	// msg += "苗人凤:choose_target miao";

	// 	// msg += "\n";


	// 	// tell_object(me, msg);
	// 	tell_object("开始随机选择");
	// 	return 1;
	// }

	// if (arg)
	// {
	// 	if (arg != "miao" && arg != "hu")
	// 	return 1;
	tell_object(me,"开始随机选择阵容!\n");

		if (random(2))
		{
			me->set_temp("daojian_fuben/state","hu");
			me->set_temp("daojian_fuben/name","胡一刀");
			tell_object(me,"你选择了胡一刀的阵容。\n");
		}
		else
		{
			me->set_temp("daojian_fuben/state","miao");
			me->set_temp("daojian_fuben/name","苗人凤");
			tell_object(me,"你选择了苗人凤的阵容。\n");
		}

		me->set_temp("daojian_fuben/time",time() + 1800);
		return 1;

	// }
}

int do_enter_fuben()
{
	object me = this_player();
	int state = "/adm/daemons/bossd"->query_start_blade_sword_fuben();
	string targetName;

	if (!state)
	{
		return notify_fail("刀剑归墟还没有开启请耐心等待!\n");
	}

	if (me->query_temp("daojian_fuben/time") < time())
	{
		return notify_fail("你还没有选择阵容,先选择阵容再进入刀剑归墟吧！\n");
	}
    
    //每次进入必须清空奶妈的恢复量，防止卡bug。
    if (me->query_temp("huifu"))
        me->delete_temp("huifu");
        
	me->move(__DIR__"guixu");
	tell_object("你来到了刀剑归墟,你选择的阵容以及护卫对象是" +me->query_temp("daojian_fuben/name") +  ",快看看战况吧！\n");

	return 1;
}
