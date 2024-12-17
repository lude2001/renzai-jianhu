// by victori
inherit NPC;
#include <ansi.h>


void create()
{
        set_name("九尾蝎",({"xie zi"}));
	set("race", "野兽");
        set("long", "一条一丈来长，有九只尾蛰的大蝎子。\n");
	set("age", 10000);
	set("attitude", "peaceful");

	set("max_jing", 2500);
	set("max_qi", 2500);
	set("neili", 2000);
	set("max_neili", 4000);
	set("jiali", 200);

	set("str", 100);
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


        set_weight(5000);
	setup();
}
int init()
{
        object me,who;
        ::init();
        who = this_object();
        if (interactive(me = this_player()))
        {
	if (me->query("id")==who->query_temp("kill_name"))
              {
	       remove_call_out("kill_ob");
               call_out("kill_ob", 1, me);
		}
        }
       add_action("do_attack","attack");
       add_action("do_stop","stop");
       add_action("do_send","sendto");
       add_action("do_sha","sha");
       add_action("do_guard","guard");
	add_action("do_hit","hit");
	add_action("do_hit","kill");
	add_action("do_hit","touxi");
//	remove_call_out("do_baohu");
//	call_out("do_baohu",5);

}



int do_attack(string arg)
{
  object ob;
  object me=this_player();
  object who=this_object();
 //  if(query("id")=="shuang er")
 //  {say("你无权使用此命令。\n");
 //  return 0;}
 // sscanf(query("id"),"dushe",host_id);
  if(me->query("id")!=(who->query("host_id")))
  return notify_fail(who->query("name")+"连理都不理你！\n");
  if(!arg||!objectp(ob=present(arg,environment(me))))
	return notify_fail(who->query("name")+"傻傻地望着你，不明白你的意思。\n");
  if(ob->query("id")==me->query("id"))
	return notify_fail(who->query("name")+"急忙把头一低，似乎不愿意去干。\n");
  if(!living(ob))
	 return notify_fail(who->query("name")+"说:"
              +ob->query("name")+"已经这样啦你还要...??!!\n");
  message_vision(who->query("name")+"吱吱怪叫一声冲了出去.\n",me);
  fight_ob(ob);
  return 1;
}

int do_stop()
{
 object who=this_object();

  object me=this_player();
 // if(query("id")=="dushe")
 // return notify_fail("你无权使用此命令。\n");
 //   sscanf(query("id"),"%s's shuang er",host_id);
  if(me->query("id")!=(who->query("host_id")))
  return notify_fail(who->query("name")+"连理都不理你！\n");
 who->set_leader(me);
message_vision("$N对"+who->query("name")+"喝道：别打了，跟我来。\n",me);
// if(!is_fighting())
//	 return notify_fail(who->query("name")+"现在没和人打斗.\n");
 command("halt");
 who->delete_temp("kill_name");
 message_vision(who->query("name")+"乖乖的回到$N身边。\n",me);
 return 1;
}

int do_sha(string arg)
{
  object who=this_object();

	object me,ob;

	me = this_player();
  if(me->query("id")!=(who->query("host_id")))
  return notify_fail(who->query("name")+"连理都不理你！\n");
	if(!arg||!objectp(ob=present(arg,environment(me))))
	return notify_fail("你要"+who->query("name")+"杀谁？\n");
  if(ob->query("id")==me->query("id"))
	return notify_fail(who->query("name")+"急忙把头一低，似乎不愿意去干。\n");
	if(!environment(ob)->query("no_fight"))
	{
        message_vision(who->query("name")+"吱吱怪叫一声冲了出去.\n",me);
	command("say 嘿嘿,你认命吧，主人要我杀了你!");
	who->set_leader(ob);
       who->set_temp("kill_name",ob->query("id"));
	remove_call_out("kill_ob");
  	call_out("kill_ob", 0, ob);
	}
	return 1;
}
int hit_ob(object me, object ob, int damage)
{
       if ((string)ob->query("family/family_name") != "五毒教") {
	     	ob->apply_condition("xiezi_poison", 20
              +(int)ob->query_condition("xiezi_poison") );
              tell_object(ob, HIG "你觉得被咬中的地方一阵麻木！\n" NOR );
	}
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
int do_guard(string arg)            //160
{
  object who=this_object();
       int i ;
	object me,ob;
	object* enemy;
	me = this_player();
       if(me->query("id")!=(who->query("host_id")))
            return notify_fail(who->query("name")+"连理都不理你！\n");
	if(!arg)
	ob = this_player();
	if(arg){
              if(!userp(present(arg,environment(me))))
	           return notify_fail("你要"+who->query("name")+"保护谁？\n");
              }
	if(arg)
            ob = present(arg,environment(me));
       who->set_temp("guard_ob",ob->query("id"));
 	message("vision",
		 name() + "发出轻微的吱叫声，开始绕着"+ob->name()+"四处游走！\n" NOR,environment(), this_object() );
	enemy = ob->query_enemy();
	i = sizeof(enemy);
	while(i--) {
		if( enemy[i] && living(enemy[i]) ) {
			kill_ob(enemy[i]);
			if( userp(enemy[i]) ) enemy[i]->fight_ob(this_object());
			else enemy[i]->kill_ob(this_object());
		}
	}
       ob->remove_all_killer();
	who->set_leader(ob);
	return 1;
}
int do_hit(string arg)
{
	object ob = this_object();
	object me = this_player();


	if (!arg )  return 0;
       if (arg != ob->query_temp("guard_ob")) return 0;
	message_vision("$N一声怪叫忽然挡在了"+me->name()+"的面前。\n", this_object());
	remove_call_out("kill_ob");
  	call_out("kill_ob", 0, me);
	return 1;
}

