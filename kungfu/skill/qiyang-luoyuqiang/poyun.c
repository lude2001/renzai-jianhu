// Cracked by Roath

// Ansi 99.12
#include <ansi.h>

inherit F_SSERVER;
string query_name() { return "����" ZJBR "����"; }
int perform(object me, object target)
{
        int ap, dp, damage, chance;
        string msg;
        object weapon;

        if (!target)
                target = offensive_target(me);

	    if (! objectp(weapon = me->query_temp("weapon")) ||
	      (string)weapon->query("skill_type") != "club")
		return notify_fail("��ʹ�õ��������ԡ�\n");
		
        if (!target || !target->is_character() || target->is_corpse() || target == me)
                return notify_fail("��Ҫ��˭ʩչ��������������\n");

        if (!me->is_fighting())
                return notify_fail("������������ֻ����ս����ʹ�ã�\n");

        if (me->query("family/family_name") != "�ϻ���" && !lv_fa(me,"�ϻ���") && !wizardp(me))
                return notify_fail("���Ǻϻ��ڵĲ����á�������������\n");

        if (me->query_skill("qiyang-luoyuqiang", 1) < 600)
		return notify_fail("�����������ǹ��Ϊ������Ŀǰ����ʹ������������\n");

        if ((int)me->query("max_neili") < 500)
                return notify_fail("�������������\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("����������㣡\n");

        if ((int)me->query("jing") < 500)
                return notify_fail("��ľ����㣬û����ʩ���⹦��\n");

        msg = CYN "\n$N����ȫ������,�ƿ��ܳ����п����谭���ڿն��𣬽����б���Ѫ֮��������ǹ�������" + weapon->name() + "�͵Ĵ���$n��\n" NOR;
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

                msg += CYN "���$n��$N�ġ���������������������ɳ����ɣ�������������ѪҲ��ȼ��������\n" NOR;
        }

        else
                msg += "����$n����η�壬�����ڹ�����Ӳ����������һ�С�\n" NOR;
        message_vision(msg, me, target);

        if (damage > 0)
                COMBAT_D->report_status(target);

        me->add("neili", -2000 - me->query("jiali"));
        me->start_busy(3);
        return 1;
}
