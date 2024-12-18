// made by lks

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "血雾"; }

int exert(object me, object target)
{
        object weapon;
        int damage;
        string msg;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("「血雾」只能对战斗中的对手使用。\n");

        if( (int)me->query_skill("force", 1) < 100 )
                return notify_fail("你的内功底子太薄，不能使用。\n");
                                
        if( (int)me->query_skill("huaxue-dafa", 1) < 120 )
                return notify_fail("你的化血大法不够熟练。\n");
                        
        if( (int)me->query("neili", 1) < 400 )
                return notify_fail("你现在内力太弱，不能使用「血雾」。\n");
                        
        msg = HIC "$N气贯丹田，咬破舌尖，吐出一口血雾。罩向$n。\n"NOR;

        if (random(me->query_skill("force")) > target->query_skill("force")/2 )
        {
        
                damage = (int)me->query_skill("force", 1);
                damage = damage +  (int)me->query_skill("huaxue-dafa",1);
                
                target->receive_damage("qi", damage);
                target->receive_wound("qi", damage/3);

                me->add("neili", -300);
                msg += WHT"$n一个不防，被血雾笼罩了全身。只听见$n在血雾中惨叫连连!\n"NOR;
                me->start_busy(2);
        } else 
        {
                msg += YEL"可是$p向旁边侧身一闪,躲过了血雾。\n"NOR;
                me->add("neili", -100);
                me->start_busy(4);
        }
        message_vision(msg, me, target);

        return 1;
}


