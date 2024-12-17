// by snow@jhfy
inherit NPC;
#include <ansi.h>

string *first_name = ({ "花皮", "青竹", "四脚", "眼镜王"});
string *name_words = ({ "蛇"});
void create()
{
        string name;
        name = first_name[random(sizeof(first_name))];
        name += name_words[random(sizeof(name_words))];
        set_name(name,({"du she"}));
	set("race", "野兽");
        set("long", "一条一尺多长，鬼头鬼脑的小蛇。\n");
	set("age", 100);
	set("attitude", "peaceful");

	set("max_jing", 600);
	set("max_qi", 600);

	set("str", 35);
	set("con", 50);

	set("limbs", ({ "头部", "身体", "尾巴" }) );
	set("verbs", ({ "bite" }) );

	set_temp("apply/attack", 80);
	set_temp("apply/defense", 50);
	set_temp("apply/armor", 50);

	set("combat_exp", 100000+random(40)*10000);
	set("chat_msg",40);
	set("chat_msg_combat",({
		"小蛇张露出两颗锋利的毒牙，凶狠狠地向你咬来。"
		}));

        set_weight(500000);
	setup();
}
void init()
{
        object me,ob;
//       ::init();
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
	if (!arg || (arg != "du she"))
		return notify_fail("你要驯服什么？\n");
	if((string)who->query("family/family_name")!="五毒教")
		return notify_fail("什么？\n");

	message_vision("$N对$n一阵怪啸：大胆，还不驯服更待何时？\n\n", who,me);
	owner = query("owner");
	if(owner) who= find_player(owner);
		message_vision("$N趴在地上，一动也不敢动了。\n",this_object());
	ob=new(__DIR__"she1.c");
	ob->move(environment(who));
	ob->set_leader(who);
       ob->set("host_id",who->query("id"));
       name=this_object()->query("name");
       ob->set_name(name,({"du she"}));

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