// beidimiao.c  ������ 
inherit ROOM; 
void create() 
{ 
	set("short", HIY"����"NOR); 
	set("long", @LONG 
��ϪԴ��Ϫˮ��ˮ�ʴ�����ˮɫ�峺��һ������ȥ�����ܿ���Ϫˮ�ײ���ɫ��Ѥ���Ķ���ʯ���Լ���һȺȺ��ʯ����׽�Բص������ɽʯ�ײ�����Ϫˮ�ĵط��ѱ�Ϫˮ�������ʴ��ʴ��һ����С�ף�����һ����ɫ����̦���Ե�Խ�����϶������ˡ�
LONG 
	);
	set("exits", ([

		
		"east"  : "/d/shaolin/yidao2",
	])); 
	set("item_desc", ([ 
		"���������顿" : "ſ�ڰ�����ˮ��������������ɵ�ӡ�ҪǮ�ģ�\n"
		ZJOBACTS2"��ˮ:pa shui\n",
	]));
	set("no_fight", 1);
	set("valid_start_room", 1);
	set("no_sleep_room", 1);	
	setup(); 
} 
      
void init() 
{ 
	add_action("do_pa", "pa"); 
} 

int do_pa(string arg) 
{ 
	object me; 
	mapping fam; 
       
	me = this_player(); 
	if (! arg || arg == "") return 0; 
	if (arg == "shui") 
	{ 
		
			if (me->query("yuanbao")<200)
			{
				return notify_fail("���ˮĿǰ�������ܺȵģ�����������ɣ�\n"); 
			}
			
			message("vision", 
				me->name() + "ҡ��ҡͷ���ƺ����һЩ�����Ķ���˦����\n", 
				environment(me), me); 
			
			message("vision", 
				me->name() + "̾Ϣһ������Ȼ��Ȼſ�ڰ��ߺ���һ��ˮ��\n", 
				environment(me), ({me}) ); 

			me->add("yuanbao",-200);
			message("vision", 
				me->name() + "վ����գ��գ�۾����ƺ�������һЩ���������顣\n", 
				environment(me), ({me}) ); 	
			me->delete_skill("literate");	
			CHANNEL_D->do_channel(this_object(), "rumor",
				"��˵" + me->name(1) + "����������ˮ��");
			return 1; 
		 
		
	} 
} 


