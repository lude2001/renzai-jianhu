// fumo by greenwc
// fomo by yushu修改
#include <ansi.h>
inherit F_SSERVER;
string query_name() { return "御剑" ZJBR "伏魔"; }
int perform(object me, object target)
{
        object weapon;
        int i, j, e, damage, damagea;
        weapon = me->query_temp("weapon");

        if (!target)
                target = offensive_target(me);

        if (!target || !target->is_character() || target->is_corpse() || target == me)
                return notify_fail("你要攻击谁？\n");

        if (!me->is_fighting())
                return notify_fail("你们没有在打架！\n");

        if (me->query("family/family_name") != "蜀山派")
                return notify_fail("不是蜀山的不能用「御剑伏魔」！\n");

        if ((int)me->query("max_neili") < 20000)
                return notify_fail("你的内功太差。\n");

        if ((int)me->query_skill("martial-cognize") < 300)
                return notify_fail("你的武学修养不足。\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("你的内力不足！\n");

        i = (int)me->query_skill("sword");
        j = (int)target->query_skill("dodge");
        e = i + j + i / 2;
        if (i < 80)
                return notify_fail("你的剑法级别还不够，使用这一招会有困难！\n");

        message_vision(HIC "\n$N口中默念御剑口诀，手中" + weapon->name() + NOR + HIC "顿时间霞光四射，一招「御剑伏魔」直斩$n！\n\n"

                           HIR " ==================>>>>>>>>>>>>>>>\n\n" NOR HIR " ==================>>>>>>>>>>>>>>>\n\n\n" NOR,
                       me, target);

        if (random(e) > j)
        {
                damage = i + random((int)me->query("max_neili")) / 10;
                damagea = i + random((int)me->query("max_neili")) / 20;
                target->receive_damage("jing", damage);
                target->receive_damage("qi", damagea);
                me->receive_damage("jing", 50);
                me->add("neili", -100);
                me->receive_damage("qi", 50);
                COMBAT_D->report_status(target);
                COMBAT_D->report_sen_status(target);
                if (!target->is_fighting(me))
                {
                        if (living(target))
                        {
                                if (userp(target))
                                        target->fight_ob(me);
                                else
                                        target->kill_ob(me);
                        }
                }
        }
        me->start_busy(2);
        return 1;
}
