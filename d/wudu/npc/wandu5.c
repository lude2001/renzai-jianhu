// by victori
inherit NPC;
#include <ansi.h>

void create()
{
        set_name("三足金蟾",({"chan chu"}));
	set("race", "野兽");
        set("long", "一只拳头大小通身金黄的小蟾蜍，据说只有月宫才有。\n");
	set("age", 10000);
	set("attitude", "peaceful");

	set("max_jing", 2500);
	set("max_qi", 2500);

	set("str", 40);
	set("con", 50);

	set("limbs", ({ "头部", "身体", "尾巴" }) );
	set("verbs", ({ "bite" }) );

	set_temp("apply/attack", 300);
	set_temp("apply/defense", 300);
	set_temp("apply/armor", 300);
	add_temp("apply/damage", 200);
       set_skill("unarmed",200+random(580));
       set_skill("parry",200+random(580));
       set_skill("dodge",200+random(580));
       set_skill("force",200+random(580));
	set("combat_exp", 5000000+random(100)*100000);

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
       object ob;
	object me,who;
	me =this_object();
	who=this_player();
	if (!arg || (arg != "chan chu"))
		return notify_fail("你要驯服什么？\n");
//	if(me->is_fighting())
//		return notify_fail("这只蟾蜍正在战斗。\n");
	if((string)who->query("family/family_name")!="五毒教")
		return notify_fail("什么？\n");

	message_vision("$N对$n一阵怪啸：大胆，还不驯服更待何时？\n\n", who,me);
	owner = query("owner");
	if(owner) who= find_player(owner);

	message_vision("$N趴在地上，一动也不敢动了。\n",this_object());
	ob=new(__DIR__"chanchu3");
	ob->move(environment(who));
	ob->set_leader(who);
       ob->set("host_id",who->query("id"));
       name=this_object()->query("name");
       ob->set_name(name,({"chan chu"}));

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