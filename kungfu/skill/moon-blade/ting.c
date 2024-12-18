#include <ansi.h>
#include <combat.h>

#define XIAN "「" HIM "小楼一夜听春雨" NOR "」"
string query_name() { return "小楼一夜"ZJBR"听春雨"; }
inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;



        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(XIAN "只能对战斗中的对手使用。\n");
 
        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "blade")
                return notify_fail("你使用的武器不对，难以施展" XIAN "。\n");

        if ((int)me->query_skill("force") < 160)
                return notify_fail("你的内功火候不够，难以施展" XIAN "。\n");

        if ((int)me->query_skill("moon-blade", 1) < 200)
                return notify_fail("你的圆月弯刀还不到家，难以施展" XIAN "。\n");

        if (me->query_skill_mapped("blade") != "moon-blade")
                return notify_fail("你没有激发圆月弯刀，难以施展" XIAN "。\n");

        if ((int)me->query("neili") < 200)
                return notify_fail("你的真气不够，难以施展" XIAN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");
        
        msg = HBRED "小楼一夜听春雨：圆月落，刀光起。纵横大地十万里。刀光寒如雪，何处听春雨？\n" NOR
              HIY "只听唰的一声，" + weapon->name() + HIY "出手了！一切只能以一个快字去形容，发生在肉眼难看清楚的高速下，\n"
              "$N" HIY "这一刀劈出时，好像也是直直的，但是这笔直劈出来的一刀，竟忽然闪起了一道弯弯的刀光。\n"
              "弯弯的刀，弯弯的刀光，开始时宛如一弯新月，忽然间就变成了一道飞虹。这一道弯弯的刀光闪起时，\n"
              + weapon->name() + HIY "上的妖异之气，使人为之震眩迷惑。\n" NOR;       
        
        ap = me->query_skill("blade");
        dp = target->query_skill("dodge");
             
        if (ap / 2 + random(ap) > dp)
        {
                damage = 0;
                if (me->query_skill("blade") > target->query_skill("force") && 
                    ! target->query("reborn"))
                {
                        me->start_busy(2);
                        me->add("neili", -100);
                        msg += HIR "当$n" HIR "感到$N" HIR "出手时，" + weapon->name() + HIR "早已挥出，化作满月时的月光，划过两丈的虚空劈向$n。\n"
                               "$n" HIR "只感到周遭所有的气流和生气都似被$N" HIR "这惊天动地的一招吸个一丝不剩，一派生机尽绝，\n"
                               "死亡和肃杀的骇人味儿。只听得轻轻的一声响，那道弯弯的刀光却还在，又弯弯地一转。然后美如月光的刀气消失了，\n"
                               "所有的声音都沉寂，所有的动作都停顿。$N" HIR "还是像一瞬前那么样静静地站在那里，好像根本没有动过。可是$N" 
                               HIR "手里的" + weapon->name() + HIR "已经在滴着血。\n" NOR;
                        damage = -1;
                } else
                {
                        me->start_busy(4);
                        me->add("neili", -600);
                        damage = me->query_skill("blade");
                        damage *= 3;
                        msg += HIR "结果$p" HIR "闪避不及，只觉得"
                                                   "一股冰寒的刀气掠过全身，$n全身顿时鲜血淋漓！\n" NOR;
						message_combatd(msg, me, target); 
                }
        } else
        {
                me->start_busy(5);
                me->add("neili", -300);
                msg += CYN "可是$p" CYN "识破了$P"
                       CYN "这一招，斜斜一跃避开。\n" NOR;
        }
        message_combatd(msg, me, target);

        if (damage < 0)
                target->die(me);

        return 1;
}


