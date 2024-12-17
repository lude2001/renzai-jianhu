// powerup.c ���๦����

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

string query_name() { return "����"ZJBR"֮��"; }
string *pfm_type() { return ({ "force", }); }

int exert(object me, object target)
{
	int skill;

	if( target != me )
		return notify_fail("��ֻ�������Լ���ս������\n");

	if( (int)me->query("neili") < 200)
		return notify_fail("�������������\n");

	if( (int)me->query_temp("powerup"))
		return notify_fail("���Ѿ����˹����ˡ�\n");

	skill = me->query_skill("force");

	message_vision(HIR "$N" HIR "���һ����ȫ�������ڽڱ��죬һ��"
		       "Ѹ�͵������������ɢ������"NOR"\n", me);

	//me->add_temp("apply/unarmed_damage", skill / 15);
	me->add_temp("apply/attack", (skill / 3) + 50);
	me->add_temp("apply/parry", skill / 3);
	me->add_temp("apply/dodge", skill / 3);
	me->set_temp("powerup", 1);
	me->add("neili", -100);

	me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill / 3 :), skill);

	if (me->is_fighting()) me->start_busy(3);

	return 1;
}

void remove_effect(object me, int amount)
{
        if (!me) return;

	if ((int)me->query_temp("powerup"))
	{
	        //me->add_temp("apply/unarmed_damage", -amount/5);
		me->add_temp("apply/attack", -amount - 50);
		me->add_temp("apply/parry", -amount);
		me->add_temp("apply/dodge", -amount);
		me->delete_temp("powerup");
		tell_object(me, "������������������ϣ��������ջص��\n");
	}
}