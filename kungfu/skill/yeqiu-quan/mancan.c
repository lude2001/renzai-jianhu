// xue.c ��������

#include <ansi.h>

inherit F_SSERVER;
 
string query_name() { return "����"ZJBR"����"; }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int i;
 
	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("������������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
		
 
	if (objectp(weapon = me->query_temp("weapon")))
		return notify_fail("������������������֣�\n");

	/*if ((int)me->query("neili") < 100)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 80)
		return notify_fail("����ڹ���򲻹���\n");
*/
	if ((int)me->query_skill("yeqiu-quan", 1) < 1)
		return notify_fail("���Ұ��ȭ�������ң��޷�ʹ�ú���������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIW "$N" HIW "ʹ��������������������������ʽ��ò��岻����"NOR"\n";
	message_combatd(msg, me);
	//me->add("neili", -100);
	//ֻ���Լ���ʦ��npc����ɱЧ��
 if (target->query_temp("quester")==getuid(me)&&me->query("combat_exp")<1000000)//ʦ�Ź���ֱ����
 {
 target->receive_wound("qi", 5, me);
  target->die(me);
  	message_combatd("���$Nһ��������$n��Ѫ��ֹ������������\n", me);
  }
  else
  {
  	target->receive_wound("qi", 1, me);
  	message_combatd("$Nʹ��Ұ��ȭ���������������Ե���û���κ��˺���\n", me);
  }/*
	for (i = 0; i < 5; i++)
	{
		if (! me->is_fighting(target))
			break;
		COMBAT_D->do_attack(me, target, weapon, 0);
	}*/

	me->start_busy(1 + random(4));
	return 1;
}
