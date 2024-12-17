// Cracked by Roath

// Ansi 99.12
#include <ansi.h>

inherit F_SSERVER;
string query_name() { return "破云" ZJBR "腾阳"; }
int perform(object me, object target)
{
        int ap, dp, damage, chance;
        string msg;
        object weapon;

        if (!target)
                target = offensive_target(me);

	    if (! objectp(weapon = me->query_temp("weapon")) ||
	      (string)weapon->query("skill_type") != "club")
		return notify_fail("你使用的武器不对。\n");
		
        if (!target || !target->is_character() || target->is_corpse() || target == me)
                return notify_fail("你要对谁施展「破云腾阳」？\n");

        if (!me->is_fighting())
                return notify_fail("「破云腾阳」只能在战斗中使用！\n");

        if (me->query("family/family_name") != "合欢宗" && !lv_fa(me,"合欢宗") && !wizardp(me))
                return notify_fail("不是合欢宗的不能用「破云腾阳」！\n");

        if (me->query_skill("qiyang-luoyuqiang", 1) < 600)
		return notify_fail("你的七阳落雨枪修为不够，目前不能使用破云腾阳！\n");

        if ((int)me->query("max_neili") < 500)
                return notify_fail("你的内力不够！\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("你的内力不足！\n");

        if ((int)me->query("jing") < 500)
                return notify_fail("你的精神不足，没法子施用外功！\n");

        msg = CYN "\n$N引动全身阳气,破开周朝所有空气阻碍，腾空而起，将手中被气血之力激荡的枪身漫火的" + weapon->name() + "猛的刺向$n！\n" NOR;
        ap = me->query_skill("force");
        dp = target->query_skill("force");

        if (random(ap) > dp / 2)
        {
                damage = me->query_skill("club") * 3 + me->query_skill("qiang");

                if (damage > 20000)
                        damage = target->query("max_qi") / 5;

                target->receive_damage("qi", damage);
                target->receive_wound("qi", damage / 3);
                
                target->start_busy(random(4) + 2);

                if (target->query("eff_qi") < target->query("max_qi") / 4)
                target->die();

                msg += CYN "结果$n被$N的「破云腾阳」穿身而过，飞驰五丈，周身漫火，连气血也被燃烧起来！\n" NOR;
        }

        else
                msg += "但是$n毫不畏惧，运起内功护体硬生生挡上这一招。\n" NOR;
        message_vision(msg, me, target);

        if (damage > 0)
                COMBAT_D->report_status(target);

        me->add("neili", -2000 - me->query("jiali"));
        me->start_busy(3);
        return 1;
}
