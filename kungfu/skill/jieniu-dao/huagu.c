// /kungfu/skill/gu.c ���ǵ�
#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "���ǵ�"; }

int perform(object me, object target)
{
	int damage;
	string msg;

		damage = (int)me->query_skill("jieniu-dao", 1);

                damage = random(damage)*10;

	if( !target ) target = offensive_target(me);

	if( !target || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("�����ǵ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if( !objectp(me->query_temp("weapon")) )
		return notify_fail("�������ô��ʹ�á����ǵ�����\n");		

	if( (int)me->query_skill("jieniu-dao", 1) < 60 )
		return notify_fail("��Ľ�ţ����������죬����ʹ�á����ǵ���!\n");

	if( (int)me->query("neili", 1) < 300 )
		return notify_fail("����������̫��������ʹ�á����ǵ���!\n");

	msg = CYN "$NĬ���񹦣�ʹ�������ǵ���������ƽ�ƹ���$n��\n"NOR;

          if (me->query_skill("jieniu-dao") > target->query_skill("force")/3 )
	{
		me->start_busy(random(2));
		target->start_busy(random(3));

		target->receive_damage("qi", damage);
		target->receive_wound("qi", damage/3);
                me->add("neili", -damage/3);

		if( damage < 40 )
			msg += HIY"���$n��$Nһ��ն�У��ƺ�һ����\n"NOR;
        else if( damage < 80 )
			msg += HIY"���$n��$Nһ��ն�У����١���һ������������\n"NOR;
        else if( damage < 160 )
			msg += RED"���$n��$Nһ��ն�У���������������\n"NOR;
		else
			msg += HIR"���$n��$Nһ��ն�У���ǰһ�ڣ��˿�Ѫӿ������\n"NOR;
		
	}
	else 
	{
		me->start_busy(random(2));
		me->add("qi", -(damage/2));
		me->add("eff_qi", -(damage/5));
		msg += CYN"����$p������$P����ͼ������һת���ػ���ȥ��\n"NOR;
	}
	message_vision(msg, me, target);

	return 1;
}
