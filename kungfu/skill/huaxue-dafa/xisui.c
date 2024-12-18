// made by lks

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "吸髓大法"; }

int exert(object me, object target)
{
        object weapon;
        int damage;
        string msg;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("「吸髓大法」只能对战斗中的对手使用。\n");

        if( (int)me->query_skill("force", 1) < 80 )
                return notify_fail("你的内功底子太薄，不能使用。\n");
                                
        if( (int)me->query_skill("huaxue-dafa", 1) < 100 )
                return notify_fail("你的化血大法不够熟练。\n");
                        
        if( (int)me->query("neili", 1) < 300 )
                return notify_fail("你现在内力太弱，不能使用「吸髓大法」。\n");
                        
        msg = HIC "$N气贯丹田，顿时脸上一片紫青，双掌推出一股阴冷无比的气流。罩向$n。\n"NOR;
        if (wizardp(me))
        {
               msg += WHT"$n只觉得一阵阴风袭来，一股寒劲直冲入脑髓、骨髓、血髓、脉髓。。。。\n"NOR;
                target->apply_condition("xisui_du",15);
        message_vision(msg, me, target);
        return 1;
        }
        if (random(me->query_skill("force")) > target->query_skill("force") )
        {
                if (random(15)<10)
                {
                target->remove_all_killer();
                
                damage = (int)me->query_skill("force", 1);
                damage = damage +  (int)me->query_skill("huaxue-dafa",1);
                
                target->receive_damage("qi", damage);
                target->receive_wound("qi", damage/3);
                target->apply_condition("xisui_du",15);
                me->add("neili", -200);
                msg += WHT"$n只觉得一阵阴风袭来，一股寒劲直冲入脑髓、骨髓、血髓、脉髓。。。。\n"NOR;
                me->start_busy(2);
                }
        } else 
        {
                msg += YEL"可是$p向旁边侧身一闪,躲过了这股阴冷无比的气流。\n"NOR;
                me->add("neili", -100);
                me->start_busy(4);
        }
        message_vision(msg, me, target);

        return 1;
}

