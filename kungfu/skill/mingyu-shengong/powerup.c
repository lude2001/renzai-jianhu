// powerup.c 

#include <ansi.h>

inherit F_CLEAN_UP;
string query_name() { return "ڤ��"ZJBR"ս��"; }
void remove_effect(object me, int amount);

int exert(object me, object target)
{
	int skill;

	if ( !wizardp(this_player()) && (me->query("family/family_name") != "�ƻ���"))
		return notify_fail("�㲻���ƻ������Ӳ���ʹ��ڤ����.\n
		 		    ڤ���񹦲�����, ���ƻ������Ӳ���, �治֪��������ôѧ���!\n
				    Ҫ������λ����֪������ɲ���.\n");
	if( target != me ) 
		return notify_fail("��ֻ����ڤ�����������Լ���ս������\n");

	if( (int)me->query("neili") < 100  ) 
		return notify_fail("�������������\n");
	if( (int)me->query_temp("powerup") ) 
                 return notify_fail("���Ѿ����˹����ˡ�\n");

	skill = me->query_skill("force");
	me->add("neili", -100);
	me->receive_damage("qi", 0);

	message_vision(
	HIM "$N΢һ��������ڤ���񹦣�������������Χ��, ��ȫ��Ǳ�ܾ������𡣢�\n" NOR, me);

	me->add_temp("apply/attack", skill/3);
	me->add_temp("apply/dodge", skill/3);
	me->set_temp("powerup", 1);
     me->set_temp("zjb_yihua", 1);

	me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill/3 :), skill);

	if( me->is_fighting() ) me->start_busy(3);

	return 1;
}

void remove_effect(object me, int amount)
{
   if ( (int)me->query_temp("powerup") ) {
	me->add_temp("apply/attack", - amount);
	me->add_temp("apply/dodge", - amount);
	me->delete_temp("powerup");
      me->delete_temp("zjb_yihua");
	tell_object(me, "���ڤ����������ϣ��������ջص��\n");}
}