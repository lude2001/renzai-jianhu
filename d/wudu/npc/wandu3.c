// by victori
inherit NPC;
#include <ansi.h>

void create()
{
        set_name("阴山天蜈",({"wu gong"}));
	set("race", "野兽");
        set("long", "一条三寸多长，长有一双翅膀剧毒蜈蚣。\n");
	set("age", 10000);
	set("attitude", "peaceful");

	set("max_jing", 2500);
	set("max_qi", 3500);
	set("neili", 2000);
	set("max_neili", 4000);
	set("jiali", 200);


	set("str", 110);
	set("con", 50);

	set("limbs", ({ "头部", "身体", "尾巴" }) );
	set("verbs", ({ "bite" }) );

	set_temp("apply/attack", 200);
	set_temp("apply/defense", 350);
	set_temp("apply/armor", 200);
	add_temp("apply/damage", 100);
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
	if (!arg || (arg != "wu gong"))
		return notify_fail("你要驯服什么？\n");
//	if(me->is_fighting())
//		return notify_fail("这只蜈蚣正在战斗。\n");
	if((string)who->query("family/family_name")!="五毒教")
		return notify_fail("什么？\n");

	message_vision("$N对$n一阵怪啸：大胆，还不驯服更待何时？\n\n", who,me);
	owner = query("owner");
	if(owner) who= find_player(owner);
		message_vision("$N趴在地上，一动也不敢动了。\n",this_object());
	ob=new(__DIR__"wugong3");
	ob->move(environment(who));
	ob->set_leader(who);
       ob->set("host_id",who->query("id"));
       name=this_object()->query("name");
       ob->set_name(name,({"wu gong"}));
	//destruct(this_object());
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