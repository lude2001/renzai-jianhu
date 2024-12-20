
#include <ansi.h>
#include <dbase.h>
#include <armor.h>

inherit F_UNIQUE;
inherit NECK;

int do_wear(string arg);
int do_remove(string arg);
object offensive_target(object me);

void create()
{
        set_name(HIG "风灵珠" NOR, ({"feng lingzhu", "fengzhu"}) );
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "颗");
                set("material", "crystal");
                set("value",10000);
set("no_steal",1);
                set("no_drop", "如此宝贵的宝物再世难求啊。\n");
                set("no_give", "这种稀世之宝怎么能轻易送人呢?\n");
                set("no_sell", "卖?这种稀世之宝谁买得起啊!\n");
                set("long","传说中的五行宝珠之一，佩之可避风吹，并可发出风系法术。为祈雨所必需之物。\n");
                set("bb",1);
//                set("replace_file", "/d/obj/flower/rose");
                set("armor_prop/armor", 1);
                set("spells/feng", 1);
        }
        setup();
}

int init()
{
        add_action("do_wear","wear");
        add_action("do_remove", "remove");
        return 1;
}

// This function selects a random target for offensive spells/functions.
object offensive_target(object me)
{
        int sz;
        object *enemy;

        enemy = me->query_enemy();
        if( !enemy || !arrayp(enemy) ) return 0;

        sz = sizeof(enemy);
        if( sz > 4 ) sz = 4;

        if( sz > 0 ) return enemy[random(sz)];
        else return 0;
}

int do_wear (string arg)
{
  object me = this_player();
  object zhu = this_object();
  string name = zhu->query("name");
  string msg;

if(arg!="all" && arg != "fengzhu" && arg != "feng lingzhu")
    return notify_fail("你要佩带什么？\n");
  msg = "$N戴上一颗"+name+"，绿色的风灵珠仿佛没有重量，随风而舞。\n"; 
  zhu->set("wear_msg",msg);
remove_call_out("fengzhuconditions");
call_out("fengzhuconditions",5,me,zhu);
  return 0;
}

int do_remove (string arg)
{
  object me = this_player();
  object zhu = this_object();
  string name = zhu->query("name");
  string msg;
if ( arg != "all" && arg != "fengzhu" && arg != "feng lingzhu")
    return notify_fail("你要摘掉什么？\n");

  msg = "$N将"+name+"轻轻地摘下来……\n"; 
  zhu->set("unequip_msg",msg);
  remove_call_out("fengzhuconditions");
  return 0;
}

void fengzhuconditions(object who,object ob)
{
string type;
     object target;
     int ap,dp,damage;
     string msg;
          
type = ob->query("armor_type");
if( who->query_temp("armor/" + type) && ob->query("equipped")!="worn")
return;
     if( who->is_fighting())
     {
        target = offensive_target(who);
        if( ! target ) return ;
        if( ! present( target,environment(who)) ) return ;

        msg = HIY"风灵珠发出呜呜的声音，$N耳中突然响起银铃般的笑声，只见铁扇公主手持芭蕉扇，\n
双手轻摇，长衫飘飘，说不出的潇洒快活。却有一股疾风朝$n刮去\n"NOR;
//divid by 10;

                ap = who->query("combat_exp");
                dp = target->query("combat_exp");
                        
                        
                if( random(dp) < ap/2 )
                 {
                        damage = 500+random(300)+who->query_skill("xianfeng-spells", 1);
                        damage -= random((int)target->query("eff_jing") / 100);
				
                        if( damage > 0 ) 
                        {
                                msg += HIC "结果$n躲避不及，被风迷了双眼，动弹不得！\n" NOR;
				    target->recieve_damage("qi", damage);	
                               target->start_busy(3+random(3));
				    ob->add("use_times", 1);
                        } 
            else
//here, cast failed and the target's mana_factor will be added to the previous
//damage to hurt yourself:(...note damage<0.
                msg += HIC "\n谁知$n毫无反应。\n" NOR;   
                }
                else
                        msg += "但是被$n躲开了。\n";

                message_vision(msg, who, target); 
        }
if(ob->query("use_times")>5)
{
message_vision("$N手中的风灵珠突然发出一道光芒，慢慢的暗了下来。\n", who, target); 
remove_call_out("fengzhuconditions");
}
else
call_out("fengzhuconditions",10,who,ob);
}



void owner_is_killed()
{
write(HIY"只见眼前金光一闪....风灵珠突然破裂了!\n"NOR);
destruct(this_object());
}