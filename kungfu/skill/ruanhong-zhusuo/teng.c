// tengshe.c ���߾�

#include <ansi.h>
#include <combat.h>

string name(){ return WHT "���߾�" NOR; }
string query_name() { return "���߾�"; }
inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ����ս���жԶ���ʹ�á�\n");

	if (userp(me) && ! me->query("can_perform/xiewei-bian/tengshe"))
		return notify_fail("�㻹����ʹ����һ�У�\n");

        if( !objectp(weapon=me->query_temp("weapon")) ||
              weapon->query("skill_type") != "whip" )
                return notify_fail("��ʹ�õ��������ԣ��޷�ʩչ" + name() + "��\n");

        if ((int)me->query_skill("ruanhong-zhusuo", 1) < 60)
                return notify_fail("�����������������죬�޷�ʩչ" + name() + "��\n");

        if( me->query("neili")<200 )
                return notify_fail("��������������޷�ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("whip") != "ruanhong-zhusuo")
                return notify_fail("��û�м��������������޷�ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = WHT "$N" WHT "��Ȼʩչ�������ߡ�������������һ����" + weapon->name() +
              WHT "��ʱ�εص�����ͬ����һ����ȻϮ��$n" + WHT "��\n" NOR;

        ap = me->query_skill("whip") + me->query_skill("force");
        dp = target->query_skill("parry") + target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = me->query_skill("whip");
                me->add("neili", -150);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           HIR "Ȼ��$n" HIR "δ�ܿ�����ͼ��һ���Һ���"
                                           + weapon->name() + HIR "�޶���û�����ڰ��"
                                           "����ʱ����������\n" NOR);
        } else
        {
                me->add("neili", -100);
                me->start_busy(3);
                msg += CYN "����$p" CYN "����������������ס��"
                       CYN "$P" CYN "�����Ī���һ����\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}