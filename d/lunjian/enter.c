#include <room.h>
inherit ROOM;
#define OUTROOM "/d/fuben/qianchipu/qianchipu"

#define LUNJIAN_DAY			0
#define LUNJIAN_HOUR		21
#define LUNJIAN_PRE			31
#define LUNJIAN_TURN		7
#define LUNJIAN_USER_MIN	5

string *total = ({});
int turn = 0;
mapping allusers = ([]);
string last_fight_record = "";

private void init_player(object me);
private void message_competition(string msg);
private void auto_check();
private void restore_status(object me);


int check_win(object me);
int check_out(object me);

void create()
{
	set("short", "��ɽ֮��");
	set("long", "�����ǻ�ɽ֮�ۣ�Ҳ������Ⱥ��������������ľ���֮�ء�");
	set("exits", ([



		"south" : OUTROOM,
	]));
	set("no_fight",1);
	set("no_fly",1);
	set("objects",([
	]));
	set("action_list",([
		"��ɽ�۽�":"jjsign",
		"ս����" : "in_the_room",
		"��ʷ��¼" : "in_the_record",
		"�ƺŽ���":"lunjiangift",
		"���ֶһ�":"ljshop",
	]));
	setup();
}

void init()
{
	add_action("ljshop","ljshop");
	add_action("jjsign","jjsign");
	add_action("lunjiangift","lunjiangift");
	add_action("in_the_room", "in_the_room");
	add_action("in_the_record", "in_the_record");
}

int in_the_record()
{
    string str = "��ʷս����¼����:"ZJBR;

    if (last_fight_record != "")
    {
        str += last_fight_record;
    }
    else
    {
    str += "��";
    }
    
    str = ZJOBLONG + str + "\n";
    
    write(str);
    
    return 1;
    
}
int in_the_room()
{
    object *rooms = children("/d/lunjian/jingji");
    object room, *players;
    string str = "";
    
    foreach(room in rooms)
    {
        players = filter_array(all_inventory(room), (: ($1)->is_player() :));
        if (sizeof(players) == 2)
            str += players[0]->query("name") + " VS " + players[1]->query("name") + ZJBR;
    }
    if (str && str != "")
    {
        write(ZJOBLONG + "�������ڱ��������У�" + ZJBR + str + "\n");
    }
    else
    {
        write(ZJOBLONG + "��������ս����\n");
    }
    return 1;
}

int ljshop(string arg)
{
	string *list,str,file,price;
	int i,yuanbao,value;
	object me,ob;
	int amount;
	mapping goods,times;

	me = this_player();
	goods = ([
		"/clone/vip/dan_chongmai4":3,
		"/clone/vip/putao":10,
		//"/clone/lunjian/wujueling":100,
	]);
	times = ([
		"/clone/lunjian/wujueling":1,
	]);
	list = keys(goods);
	if (! arg)
	{
		str = ZJOBLONG"��Ŀǰ��"+me->query("lunjian/pot")+"�۽����֣���ѡ������һ��ĵ��ߣ�\n"ZJOBACTS2+ZJMENUF(4,4,8,32);
		for(i=0;i<sizeof(list);i++)
		{
			file = list[i];
			if(!goods[file]||file_size(file+".c")<0) continue;
			yuanbao = goods[file];
			price = yuanbao+"����";
			str += sprintf("%s"ZJBR"%s:ljshop look %s"ZJSEP,file->query("name"),price,file);
		}
		tell_object(me,str+"\n");
		return 1;
	}
	else if (sscanf(arg,"look %s",file)==1)
	{
		if(file_size(file+".c")<0||!goods[file])
			return notify_fail(HIM"�һ��б���û��������ߣ���"NOR"\n");

		yuanbao = goods[file];
		price = yuanbao+"����";
		str = ZJOBLONG+"��"+file->query("name")+"�������۸�"+price+NOR+ZJBR"һһһһһһһһһһһһһһһһһһһһһһһ"ZJBR;
		if(times[file])
			str += HIR"����Ʒÿ������޶һ�"+times[file]+"��"NOR ZJBR;
		str += file->long();
		str += ZJOBACTS2+ZJMENUF(4,4,10,28);
		str += "�һ�:ljshop buy "+file+"\n";
		tell_object(me,str+"\n");
		return 1;
	}
	else if (sscanf(arg,"buy %s",file)==1)
	{
		if(file_size(file+".c")<0||!goods[file])
			return notify_fail(HIM"�һ��б���û��������ߣ���"NOR"\n");

		yuanbao = goods[file];

		if(times[file])
		{
			if(me->query("lunjian/duihuan/"+file->query("id")) >= times[file])
				return notify_fail(HIM"����Ʒÿ�����ֻ�ܶһ�"+times[file]+"�Σ���"NOR"\n");
			me->add("lunjian/duihuan/"+file->query("id"),1);
		}
		if(me->query("lunjian/pot") < yuanbao)
			return notify_fail(HIM"��Ķһ����ֲ��㣬��μӲμ��۽���ѣ���"NOR"\n");
		me->add("lunjian/pot",-yuanbao);
		ob = new(file);
		log_file("pay/lunjian", ctime(time()) + "	" + me->query("name") + "�һ���"+ob->short()+"��\n");
		tell_object(me,"��ɹ��һ�����"+ob->short()+"��"NOR"\n");
		ob->move(me);
		return 1;
	}
	else
		return notify_fail(HIM"�����ʲô����"NOR"\n");

	return 1;
}

int valid_leave(object me, string dir)
{
	if(allusers[me->query("id")])
	{
		tell_object(me,"���뿪�˻�ɽ֮�ۣ������һ�ֱ������ڳ��Ļ��㽫ʧȥһ�ν������ᡣ\n");
	}
	return ::valid_leave(me, dir);
}

int lunjiangift()
{
	object me;
	string str;
	
	me = this_player();
	str = FAMILY_D->bouns_lunjian_leader(me);
	tell_object(me,str);
	return 1;
}

int jjsign()
{
	int now = time();
	object me = this_player();

	if(localtime(now)[6]!=LUNJIAN_DAY||localtime(now)[2]!=LUNJIAN_HOUR||localtime(now)[1]>LUNJIAN_PRE)
		return notify_fail(ZJOBLONG"����ʱ�䣺"+LUNJIAN_HOUR+":00-"+LUNJIAN_HOUR+":31��\n");

	if (me->query("combat_exp")<200000)
		return notify_fail("�㾭����ǳ�����ǰѹ������������ɡ�\n");

	if (allusers[me->query("id")])
		return notify_fail("���Ѿ��������ˣ�Ŀǰ����������"+sizeof(allusers)+"��\n");

	allusers[me->query("id")]=1;
	tell_object(me,"�����ɹ������ڴ��Ժ�"+LUNJIAN_HOUR+"��30���Զ����뾺�����С�\n");
	set_heart_beat(1);
	return 1;
}

int sort_total(string user1,string user2)
{
	return (int)allusers[user2]-(int)allusers[user1];
}

private void auto_check()
{
	object tmp1,tmp2,*inv,*rooms,ob;
	string name,msg;
	string *us,room;
	int i;

	rooms = children("/d/lunjian/jingji");
	if(!sizeof(rooms))
	{
	    last_fight_record += "--------��" + (turn + 1) + "��--------"ZJBR;
	    
		total = sort_array(keys(allusers),(: sort_total :));
		us = filter_array(total, (: find_player($1)&&present(find_player($1),$(this_object())) :));
		if(sizeof(us)<1 || turn >= LUNJIAN_TURN)
		{
			if(allusers[total[0]]<2)
			{
				msg = "��˵��ɽ�۽����������ӵ��ӣ�δ�ܾ������������𡿣�";
				message_competition(msg);
			}
			else
			{
				if(ob = find_player(total[0]))
					name = ob->query("name");
				else
					name = TOP_D->get_name(total[0]);
				msg = "��ɽ�۽�Բ��������" + name + "��á�����ͨ���ĳƺţ�";
				FAMILY_D->set_lunjian_leader("����ͨ",total[0]);
				message_competition(msg);

				if(sizeof(total)>1)
				{
					if(ob = find_player(total[1]))
						name = ob->query("name");
					else
						name = TOP_D->get_name(total[1]);
					msg = name + "��á���а���ĳƺţ�";
					FAMILY_D->set_lunjian_leader("��а",total[1]);
					message_competition(msg);
				}

				if(sizeof(total)>2)
				{
					if(ob = find_player(total[2]))
						name = ob->query("name");
					else
						name = TOP_D->get_name(total[2]);
					msg = name + "��á��������ĳƺţ�";
					FAMILY_D->set_lunjian_leader("����",total[2]);
					message_competition(msg);
				}

				if(sizeof(total)>3)
				{
					if(ob = find_player(total[3]))
						name = ob->query("name");
					else
						name = TOP_D->get_name(total[3]);
					msg = name + "��á��ϵۡ��ĳƺţ�";
					FAMILY_D->set_lunjian_leader("�ϵ�",total[3]);
					message_competition(msg);
				}

				if(sizeof(total)>4)
				{
					if(ob = find_player(total[4]))
						name = ob->query("name");
					else
						name = TOP_D->get_name(total[4]);
					msg = name + "��á���ؤ���ĳƺţ�";
					FAMILY_D->set_lunjian_leader("��ؤ",total[4]);
					message_competition(msg);
				}

				if (sizeof(total) > 5)
				{
					for(int s = 5;s < sizeof(total);s++)
					{
						string title_name;

						if (s > 16)
						break;

						title_name = "��" + chinese_number(s-4) + "����";

						
						if(ob = find_player(total[s]))
						name = ob->query("name");
						else
						name = TOP_D->get_name(total[s]);
						msg = name + "��á�" + title_name + "���ĳƺţ�";
						FAMILY_D->set_lunjian_leader(title_name,total[s]);
						message_competition(msg);
					}
				}
				set_heart_beat(0);
				delete("pre_start");
				delete("start");
			}
			allusers = ([]);
			turn = 0;
			return;
		}
		while(sizeof(us)>1)
		{
			tmp1 = find_player(us[0]);
			us -= ({ tmp1->query("id") });
			tmp2 = find_player(us[0]);
			us -= ({ tmp2->query("id") });
			init_player(tmp1);
			init_player(tmp2);
			room = new("/d/lunjian/jingji");
			tmp1->move(room);
			tmp2->move(room);
			tmp1->kill_ob(tmp2);
			tmp2->kill_ob(tmp1);
			room->set("record",tmp1->query("name") + " vs " + tmp2->query("name"));
		}
		if(sizeof(us))
		{
			ob = find_player(us[0]);
			ob->add("lunjian/pot",1);
			allusers[us[0]] += 1;
			tell_object(ob,"���ڱ��־����������ֿգ��Զ���������ȴ���һ��ƥ�䡣\n");
			log_file("lunjian", ctime(time()) + ob->query("name") + "�ֿս�������������1��\n");
		}
		turn++;
		return;
	}
	for (i = 0; i < sizeof(rooms); i++)
	{
	    rooms[i]->add("fight_time",2);//ÿ����������������
		inv = filter_array(all_inventory(rooms[i]),(: playerp($1) :));
		if(!sizeof(inv))
		{
			last_fight_record += rooms[i]->query("record")+ ZJBR"ս����ʱ:"+ rooms[i]->query("fight_time") + "��" + ZJBR;
			destruct(rooms[i]);
		}
		else if(sizeof(inv)==1)
		{
			allusers[inv[0]->query("id")]++;
			inv[0]->add("lunjian/pot",1);
			rooms[i]->set("record",rooms[i]->query("record") + sprintf("(%sʤ��)",inv[0]->query("name")));
			log_file("lunjian", ctime(time()) + inv[0]->query("name") + "ʤ����������������1��\n");
			check_win(inv[0]);
		}
		else if (rooms[i]->query("fight_time") >= 120 && sizeof(inv) == 2) //ս���������ж�ƽ��
		{
		    rooms[i]->set("record",rooms[i]->query("record") + sprintf("(ƽ��)"));
		    			
		    allusers[inv[0]->query("id")]++;
			inv[0]->add("lunjian/pot",1);
			log_file("lunjian", ctime(time()) + inv[0]->query("name") + "ʤ����������������1��\n");
			check_win(inv[0]);
			
			allusers[inv[1]->query("id")]++;
			inv[1]->add("lunjian/pot",1);
			log_file("lunjian", ctime(time()) + inv[1]->query("name") + "ʤ����������������1��\n");
			check_win(inv[1]);
		}
	}
}

private void init_player(object me)
{
	tell_object(me, HIY "�������˻�ɽ�۽��ı��䳡..."NOR"\n");
	me->set_override("unconcious", (: call_other, __FILE__, "check_out" :));
	me->set_override("die", (: call_other, __FILE__, "check_out" :));
	me->set_override("net_dead", (: call_other, __FILE__, "check_out" :));//�����ж�ʧ��
	me->set_override("quit", (: call_other, __FILE__, "check_quit" :));
	me->set_temp("backup/killer", me->query_killer());
	me->set_temp("backup/want", me->query_want());
	me->set_temp("in_pkd", 1);

	me->set("backup/condition", me->query_condition());
	me->clear_condition();
}

private void message_competition(string msg)
{
	CHANNEL_D->do_channel(this_object(), "rumor", msg);
}

private void restore_status(object me)
{
	mapping my;
	mapping cnd;
	string *ks;
	int i;

	me->delete_temp("in_pkd");
	me->delete_override("unconcious");
	me->delete_override("die");
	me->delete_override("quit");
	me->remove_all_enemy(1);
	me->remove_all_killer();
	me->clear_condition();
	me->receive_damage("qi", 0);
	me->apply_killer(me->query_temp("backup/killer"));
	me->apply_want(me->query_temp("backup/want"));

	cnd = me->query("backup/condition");
	me->delete("backup/condition");
	me->delete_temp("block_msg/all");
	if (! mapp(cnd)) return;
	ks = keys(cnd);
	for (i = 0; i < sizeof(ks); i++)
		me->apply_condition(ks[i], cnd[ks[i]]);

	my = me->query_entire_dbase();
	my["jing"]   = my["eff_jing"]   = my["max_jing"];
	my["jingli"] = my["eff_jingli"] = my["max_jingli"];
	my["qi"]     = my["eff_qi"]     = my["max_qi"]+me->query_gain_qi();
	my["neili"]  = my["max_neili"];
}

void heart_beat()
{
	int i,now = time();
	object tmp1,tmp2,room,*inv;
	string msg;

	room = this_object();

	if(!query("pre_start")&&localtime(now)[1]==LUNJIAN_PRE)
	{
		set("pre_start",1);
		last_fight_record = ""; //�����ʷ��¼
		tell_room(this_object(),"1���Ӻ󽫽��뾺������������׼��������\n");
	}
	else if(!query("start")&&localtime(now)[1]==(LUNJIAN_PRE+1))
	{
		set("start",1);
		inv = filter_array(all_inventory(this_object()), (: playerp($1)&&$(allusers)[$1->query("id")] :));
		if(sizeof(inv)<LUNJIAN_USER_MIN)
		{
			msg = "��˵���λ�ɽ�۽���������̫�٣��δ�ܳɹ����У�";
			message_competition(msg);
			delete("pre_start");
			delete("start");
			set_heart_beat(0);
			return;
		}
		while(sizeof(inv)>1)
		{
			tmp1 = inv[random(sizeof(inv))];
			inv -= ({ tmp1 });
			tmp2 = inv[random(sizeof(inv))];
			inv -= ({ tmp2 });
			init_player(tmp1);
			init_player(tmp2);
			room = new("/d/lunjian/jingji");
			tmp1->move(room);
			tmp2->move(room);
			tmp1->kill_ob(tmp2);
			tmp2->kill_ob(tmp1);
			room->set("record",tmp1->query("name") + " vs " + tmp2->query("name"));
		}
		if(sizeof(inv))
		{
			allusers[inv[0]->query("id")] += 1;
			tell_object(inv[0],"���ڱ��־����������ֿգ��Զ���������ȴ���һ��ƥ�䡣\n");
		}
	}
	else if(localtime(now)[1]>LUNJIAN_PRE)
	{
		auto_check();
	}
}

int check_quit(object me)
{
	object ob;
	mapping my;
	string msg;

	my = me->query_entire_dbase();
	my["jing"]   = my["eff_jing"]   = my["max_jing"];
	my["jingli"] = my["eff_jingli"] = my["max_jingli"];
	my["qi"]     = my["eff_qi"]     = my["max_qi"]+me->query_gain_qi();
	my["neili"]  = my["max_neili"];

	if(me->is_busy())
		me->interrupt_me(me,me->query_busy());

	restore_status(me);

	tell_object(me, "���ӳ��˾�������\n");

	me->move(this_object());
	message("vision", "ֻ��" + me->name() + "������ŵ����˳�����\n",environment(me), ({ me }));
	return 1;
}

int check_out(object me)
{
	object ob;
	mapping my;
	string msg;

	my = me->query_entire_dbase();
	my["jing"]   = my["eff_jing"]   = my["max_jing"];
	my["jingli"] = my["eff_jingli"] = my["max_jingli"];
	my["qi"]     = my["eff_qi"]     = my["max_qi"]+me->query_gain_qi();
	my["neili"]  = my["max_neili"];

    me->add("combat_exp",1000);
    me->add("potential",1000);
	tell_object(me, HIR "\n�������ǰһ��ģ��...�������ˣ������ڱ����۽��н���ʧ��,���1000���飬1000Ǳ�ܣ�"NOR"\n");

	if(me->is_busy())
		me->interrupt_me(me,me->query_busy());

	restore_status(me);
	me->move(this_object());
	message("vision", "һ����Ӱٿ�Ĵ��˳������漴���ǡ�ž����һ�����ͼ�" + me->name() +"ˤ���˵��ϣ�һ��������������ӡ�\n", environment(me), ({ me }));
	tell_object(me, "�������У�����ñ������������������ص�ˤ���˵��ϡ�\n");
	if (! living(me))
		me->revive();
	return 1;
}

int check_win(object me)
{
	object ob;
	mapping my;
	string msg;

	my = me->query_entire_dbase();
	my["jing"]   = my["eff_jing"]   = my["max_jing"];
	my["jingli"] = my["eff_jingli"] = my["max_jingli"];
	my["qi"]     = my["eff_qi"]     = my["max_qi"]+me->query_gain_qi();
	my["neili"]  = my["max_neili"];

    me->add("combat_exp",2000);
    me->add("potential",2000);
    me->add("yuan_bao",5);
	tell_object(me, HIR "\n���ڱ����۽��л�ʤ����,���2000���飬2000Ǳ�ܣ�5��ͨ����"NOR"\n");

	if(me->is_busy())
		me->interrupt_me(me,me->query_busy());

	restore_status(me);
	me->move(this_object());

	return 1;
}