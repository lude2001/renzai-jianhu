// ���ɷ�

#include <ansi.h>

string query_name() { return "����"ZJBR"����"; }

int perform(object me)
{
	int skill;
	string msg;
	object weapon;
	
	if (objectp(weapon = me->query_temp("weapon")) &&
	    weapon->query("skill_type") != "staff" &&
	    weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õı������ԣ���ôʹ�á����ɼ�������\n");
	
	if( objectp(weapon = me->query_temp("weapon"))&&weapon->query("magic/skill/shedao-qigong-chang1")){
		if ((int)me->query_skill("shedao-qigong", 1) < 60)
			return notify_fail("����ߵ��湦������죬����ʹ�ó��ɷ���\n");
		if ((int)me->query("neili") < 300)
			return notify_fail("���Ѿ����þ�ƣ���ߣ����������ˡ�\n");
		if ((int)me->query_temp("chang") >= 200)
			return notify_fail("���Ѿ�����̫���ˣ������ٳ��ˡ�\n");
		me->add("neili", -200);

		message_combatd(HIR "ֻ��$N" HIR "���������дʣ����"
				"֮���书�����"NOR"\n", me);
		me->add_temp("apply/attack", 1);
		me->add_temp("apply/dodge", 1);
		me->add_temp("apply/defense", 1);
		me->add_temp("chang", 1);
		
		
	}else{
		if (! me->is_fighting())
		return notify_fail("���ɷ�ֻ����ս����ʹ�á�\n");

		if ((int)me->query_skill("shedao-qigong", 1) < 60)
			return notify_fail("����ߵ��湦������죬����ʹ�ó��ɷ���\n");

		if ((int)me->query("neili") < 300)
			return notify_fail("���Ѿ����þ�ƣ���ߣ����������ˡ�\n");

		if ((int)me->query_temp("chang") >= 30)
			return notify_fail("���Ѿ�����̫���ˣ������ٳ��ˡ�\n");

		skill = me->query_skill("force");

		me->add("neili", -200);

		message_combatd(HIR "ֻ��$N" HIR "���������дʣ����"
				"֮���书�����"NOR"\n", me);

		me->add_temp("apply/attack", 1);
		me->add_temp("apply/dodge", 1);
		me->add_temp("apply/defense", 1);
		me->add_temp("chang", 1);
		}
		
	
		return 1;
}
