inherit NPC;
inherit F_SAVE;

string ask_buchang();

void create()
{
    set_name("����ʹ��", ({"qian"}));
    set("long", "Сǧ��ô�ɰ���������ô���Ķ�Сǧ���֡�\n");
    set("gender", "Ů��");
    set("age",17);
    set("combat_exp", 1);
    set("create_time", (time()/86400 + 1) * 86400);
    
    set("inquiry", ([
            " ��2000�������" : (: ask_buchang :),
        ]));
    
    setup();
}

string query_save_file() { return DATA_DIR + "npc/qian"; }

string ask_buchang()
{
	object gift, who = this_player();
	string str;
	
// 	if (who->query("birthday") > query("create_time"))
// 	{
// 		return ("ֻ����" + CHINESE_D->chinese_date(query("create_time"), 1) + "֮ǰ�����Ľ�ɫ������ȡ��\n");
// 	}

	
	if (who->query("buchang_lingqu") != 4)
	{
		if ((time() - who->query("birthday")) / 360 < 2)
		{
			return "��ע��δ����Сʱ���޷���ȡ��";
		}
		
		if (query(who->query("id")))
		{
			return "���Ѿ���ȡ��2000������ˡ�\n";
		}
		
		str = "";
		who->set("buchang_lingqu", 4);
	    if (objectp(gift = new_bind("/clone/gift/putao1")))
	    {
		    gift->set_amount(20);
		    str += "��ϲ��������20��" + gift->short();
			log_file("buchang_shilian", ctime(time()) + who->name() + who->query("id") + "��ȡ���������ѡ�\n");
			gift->move(who);
		}
		
	   if (objectp(gift = new_bind("/clone/gift/dan_chongmai4")))
	    {
		    gift->set_amount(100);
		    str += "��ϲ��������100��" + gift->short();
			log_file("buchang_shilian", ctime(time()) + who->name() + who->query("id") + "��ȡ���������ѡ�\n");
			gift->move(who);
		}
		
// 		if (objectp(gift = new_bind("/clone/vip/kuilei")))
// 		{
// 			gift->set_amount(10);
// 			gift->move(who);
// 			str += "������ʮ��������ܡ�";
// 		}
// 		if (objectp(gift = new_bind("/clone/gift/tianxiang1")))
// 		{
// 			log_file("buchang_shilian", ctime(time()) + who->name() + "��ȡ��������¶��\n");
// 			gift->set_amount(5);
// 			gift->move(who);
// 			str += "���������������¶";
// 		}

		set(who->query("id"), 2);
	}
	else
		return "���Ѿ���ȡ��2000ǧ����������ˣ��޷��ٴ���ȡ��Ŷ��";

	return str;
}


void die()
{
	object ob, me, who;
	
	me = this_object();
	who = me->query_last_damage_from();
	ob = new(base_name(me));
	ob->set("create_time", query("create_time"));
	ob->move(environment(me));
	tell_object(who, ZJOBLONG + "Сǧ���������ħ������ܵ�����ģ�����ɱ�����ģ�\n");
	log_file("kill_qian", ctime(time()) + "   " + who->name() + "\n");
	
	::die();
}

void init()
{
    add_action("disable", ({ "kill", "hit", "fuhuo", "touxi", "fight", "steal"}));
}

int disable(string arg)
{
    object who = this_player();
    
    if (arg != "qian")
        return 0;
    
    tell_object(who, "Сǧһ�������㣬�㵹�ڵ��϶������á�\n");
    who->start_busy(180);

    return 1;
}

int accept_ansuan(object who)
{
    tell_object(who, "���밵��Сǧ����\nСǧ���ߣ����밵���ң��Թ���ԭ�ط�վ�ɣ�\n");
    who->start_busy(300);
    return 0;
}

void fight_ob(object ob)
{
	::fight_ob(ob);
    tell_object(ob, "Сǧһ�������㣬�㵹�ڵ��϶������á�\n");
    ob->start_busy(180);
    
}

int accept_fight(object who)
{
	command("say û��Ȥ��");
	return 0;
}

void receive_damage(string type, int n)
{
	return;
}

void receive_wound(string type, int n)
{
	return;
}