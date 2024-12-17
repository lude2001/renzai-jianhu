//zhanqi by yushu 2001.2
#include <ansi.h>

inherit F_CLEAN_UP;

string query_name() { return "���"ZJBR"ս��"; }

void remove_effect(object me, int amount);

int exert(object me, object target)
{
	int skill;

	if (target != me)
		return notify_fail("��ֻ�������Լ���ս������\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("�������������\n");

	if ((int)me->query_temp("zhanqi"))
		return notify_fail("���Ѿ����˹����ˡ�\n");

	skill = me->query_skill("force");
	me->add("neili", -100);
	me->receive_damage("qi", 0);

    message_vision(HIM "$N΢һ����������ɽ�ķ���һ�����ս���ӵ���ֱ���춥��\n" NOR, me);

	me->add_temp("apply/attack", skill * 2 / 3);
	me->add_temp("apply/parry", skill / 3);
	me->add_temp("apply/dodge", skill / 3);
	me->set_temp("zhanqi", 1);

	me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill :), skill);

	if (me->is_fighting()) me->start_busy(3);

	return 1;
}

void remove_effect(object me, int amount)
{
    	if ((int)me->query_temp("powerup"))
		me->add_temp("apply/attack", - (amount * 2 / 3));
		me->add_temp("apply/parry", - (amount / 3));
		me->add_temp("apply/dodge", - (amount / 3));
		me->delete_temp("zhanqi");
		tell_object(me, HIM"������ս��ѭ��һ������ϣ��������ջص��\n"NOR);
}
