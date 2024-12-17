// powerup.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

string query_name() { return "����"ZJBR"֮��"; }
string *pfm_type() { return ({ "force", }); }

int exert(object me, object target)
{
	int skill;

	if (target != me)
		return notify_fail("��ֻ���ö����ķ��������Լ���ս������\n");

	if ((int)me->query("neili") < 150)
		return notify_fail("�������������\n");

	if ((int)me->query_temp("powerup"))
		return notify_fail("���Ѿ����˹����ˡ�\n");

	skill = me->query_skill("force");
	me->add("neili", -50);
	me->receive_damage("qi", 0);
	message_combatd(HIY "$N" HIY "����������������ķ���"
			"�����Գ�һ�����֮�⣬�ľ����߷緶��"NOR"\n", me);
// 	me->add_temp("apply/attack", skill / 3);
// 	me->add_temp("apply/defense", skill / 3);
	me->add_temp("apply/attack", skill * 2);
	me->add_temp("apply/defense", skill / 2);
	me->add_temp("apply/parry", skill / 2);
	me->add_temp("apply/dodge", skill / 2);
	//me->add_temp("apply/armor", skill * 2);
	me->set_temp("powerup", 1);

	me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill * 2 :), skill);

	if (me->is_fighting()) me->start_busy(3);
	return 1;
}

void remove_effect(object me, int amount)
{
	if (me->query_temp("powerup"))
	{
		me->add_temp("apply/attack", -amount);
		me->add_temp("apply/defense", -amount / 4);
		me->add_temp("apply/parry", -amount / 4);
    	me->add_temp("apply/dodge", -amount / 4);
	   // me->add_temp("apply/armor", -amount);
		me->delete_temp("powerup");
		tell_object(me, "��Ķ����ķ�������ϣ��������ջص��\n");
	}
}
