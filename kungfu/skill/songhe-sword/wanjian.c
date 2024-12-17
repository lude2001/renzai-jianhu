#include <ansi.h>
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
string query_name() { return "万剑决"; }
int perform(object me, object target)
{
        object weapon;
        int i, j, k, u, damage;
        weapon = me->query_temp("weapon");
        if (!target)
                target = offensive_target(me);
        if (!target || !target->is_character() || target->is_corpse() || target == me)
                return notify_fail("你要攻击谁？\n");
        if (!me->is_fighting())
                return notify_fail("你们没有在打架！\n");

        if (me->query("family/family_name") != "蜀山派" && !lv_fa(me,"蜀山派"))
                return notify_fail("不是蜀山的不能用「万剑决」！\n");

        if ((int)me->query("max_neili") < 1500)
                return notify_fail("你的内力太差。\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("你的内力不足！\n");

        if ((int)me->query("jing") < 200)
                return notify_fail("你的精神不足，没法子施用外功！\n");

        if ((int)me->query_skill("zuixian-steps", 1) < 120)
                return notify_fail("你的醉仙望月步等级不够，不能使用这一招！\n");
        k = (int)me->query_skill("sword");
        j = (int)target->query_skill("dodge");
        if (k < 100)
                return notify_fail("你的剑法级别还不够，使用这一招会有困难！\n");
        u = 1 + k / 50;
        if (u > 10)
                u = 10;
                
        message_vision(HIC "\n$N仰天大喝了一声：\n" NOR, me, target);
        message_vision(HIW "\n万～～～～剑～～～～决\n" NOR, me, target);
        message_vision(HIC "\n一刹那间千万剑光破空而来，劈面罩向$n\n" NOR, me, target);
        for (i = 0; i <= u; i++)
        {
                COMBAT_D->do_attack(me, target, weapon, TYPE_REGULAR, HIC "\n一刹那间千万剑光破空而来，劈面罩向$n\n" NOR);
                if (random(k + j) > j)
                {
                        message_vision(HIY "\n$n一个不慎，中了一剑\n" NOR, me, target);
                        damage = k + random(k);
                        target->receive_damage("qi", damage);
                        target->receive_wound("qi", damage / 2);
                        COMBAT_D->report_status(target);
                        //me->receive_damage("jing", 100);
                        me->add("neili", -100);
                }
                else
                {
                        message_vision(HIY "\n$n左跳右闪，好不容易避开了一轮剑雨\n" NOR, me, target);
                        //me->receive_damage("jing", 100);
                        me->add("neili", -100);
                }
        }
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
        if (weapon->query("magic/skill/songhe-sword"))//拥有胡家专属宝石的加成
        me->start_busy(2);
        else
        me->start_busy(3);
        
        me->add("shushan/wanjian_perform", -1);
        return 1;
}
