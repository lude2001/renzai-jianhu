// huxin-dan.c 天王护心丹

#include <ansi.h>

inherit ITEM;

void init()
{
	add_action("do_eat", "pai");
}

void create()
{
	set_name(HIR"须弥碑【绑】"NOR, ({"xumi bei"}));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long","一座"+name()+"，相传须弥山浩瀚无垠，十里一座须弥碑，这是其中的一座，具有神奇的妙用"ZJURL("cmds:pai xumi bei")+ZJSIZE(20)+"拍一下"NOR"。\n");
		set("value", 2000);
		set("unit", "座");
		set("no_sell",1);
        set("no_give",1);
		set("no_put", 1);
        set("no_drop",1);
        set("no_get",1);
        set("no_teal", 1);
		set("yuanbao", 300);
		set("no_put", 1);
		set("no_get", 1);
		set("no_drop", 1);
		set("no_give", 1);
		set("no_sell", 1);
		set("no_steal", 1);
		set("no_beg", 1);
	  }
   	setup();
}

int do_eat(string arg)
{
       int q, j;

       object me, ob;      
       me=this_player();
       ob=this_object();

	if (!arg || arg!="xumi bei")
		return notify_fail("你要干什么?\n");

	if(me->is_busy())
		return notify_fail("你正忙着呢。\n");

	if (sizeof(filter_array(me->query_enemy(),(: userp :))))
		return notify_fail("正在和玩家对手战斗，不能使用须弥碑。\n");

	if(me->query("combat_exp", 1) > 2500000) 
		return notify_fail("你已经是武林高手了，此碑已经对你失去了作用！\n");

//	if(me->query_condition("medicine") > 0 )
//		  return notify_fail("须弥碑正在补充能量，你再等等吧。\n");
if (me->query("neili")<10000)
{
me->add("neili",2000);
me->add("jing",2000);
}

//		me->apply_condition("medicine", 10);
		message_vision(HIG"$N拍了拍须弥碑"+name()+HIG"，顿时内力充盈！"NOR"\n" , me);
		me->start_busy(2);	

/*  if(ob->query("numb") < 1){
		write(""+name()+"已经被吃的一丝不剩了。\n");
		destruct(this_object()); 
	     }
	   else write(""+name()+"还能继续使用"+ob->query("numb")+"次。\n");
   
		return 1;
	     }*/
	     return 1;
	
}


int query_autoload() { return 1; }

