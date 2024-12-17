
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
        set_name(HIG "������" NOR, ({"feng lingzhu", "fengzhu"}) );
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("material", "crystal");
                set("value",10000);
set("no_steal",1);
                set("no_drop", "��˱���ı����������󰡡�\n");
                set("no_give", "����ϡ��֮����ô������������?\n");
                set("no_sell", "��?����ϡ��֮��˭�����!\n");
                set("long","��˵�е����б���֮һ����֮�ɱܷ紵�����ɷ�����ϵ������Ϊ����������֮�\n");
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
    return notify_fail("��Ҫ���ʲô��\n");
  msg = "$N����һ��"+name+"����ɫ�ķ�����·�û�������������衣\n"; 
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
    return notify_fail("��Ҫժ��ʲô��\n");

  msg = "$N��"+name+"�����ժ��������\n"; 
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

        msg = HIY"�����鷢�����ص�������$N����ͻȻ����������Ц����ֻ�����ȹ����ְֳŽ��ȣ�\n
˫����ҡ������ƮƮ��˵������������ȴ��һ�ɼ��糯$n��ȥ\n"NOR;
//divid by 10;

                ap = who->query("combat_exp");
                dp = target->query("combat_exp");
                        
                        
                if( random(dp) < ap/2 )
                 {
                        damage = 500+random(300)+who->query_skill("xianfeng-spells", 1);
                        damage -= random((int)target->query("eff_jing") / 100);
				
                        if( damage > 0 ) 
                        {
                                msg += HIC "���$n��ܲ�������������˫�ۣ��������ã�\n" NOR;
				    target->recieve_damage("qi", damage);	
                               target->start_busy(3+random(3));
				    ob->add("use_times", 1);
                        } 
            else
//here, cast failed and the target's mana_factor will be added to the previous
//damage to hurt yourself:(...note damage<0.
                msg += HIC "\n˭֪$n���޷�Ӧ��\n" NOR;   
                }
                else
                        msg += "���Ǳ�$n�㿪�ˡ�\n";

                message_vision(msg, who, target); 
        }
if(ob->query("use_times")>5)
{
message_vision("$N���еķ�����ͻȻ����һ����â�������İ���������\n", who, target); 
remove_call_out("fengzhuconditions");
}
else
call_out("fengzhuconditions",10,who,ob);
}



void owner_is_killed()
{
write(HIY"ֻ����ǰ���һ��....������ͻȻ������!\n"NOR);
destruct(this_object());
}