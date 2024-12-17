// xiang.c �������

#include <ansi.h>

inherit F_SSERVER;
void remove_effect(object me, int aamount);
string query_name() { return "����"ZJBR"����"; }
string *pfm_type() { return ({ "strike", }); }

int perform(object me, object target)
{
	string msg;
	int ap, dp;
	int count;
	int i;
	int sign = 0;
	int unarmed_lev = 0;//ȭ�ż��ܵȼ�
	
	object hands;
 
	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}
    
    
	if (objectp(hands = me->query_temp("armor/hands")) && hands->query("magic/skill/dragon-strike-xiang"))
	{
	    sign = 1;
	    if (me->query("neili") < 5400)
	        return notify_fail("����������㡣\n");
	    
	    if (me->query("qi") < 1800)
	        return notify_fail("�����Ѫ���㡣\n");
	}
	
	if (! target || ! me->is_fighting(target))
		return notify_fail("��������졹ֻ����ս���жԶ���ʹ�á�\n");
 
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("��������졹ֻ�ܿ���ʹ�á�\n");
		
	if (me->query("max_neili") < 2000)
		return notify_fail("���������Ϊ���������޷�ʩչ��������졹��\n");

	if ((int)me->query("neili") < 500)
		return notify_fail("�������������\n");

	if ((int)me->query("qi") < 800)
		return notify_fail("����������ڲ�����\n");

	if ((int)me->query_skill("dragon-strike", 1) < 150)
		return notify_fail("��Ľ���ʮ���ƻ�򲻹����޷�ʹ�á�������졹��\n");

	if ((int)me->query_skill("force") < 300)
		return notify_fail("����ڹ���Ϊ�������޷�ʹ�á�������졹��\n");

	if (me->query_skill_prepared("strike") != "dragon-strike")
		return notify_fail("������û��׼��ʹ�ý���ʮ���ƣ��޷�ʹ�á�������졹��\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");
	
	unarmed_lev = me->query_skill("unarmed")/3 /2 ;
	//me->add_temp("str", unarmed_lev * 2);
	//me->set_temp("xiang", 1);
	//me->start_call_out((: call_other, __FILE__, "remove_effect", me, unarmed_lev * 2:), 5);
		
	msg = HIY "$N" HIY "����һ��������ǰһ����˫����Ȼ�������ͷ׶���������һ�����������ھ���֮�ϣ�"NOR"\n";
	ap = me->query_skill("strike") + me->query("str") * 10;
	dp = target->query_skill("parry") + target->query("dex") * 6;
	if (ap / 2 + random(ap) > dp)
	{
		count = ap / 9;
		msg += HIR "$n" HIR "���$P" HIR "����ɽ�������ƣ���ȫ�޷��ֵ���Ψ���˺�"NOR"\n";
	} else
	{
		msg += HIC "$n" HIC "����Ӧս���߾����ܻ���$P" HIC "�⼸�ơ�"NOR"\n";
		count = 0;
	}

	message_vision(msg, me, target);
	me->add_temp("apply/attack", count*3);
	
	
	
	if (sign)
	{
    	me->add("neili", -2500);
    // 	me->add("qi", -1800);
	    for (i = 0; i < 18; i++)
	    {
    		if (! me->is_fighting(target))
    			break;
    		if (random(5) < 2 && ! target->is_busy())
    			target->start_busy(1);
    
    		COMBAT_D->do_attack(me, target, 0, 0);
	    }
	}
	else
	{
    	me->add("neili", -300);
    	me->add("qi", -100);    // Why I don't use receive_damage ?
    				// Becuase now I was use it as a cost
    	for (i = 0; i < 6; i++)
    	{
    		if (! me->is_fighting(target))
    			break;
    		if (random(5) < 2 && ! target->is_busy())
    			target->start_busy(1);
    
    		COMBAT_D->do_attack(me, target, 0, 0);
    	}
	}
	target->interrupt_me(target, 1);

	me->start_busy(1 + random(5));
	me->add_temp("apply/attack", -count*2);

	return 1;
}

void remove_effect(object me, int aamount)
{
	if ((int)me->query_temp("xiang"))
	{
		me->add_temp("str", -aamount);
		me->delete_temp("xiang");
		tell_object(me, "ƴ���ľ��Ķ�û�˵����ɡ�\n");
	}
}