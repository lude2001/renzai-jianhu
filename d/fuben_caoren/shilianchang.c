inherit ROOM;

int start_fuben_caoren(object who);
int get_max_level(string *skills, mapping map_skills);

void create()
{
	set("short", "������");
	set("long", @LONG
���ǵ�������������
LONG);

	set("action_list", ([
		"�뿪����" : "likai",
		]));
	
	set("no_magic", 1);
	set("no_clean_up_fb", 1);
	setup();
}

void init()
{
	add_action("do_likai", "likai");
}

int do_likai(string arg)
{
	if(!arg)
		return notify_fail(ZJOBLONG + "��ȷ��Ҫ�뿪������\n" ZJOBACTS2 + "ȷ��:likai y\n");
	
	if(arg == "y")
		this_player()->move("d/city/kedian");
	remove_call_out("end_fuben_caoren");
	destruct(this_object());
	
	return 1;
}

int start_fuben_caoren(object who)
{
	int last_time, i, level;
	object caoren;
	mapping caoren_hp;
	
	last_time = who->query("fuben_caoren/last_time");
	if((last_time/86400 == time()/86400) && (who->query("fuben_caoren/count") > 1))
	{
		tell_object(who, "����������һ��ֻ�ܽ������Ρ�\n");
		return 0;
	}
	else if(last_time/86400 != time()/86400)
	{
		who->delete("fuben_caoren/count");
	}
	
	for(i = 0; i < 10; i++)
	{
		caoren = new(__DIR__"caoren");
		level = get_max_level(keys(who->query_skills()), who->query_skills()) / 100;
		caoren_hp = caoren->query_entire_dbase();
		caoren_hp["max_qi"] = caoren_hp["eff_qi"] = caoren_hp["qi"] = caoren_hp["max_qi"] + 1000 * level;
		caoren_hp["max_neili"] = caoren_hp["neili"] = caoren_hp["max_neili"] + 500 * level;
		caoren_hp["max_jing"] = caoren_hp["jing"] = caoren_hp["eff_jing"] =caoren_hp["max_jing"] + 500 * level;
		
		caoren->move(this_object());
	}
	who->set("fuben_caoren/last_time", time());
	who->add("fuben_caoren/count", 1);
	set("fuben_caoren", who->query("fuben_caoren/count"));
	who->move(this_object());
	call_out("end_fuben_caoren", 900, who, this_object());
	write("��ս��ʼ������\n");
	
	return 1;
}

void end_fuben_caoren(object me, object room)
{
	if (sscanf(base_name(environment(me)), __DIR__"%*s") && (room->query("fuben_caoren") == me->query("fuben_caoren/count")))
	{
		me->move("d/city/kedian");
		tell_object(me,HBRED+HIY"��սʱ�䵽���㱻�������ݿ͵�\n"NOR);
	}
	if(objectp(room))
		destruct(room);
}

int get_max_level(string *skills, mapping map_skills)	//��ȡ�书��������ߵȼ��书
{
	string temp;
	int max_level = 0;
	
	foreach(temp in skills)
	{
		if (max_level < map_skills[temp])
		{
			max_level = map_skills[temp];
		}
	}
	
	return max_level;
}
