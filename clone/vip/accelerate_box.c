// chuji_box.c
inherit ITEM;
#include <ansi.h>
void create()
{
	set_name(HIY"������ٿ�����"NOR,({"quest box"}));
	set_weight(5000);
	
	if( clonep() )
		set_default_object(__FILE__);
	else
       {
	    set("long",
		"����ϵͳ������"+this_object()->query("name")+",\n"ZJURL("cmds:openbox boxno4")ZJSIZE(15)"��"NOR"���������������ȡһ��������ٿ�Ŷ��!\n");
	    set("unit","��");
	    set("win_box",1);
	    set("yuanbao",50);
	    
	}
}
void init()
{
    if (environment()==this_player())
    add_action("do_openbox","openbox boxno4",1);
}
//�򿪱���ĺ���
int do_openbox()
{
   int i;
   int num=1;
   string obj=""; 
   object ob;
   /*
   * ������ٿ�
  */
   string *box=
({
"/clone/quest_give/quest_one","/clone/quest_give/quest_two","/clone/quest_give/quest_three","/clone/quest_give/quest_four",
});
  
    object me = this_player();
	if (me->is_busy())
	      { write("����һ������δ��ɣ�\n"); return 1;}
	if( me->is_fighting() )
	      { write("ս���п����䣿����ѽ��\n"); return 1;}
       
    message_vision(HIG"$N�������["+this_object()->query("name")+"]�ĸ���,���仯Ϊһ���ɫ�⻪��"NOR"\n",me);
    i=random((int)sizeof(box));
    
    ob = new(box[i]); 
    if(ob->query("base_value"))
    {
       num=1;
       ob->set_amount(num);
    }
   tell_object(me,""HIY"*****************************************************\n");
  tell_object(me,""HIR"��ϲ: "NOR"���["+this_object()->query("name")+"]�еõ���..."+chinese_number(num)+ob->query("unit")+HIY+"<< "+ob->query("name")+HIY+" >>"+NOR+"\n");
 tell_object(me,""HIY"*****************************************************"NOR"\n");
    ob->move(me); 
    destruct(this_object());
	return 1;
}
int query_autoload()
{
	return 1;
}