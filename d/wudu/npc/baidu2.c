// by victori
inherit NPC;
#include <ansi.h>

string *first_name = ({ "毒", "长腿", "大肚", "花斑"});
string *name_words = ({ "蜘蛛"});
void create()
{
        string name;
        name = first_name[random(sizeof(first_name))];
        name += name_words[random(sizeof(name_words))];
        set_name(name,({"zhi zhu"}));
	set("race", "野兽");
        set("long", "一只鸡蛋大小，鬼头鬼脑的小蜘蛛。\n");
	set("age", 100);
	set("attitude", "peaceful");

	set("max_jing", 200);
	set("max_qi", 200);

	set("str", 20+random(30));
	set("con", 50+random(50));

	set("limbs", ({ "头部", "身体", "长腿" }) );
	set("verbs", ({ "bite" }) );

	set_temp("apply/attack", 50+random(50));
	set_temp("apply/defense", 50);
	set_temp("apply/armor", 50);

	set("combat_exp", 100000+random(40)*10000);

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
	if (!arg || (arg != "zhi zhu"))
		return notify_fail("你要驯服什么？\n");

	if((string)who->query("family/family_name")!="五毒教")
		return notify_fail("什么？\n");

	message_vision("$N对$n一阵怪啸：大胆，还不驯服更待何时？\n\n", who,me);
	owner = query("owner");
	if(owner) who= find_player(owner);
		message_vision("$N趴在地上，一动也不敢动了。\n",this_object());
	ob=new(__DIR__"zhizhu1.c");
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