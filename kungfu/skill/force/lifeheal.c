// lifeheal.c

#include <ansi.h>

int exert(object me, object target)
{
	string force;

	if (! target || target == me)
		return notify_fail("��Ҫ������Ϊ˭���ˣ�\n");

	if (me->is_fighting() || target->is_fighting())
		return notify_fail("ս�����޷��˹����ˣ�\n");

	if (target->query("not_living"))
		return notify_fail("�㲻�ܸ�" + target->name() + "���ˡ�\n");

	force = me->query_skill_mapped("force");
	if (! force)
		return notify_fail("����뼤��һ���ڹ������������ˡ�\n");

	if ((int)me->query_skill(force,1) < 50)
		return notify_fail("���" + to_chinese(force) + "�ȼ�������\n");

	if ((int)me->query("max_neili") < 300)
		return notify_fail("���������Ϊ������\n");

	if ((int)me->query("neili") < 150)
		return notify_fail("�����ڵ�����������\n");

	if ((int)target->query("eff_qi") >= ((int)target->query("max_qi")+target->query_gain_qi()))
		return notify_fail( target->name() +
			"����û�����ˣ�����Ҫ���˹����ƣ�\n");

	if ((int)target->query("eff_qi") < (int)target->query("max_qi") / 5)
		return notify_fail( target->name() +
			"�Ѿ����˹��أ����ܲ�����������𵴣�\n");

	message_vision(
		HIY "$N������������" + to_chinese(force) +
		"������������$n���ģ������ؽ���������$n����....\n"
		HIW "���˲��ã�$N��ͷ��ð������ĺ��飬$n�³�һ"
		"����Ѫ����ɫ������������ˡ�"NOR"\n",
		me, target );

	target->receive_curing("qi", 10 + (int)me->query_skill("force") / 2);
	target->add("qi", 10 + (int)me->query_skill("force") / 3);
	if ((int)target->query("qi") > (int)target->query("eff_qi"))
		target->set("qi", (int)target->query("eff_qi"));

	me->add("neili", -150);
	me->start_busy(1);
	return 1;
}
