// fumo by greenwc
// fomo by yushu�޸�
#include <ansi.h>
inherit F_SSERVER;
string query_name() { return "����" ZJBR "��ħ"; }
int perform(object me, object target)
{
        object weapon;
        int i, j, e, damage, damagea;
        weapon = me->query_temp("weapon");

        if (!target)
                target = offensive_target(me);

        if (!target || !target->is_character() || target->is_corpse() || target == me)
                return notify_fail("��Ҫ����˭��\n");

        if (!me->is_fighting())
                return notify_fail("����û���ڴ�ܣ�\n");

        if (me->query("family/family_name") != "��ɽ��")
                return notify_fail("������ɽ�Ĳ����á�������ħ����\n");

        if ((int)me->query("max_neili") < 20000)
                return notify_fail("����ڹ�̫�\n");

        if ((int)me->query_skill("martial-cognize") < 300)
                return notify_fail("�����ѧ�������㡣\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("����������㣡\n");

        i = (int)me->query_skill("sword");
        j = (int)target->query_skill("dodge");
        e = i + j + i / 2;
        if (i < 80)
                return notify_fail("��Ľ������𻹲�����ʹ����һ�л������ѣ�\n");

        message_vision(HIC "\n$N����Ĭ�������ھ�������" + weapon->name() + NOR + HIC "��ʱ��ϼ�����䣬һ�С�������ħ��ֱն$n��\n\n"

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
