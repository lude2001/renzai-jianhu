#include <ansi.h>
#include <combat.h>

#define XIAN "��" HIY "���ֻ�ɽ" NOR "��"
string query_name() { return "���ֻ�ɽ"; }
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
                return notify_fail(XIAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "blade")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" XIAN "��\n");

    	if (me->query_skill("zuoyou-hubo", 1))
    	return notify_fail("���һ����ͺ��ҵ��������ݡ�\n");
	
        if ((int)me->query_skill("force") < 160)
                return notify_fail("����ڹ���򲻹�������ʩչ" XIAN "��\n");

        if ((int)me->query_skill("hujia-daofa", 1) < 500)
                return notify_fail("��ĺ��ҵ����������ң�����ʩչ" XIAN "��\n");

        if (me->query_skill_mapped("blade") != "hujia-daofa")
                return notify_fail("��û�м������ҵ���������ʩչ" XIAN "��\n");

        if ((int)me->query("neili") < 200)
                return notify_fail("�����������������ʩչ" XIAN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

    msg = HIY"�ƽ������װ
    ҹ���������â
    �ɷ���ʮ��δ��
    �ᵶ�����˰˻�
    ֻ��$N��������" + weapon->name() +  HIY "������ָ�죬����������������$N�ŷ�ȫ��������һ�߳�ǰ��������ʱ�����쵶��ϯ��˷�������Я���˷��ֻ�ɽ֮�Ƴ���$nϯ���ȥ����������֮������ʯ���ѣ���ľ�ݾ���
    ���硿-����¾�أ�
    ���֡�-������ɣ�
    ����-����߱а��
    ��ɽ��-����ɱ����
    ��������������
    ���о������
    ������-�����Ƽ�"NOR"��";

        ap = me->query_skill("blade") + me->query_skill("force");
        dp = target->query_skill("force");

        if (ap / 2 + random(ap / 2) > dp)
	{
	        	damage = ap / 2 + random(ap / 2);
                me->add("neili", -damage / 3);
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi",damage / 4 + random(damage / 4), me);
		msg +=                     HIR "$n" HIR "����������˸����ĵ�����"
                                           "һ���ҽУ��������������֣���Ѫ�Ĵ��罦��\n" NOR;
		me->start_busy(2);
        if (ap / 3 + random(ap / 2) > dp && ! target->is_busy())
                        target->start_busy(ap / 60 + 2);
	} else 
	{
		msg += CYN "$p" CYN "���һ����Ҳ���мܣ��������"
                       "�������ߣ��ܿ���$P" CYN "��һ�С�\n" NOR;
                me->add("neili", -150);
		me->start_busy(2);
	}
	message_combatd(msg, me, target);

	return 1;
}
