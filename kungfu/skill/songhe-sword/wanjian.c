#include <ansi.h>
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
string query_name() { return "�򽣾�"; }
int perform(object me, object target)
{
        object weapon;
        int i, j, k, u, damage;
        weapon = me->query_temp("weapon");
        if (!target)
                target = offensive_target(me);
        if (!target || !target->is_character() || target->is_corpse() || target == me)
                return notify_fail("��Ҫ����˭��\n");
        if (!me->is_fighting())
                return notify_fail("����û���ڴ�ܣ�\n");

        if (me->query("family/family_name") != "��ɽ��" && !lv_fa(me,"��ɽ��"))
                return notify_fail("������ɽ�Ĳ����á��򽣾�����\n");

        if ((int)me->query("max_neili") < 1500)
                return notify_fail("�������̫�\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("����������㣡\n");

        if ((int)me->query("jing") < 200)
                return notify_fail("��ľ����㣬û����ʩ���⹦��\n");

        if ((int)me->query_skill("zuixian-steps", 1) < 120)
                return notify_fail("����������²��ȼ�����������ʹ����һ�У�\n");
        k = (int)me->query_skill("sword");
        j = (int)target->query_skill("dodge");
        if (k < 100)
                return notify_fail("��Ľ������𻹲�����ʹ����һ�л������ѣ�\n");
        u = 1 + k / 50;
        if (u > 10)
                u = 10;
                
        message_vision(HIC "\n$N��������һ����\n" NOR, me, target);
        message_vision(HIW "\n�򡫡�����������������\n" NOR, me, target);
        message_vision(HIC "\nһɲ�Ǽ�ǧ�򽣹��ƿն�������������$n\n" NOR, me, target);
        for (i = 0; i <= u; i++)
        {
                COMBAT_D->do_attack(me, target, weapon, TYPE_REGULAR, HIC "\nһɲ�Ǽ�ǧ�򽣹��ƿն�������������$n\n" NOR);
                if (random(k + j) > j)
                {
                        message_vision(HIY "\n$nһ������������һ��\n" NOR, me, target);
                        damage = k + random(k);
                        target->receive_damage("qi", damage);
                        target->receive_wound("qi", damage / 2);
                        COMBAT_D->report_status(target);
                        //me->receive_damage("jing", 100);
                        me->add("neili", -100);
                }
                else
                {
                        message_vision(HIY "\n$n�����������ò����ױܿ���һ�ֽ���\n" NOR, me, target);
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
        if (weapon->query("magic/skill/songhe-sword"))//ӵ�к���ר����ʯ�ļӳ�
        me->start_busy(2);
        else
        me->start_busy(3);
        
        me->add("shushan/wanjian_perform", -1);
        return 1;
}
