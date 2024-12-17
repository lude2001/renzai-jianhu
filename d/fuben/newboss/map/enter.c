// Room: /city/beidajie2.c

inherit ROOM;

void create()
{
	set("short", "�����������");
	set("long", @LONG
���ǵ����������ڡ�
LONG );
	set("outdoors", "city");
	set("exits", ([



		"south":"/d/guanwai/beicheng",
	]));
	set("action_list", ([
		"����" : "choose_target",
		"����" : "enter_fuben",
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
	//({��, ��, ʱ, ��, ��, ��, ����, ��, ʱ��, ʱ��, ����ʱ})

	//ÿ������6�㵽����11�㿪������,����������,������ȡʮ����
	if (timeDispose[1]<50||(timeDispose[2] < 17 || timeDispose[2] > 23))
	return notify_fail("���ڲ��Ǳ���ʱ�䣡\n");

	if (me->query("combat_exp") < 1000000)
	return notify_fail("���ղ������Ǳ�ȥ���������˰ɣ����ڵ��㣬��û���ʸ�\n");

	if (time() < me->query_temp("daojian_fuben/time") && me->query_temp("daojian_fuben/time"))
	{
		return notify_fail("���Ѿ�ѡ��" + me->query_temp("daojian_fuben/name") +"������!\n");
	}

	// if (!arg)
	// {
	// 	// string msg = "��ѡ������һ����ѡ��˭����˭������ȫ��������һ����\n";
	// 	// msg = ZJOBLONG + msg;

	// 	// msg += ZJOBACTS2;
	// 	// msg += "��һ��:choose_target hu"ZJSEP;
	// 	// msg += "���˷�:choose_target miao";

	// 	// msg += "\n";


	// 	// tell_object(me, msg);
	// 	tell_object("��ʼ���ѡ��");
	// 	return 1;
	// }

	// if (arg)
	// {
	// 	if (arg != "miao" && arg != "hu")
	// 	return 1;
	tell_object(me,"��ʼ���ѡ������!\n");

		if (random(2))
		{
			me->set_temp("daojian_fuben/state","hu");
			me->set_temp("daojian_fuben/name","��һ��");
			tell_object(me,"��ѡ���˺�һ�������ݡ�\n");
		}
		else
		{
			me->set_temp("daojian_fuben/state","miao");
			me->set_temp("daojian_fuben/name","���˷�");
			tell_object(me,"��ѡ�������˷�����ݡ�\n");
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
		return notify_fail("�������滹û�п��������ĵȴ�!\n");
	}

	if (me->query_temp("daojian_fuben/time") < time())
	{
		return notify_fail("�㻹û��ѡ������,��ѡ�������ٽ��뵶������ɣ�\n");
	}
    
    //ÿ�ν�������������Ļָ�������ֹ��bug��
    if (me->query_temp("huifu"))
        me->delete_temp("huifu");
        
	me->move(__DIR__"guixu");
	tell_object("�������˵�������,��ѡ��������Լ�����������" +me->query_temp("daojian_fuben/name") +  ",�쿴��ս���ɣ�\n");

	return 1;
}
