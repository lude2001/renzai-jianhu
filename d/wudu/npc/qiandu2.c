// by victori
inherit NPC;
#include <ansi.h>
void create()
{
        set_name("��Ѫ֩��",({"zhi zhu"}));
	set("race", "Ұ��");
        set("long", "һֻȭͷ��С��ȫ����ë�Ķ�֩�롣\n");
	set("age", 100);
	set("attitude", "peaceful");

	set("max_jing", 2500);
	set("max_qi", 1000+random(500));
	set("neili", 500+random(1000));
	set("max_neili", 2000);
	set("jiali", 10+random(100));

	set("str", 30);
	set("con", 50);

	set("limbs", ({ "ͷ��", "����", "����" }) );
	set("verbs", ({ "bite" }) );

	set_temp("apply/attack", 150);
	set_temp("apply/defense", 150);
	set_temp("apply/armor", 150);
	set_temp("apply/damage", 100);
       set_skill("unarmed",180+random(300));
       set_skill("parry",180+random(300));
       set_skill("dodge",180+random(300));
       set_skill("force",180+random(300));

	set("combat_exp", 1000000+random(40)*100000);

        set_weight(500000);
	setup();
}
void init()
{
        object me;
        add_action("do_xun", "xun");
//       object me,ob;
//        ::init();
        if (interactive(me = this_player()))
        {
      	       remove_call_out("kill_ob");
              call_out("kill_ob", 1, me);
        }
        ::init();
}
int do_xun(string arg)
{
	string owner,name;
	object owner_ob;
       object ob;
	object me,who;
	me =this_object();
	who=this_player();
	if (!arg || (arg != "zhi zhu"))
		return notify_fail("��Ҫѱ��ʲô��\n");
	if((string)who->query("family/family_name")!="�嶾��")
		return notify_fail("ʲô��\n");

	message_vision("$N��$nһ���Х���󵨣�����ѱ��������ʱ��\n\n", who,me);
	owner = query("owner");
	if(owner) who= find_player(owner);
		message_vision("$Nſ�ڵ��ϣ�һ��Ҳ���Ҷ��ˡ�\n",this_object());
	ob=new(__DIR__"zhizhu2.c");
	ob->move(environment(who));
	ob->set_leader(who);
       ob->set("host_id",who->query("id"));
       name=this_object()->query("name");
       ob->set_name(name,({"zhi zhu"}));
	destruct(this_object());
	return 1;
}
void die()
{
	object me,ob,item;
	mapping team;
	int rand;
	string file;

	ob = this_object();
	me = ob->query_temp("last_damage_from");

    rand = random(100);
	if(rand < 55)
	{
		item = new("clone/worm/obj/dunang");
		if(item)
		{
			item->move(environment(ob));
		}
    }

	destruct(ob);
}