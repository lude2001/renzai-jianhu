// huxin-dan.c �������ĵ�

#include <ansi.h>

inherit ITEM;

void init()
{
	add_action("do_eat", "pai");
}

void create()
{
	set_name(HIR"���ֱ�����"NOR, ({"xumi bei"}));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long","һ��"+name()+"���ഫ����ɽ�������ʮ��һ�����ֱ����������е�һ�����������������"ZJURL("cmds:pai xumi bei")+ZJSIZE(20)+"��һ��"NOR"��\n");
		set("value", 2000);
		set("unit", "��");
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
		return notify_fail("��Ҫ��ʲô?\n");

	if(me->is_busy())
		return notify_fail("����æ���ء�\n");

	if (sizeof(filter_array(me->query_enemy(),(: userp :))))
		return notify_fail("���ں���Ҷ���ս��������ʹ�����ֱ���\n");

	if(me->query("combat_exp", 1) > 2500000) 
		return notify_fail("���Ѿ������ָ����ˣ��˱��Ѿ�����ʧȥ�����ã�\n");

//	if(me->query_condition("medicine") > 0 )
//		  return notify_fail("���ֱ����ڲ������������ٵȵȰɡ�\n");
if (me->query("neili")<10000)
{
me->add("neili",2000);
me->add("jing",2000);
}

//		me->apply_condition("medicine", 10);
		message_vision(HIG"$N���������ֱ�"+name()+HIG"����ʱ������ӯ��"NOR"\n" , me);
		me->start_busy(2);	

/*  if(ob->query("numb") < 1){
		write(""+name()+"�Ѿ����Ե�һ˿��ʣ�ˡ�\n");
		destruct(this_object()); 
	     }
	   else write(""+name()+"���ܼ���ʹ��"+ob->query("numb")+"�Ρ�\n");
   
		return 1;
	     }*/
	     return 1;
	
}


int query_autoload() { return 1; }

