// by victori
inherit NPC;
#include <ansi.h>

string *first_name = ({"�嶾", "����", "���", "����"});
string *name_words = ({"���"});
void create()
{
        string name;
        name = first_name[random(sizeof(first_name))];
        name += name_words[random(sizeof(name_words))];
        set_name(name,({"chan chu"}));
	set("race", "Ұ��");
        set("long", "һֻȭͷ��С����ͷ���Ե�С��󡡣\n");
	set("age", 100);
	set("attitude", "peaceful");

	set("max_jing", 200);
	set("max_qi", 1200);

	set("str", 50);
	set("con", 100);

	set("limbs", ({ "ͷ��", "����", "β��" }) );
	set("verbs", ({ "bite" }) );

	set_temp("apply/attack", 70);
	set_temp("apply/defense", 70);
	set_temp("apply/armor", 70);

	set("combat_exp", 500000);

        set_weight(500000);
	setup();
}
void init()
{
        object me,ob;
        add_action("do_xun", "xun");
//       object me,ob;
//        ::init();
        if (interactive(me = this_player()))
        {
	if (!(ob = present("xionghuang", this_player())))
               {
      	       remove_call_out("kill_ob");
              call_out("kill_ob", 1, me);
		}
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
	if (!arg || (arg != "chan chu"))
		return notify_fail("��Ҫѱ��ʲô��\n");

	if((string)who->query("family/family_name")!="�嶾��")
		return notify_fail("ʲô��\n");

	message_vision("$N��$nһ���Х���󵨣�����ѱ��������ʱ��\n\n", who,me);
	owner = query("owner");
	if(owner) who= find_player(owner);

		message_vision("$Nſ�ڵ��ϣ�һ��Ҳ���Ҷ��ˡ�\n",this_object());

	ob=new(__DIR__"chanchu1.c");
	ob->move(environment(who));
	ob->set_leader(who);
       ob->set("host_id",who->query("id"));
       name=this_object()->query("name");
       ob->set_name(name,({"chan chu"}));
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