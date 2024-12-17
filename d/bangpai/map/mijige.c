
inherit ROOM;

void create()
{
	set("short", "�ؼ���");
	set("long", "�����ǰ������ֵ��о��ؼ��ĵط���");
	set("exits", ([
		"north" : __DIR__"liangong",
	]));
	set("bangpai_room","1");
	set("no_fight","1");
	set("action_list", ([
		HIG"�о��ؼ�"NOR:"miji_uplv",
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
		string msg = ZJOBLONG + "��Ҫ������һ���ؼ���\n";
		msg += ZJOBACTS2;
		msg += "����Ϸ:miji_uplv wu"ZJSEP;
		msg += "�˶ν�:miji_uplv ba"ZJSEP;
		msg += "���־�:miji_uplv liu\n";
		write(msg);
		return 1;
	}

	if (arg != "wu" && arg != "ba" && arg != "liu")
	{
		return notify_fail("��ֻ������ָ���ؼ���\n");
	}

    if (me->query("miji/" + arg) < 20)
    {
	money = (me->query("miji/" + arg) * me->query("miji/" + arg) + 500) * 10000;
	gongxian = money / 10000;
    }
    else
    {
        if (me->query("miji/" + arg) >= 500)
              return notify_fail("�ȼ����ˡ�\n");
              
        gongxian = me->query("miji/" + arg) * 2;
        money =  (me->query("miji/" + arg) + 100) * 10000;
        potential =  me->query("miji/" + arg) * 300;
        
        if (me->query("potential") - me->query("learned_points") < potential)
        return notify_fail("Ǳ�ܲ��㡣\n");
        
    }

	if (!BANGHUI_D->query_banghui(short + "/mijige"))
	return notify_fail("��İ����ؼ�����δ������ɡ�\n");

	if (me->query("balance") < money)
	return notify_fail("���Ǯׯ������\n");

	if (BANGHUI_D->query_banghui (short+"/gongxian/"+me->query("id")) < gongxian)
	return notify_fail("��İ��ɹ��ײ�����\n");
	
	me->add("balance",-money);
	BANGHUI_D->set_banghui(short+"/gongxian/"+me->query("id"), BANGHUI_D->query_banghui (short+"/gongxian/"+me->query("id"))-gongxian);
	me->add("miji/" + arg,1);
	
	if (!undefinedp(potential)||potential)
	me->add("potential",-potential);
	
	CHAR_D->setup_char(me);

	tell_object(me,"�����ɹ���\n");

	return 1;
}
