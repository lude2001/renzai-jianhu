// Cracked by Roath

// Ansi 99.12
#include <ansi.h>

inherit F_SSERVER;
string query_name() { return "��ˮ" ZJBR "�޺�"; }
int perform(object me, object target)
{
        int ap, dp, damage, chance;
        string msg;
        object weapon;

        if (!target)
                target = offensive_target(me);

        if (!target || !target->is_character() || target->is_corpse() || target == me)
                return notify_fail("��Ҫ��˭ʩչ����ˮ�޺ۡ���\n");

        if (!me->is_fighting())
                return notify_fail("����ˮ�޺ۡ�ֻ����ս����ʹ�ã�\n");

        if (me->query("family/family_name") != "��ɽ��" && !lv_fa(me,"��ɽ��"))
                return notify_fail("������ɽ�Ĳ����á���ˮ�޺ۡ���\n");

        if ((int)me->query("max_neili") < 500)
                return notify_fail("�������������\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("����������㣡\n");

        if ((int)me->query("jing") < 500)
                return notify_fail("��ľ����㣬û����ʩ���⹦��\n");

        if ((int)me->query_skill("songhe-sword", 1) < 800)
                return notify_fail("����ɺ׽�����Ϊ��������ʹ����һ�л������ѣ�\n");

        msg = CYN "\n$N����ζ��缲�磬�Կ�����ǧ�߷������ٶȣ�ֱ��$n��\n" NOR;
        ap = me->query("combat_exp");
        ap = ap;
        dp = target->query("combat_exp");
        if (random(ap / 2) > dp)
        {
                damage = me->query_skill("sword") * 3 + me->query("jiali");
                if (damage > 10000)
                        damage = target->query("max_qi") / 5;
                target->receive_damage("qi", damage);
                target->receive_wound("qi", damage / 3);
                target->start_busy(random(4) + 2);
                msg += CYN "���$n��$N�ġ���ˮ�޺ۡ�����������\n" NOR;
        }

        else
                msg += "���Ǳ�$n�㿪�ˡ�\n" NOR;
        message_vision(msg, me, target);
        if (damage > 0)
                COMBAT_D->report_status(target);

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
        me->add("neili", -80 - me->query("jiali"));
        me->start_busy(3);
        return 1;
}