// ����ս�졣by ����ҹ��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "����ս��" NOR; }
string query_name() { return "����"ZJBR"ս��"; }
int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( me->query_temp("weapon") || me->query_temp("secondary_weapon") )
                return notify_fail(name() + "ֻ�ܿ���ʹ�á�\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("���ڹ���Ϊ����������ʩչ" + name() + "��\n");

        if( me->query("max_neili")<3000 )
                return notify_fail("��������Ϊ����������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("taisu-moon", 1) < 200)
                return notify_fail("��̫������ʽ��򲻹�������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("cuff") != "taisu-moon")
                return notify_fail("��û�м���̫������ʽ������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("cuff") != "taisu-moon")
                return notify_fail("��û��׼��̫������ʽ������ʩչ" + name() + "��\n");

        if( me->query("neili")<1000 )
                return notify_fail("��������������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        // ��һȭ���жϱ������ж��Ʒ�
		ap = me->query_skill("cuff") + me->query("str") * 25;
		dp = target->query_skill("dodge") + target->query("dex") * 10;
        damage = me->query_skill("cuff");
        damage+= me->query("jiali");

        message_combatd(sort_msg(HIM "\n��Ȼ��$N" HIW "���μ�������ȭ���գ������ſ���ȭ�����ƾ���ʱ��������"
                     "��$n" HIW "��ȥ������̫������ʽ��" NOR + HIY "����ս���һʽ" NOR
                     + HIW "��һ�У�����ȭ��֮��˵���㵽���Ʋ��ɵ���$n" HIW
                     "��ȥ����\n" NOR), me, target);
        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target,UNARMED_ATTACK, damage, 65,
                                          HIR "$p" HIR "һ�㣬ֻ��$P" HIR "����"
                                          "һ�����ѻ����Լ���ǰ����������������"
                                          "�����С�\n:����@?");

                message_combatd(msg, me, target);

        } else
        {
                msg = HIC "$p" HIC "�ھ�ӿ��������Ӧ�ԣ��������࣬$P"
                      HIC "ȭ������ţ�뺣������жȥ��\n" NOR;
                message_combatd(msg, me, target);
        }

        // �ڶ�ȭ���жϸ��ǣ�ȭ��
        ap = me->query_skill("cuff") + me->query("con") * 25;
        dp = target->query_skill("parry") + target->query("dex") * 10;

        message_combatd(sort_msg(HIW "\n$N" HIW "һ�мȳ���������Ȼ������$n" HIW "������֮��"
                     "����ȭ���գ�ǰȭ��ͼ��Ӱ���������Ϊ��" NOR + HIY "����"
                     "ս��ڶ�ʽ" NOR + HIW "����ȭ������ŭ����ӿ���Ʋ��ɵ�����ʱ$n"
                     HIW "�����ƿ�������  ��\n" NOR), me, target);
        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK,damage, 65,
                                           HIR "ֻ��$p" HIR "һ���Һ�����$P" HIR
                                           "һȭ�������䣬�����꿦�ꡱ���˺ü�����"
                                           "�ǡ�");

                message_combatd(msg, me, target);
        } else
        {
                msg = HIC "$p" HIC "����˫�ۣ�����Ӧ�ԣ��������࣬$P"
                      HIC "ȭ������ţ�뺣������жȥ��\n" NOR;
                message_combatd(msg, me, target);
        }

        // ���һȭ���ж�����+�������Ӹ����У�
        ap = me->query_skill("cuff") + (me->query("dex")+me->query("int")) * 25;
        dp = target->query_skill("force") + target->query("dex") * 10;

        message_combatd(sort_msg(HIW "\n������$N" HIW "һ�����ȣ���ȭ���ٻӳ���ǰ��ȭ��δ��"
                     "������ȭ���϶�Ϊһ���ֹ���һ�С�" NOR + HIY "����ս�����ʽ" NOR
                     + HIW "����ȭ��������������ǰ�����"
                     "ȥ��$n" HIW "ֻ����Ѫ��ӿ����Ϣ���ǡ�\n" NOR), me, target);

        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK,damage, 75,
                                           HIR "���$p" HIR "����������$P" HIR
                                           "��ȭ����ʱ���ض��������ۡ������һ��"
                                           "����Ѫ��\n:����@?");

                message_combatd(msg, me, target);
                me->start_busy(1 + random(3));
                me->add("neili", -200-random(100));
                return 1;
        } else
        {
                msg = HIC "$p" HIC "�����о������������μ��ˣ�˲��Ʈ����"
                      "�ɣ��ѳ�$P" HIC "ȭ��֮�⡣\n" NOR;
                message_combatd(msg, me, target);
                me->start_busy(1 + random(3));
                me->add("neili", -200-random(100));
                return 1;
        }
        message_combatd(msg, me, target);
        return 1;
}
