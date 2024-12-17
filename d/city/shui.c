// beidimiao.c  北帝庙 
inherit ROOM; 
void create() 
{ 
	set("short", HIY"忘川"NOR); 
	set("long", @LONG 
香溪源的溪水，水质纯净，水色清澈，一眼望下去，就能看到溪水底部那色彩绚丽的鹅卵石，以及那一群群在石缝中捉迷藏的鱼儿。山石底部靠近溪水的地方已被溪水长年的侵蚀而蚀出一个个小孔，铺上一层绿色的青苔，显得越发古老而神秘了。
LONG 
	);
	set("exits", ([

		
		"east"  : "/d/shaolin/yidao2",
	])); 
	set("item_desc", ([ 
		"【忘川忘情】" : "趴在岸边饮水，可遗忘读书变成傻子。要钱的！\n"
		ZJOBACTS2"饮水:pa shui\n",
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
				return notify_fail("这个水目前不是你能喝的！想好了再来吧！\n"); 
			}
			
			message("vision", 
				me->name() + "摇了摇头，似乎想把一些不愉快的东西甩掉。\n", 
				environment(me), me); 
			
			message("vision", 
				me->name() + "叹息一声，毅然决然趴在岸边喝了一口水。\n", 
				environment(me), ({me}) ); 

			me->add("yuanbao",-200);
			message("vision", 
				me->name() + "站起来眨了眨眼睛，似乎忘记了一些不愉快的事情。\n", 
				environment(me), ({me}) ); 	
			me->delete_skill("literate");	
			CHANNEL_D->do_channel(this_object(), "rumor",
				"据说" + me->name(1) + "喝下了忘情水。");
			return 1; 
		 
		
	} 
} 


