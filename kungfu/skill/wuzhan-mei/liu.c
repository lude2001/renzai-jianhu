// liu.c
// ������Ӱ liu

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill;
	string msg;
	int ap, dp;
	int count;
	int i;
        object weapon;


		if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

        if (userp(me) && ! me->query("can_perform/wuzhan-mei/liu")) 
                return notify_fail("�㻹û���ܹ�����ָ�㣬�޷�ʩչ��������Ӱ����\n"); 
                
        if((skill = me->query_skill("wuzhan-mei",1)) < 100)
                return notify_fail("�����չ÷�����������죬�޷�ʹ�á�������Ӱ����\n");

        if( !target ) target = offensive_target(me);

        if( !target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("��������Ӱ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if(me->query("neili") < 400 )
                return notify_fail("��Ŀǰ���������㣬�޷�ʩչ��������Ӱ����\n");

        if(!(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "wuzhan-mei")
                return notify_fail("�������ʹ�ý�ʱ����ʹ����������Ӱ����\n");


		msg = HIY "$N" HIY "�����Ҷ����ó�һƬ��⣬ʩչ�����ž�ѧ��������Ӱ����"NOR"\n";
		ap = me->query_skill("sword");
		dp = target->query_skill("parry");

		if (ap / 2 + random(ap * 2) > dp)
		{
			msg += HIC "���$p" HIC "��$P" HIC
			       "���˸����ֲ������������˲�Ͼ��"NOR"\n";
			count = ap / 2;
			me->add_temp("apply/attack", count);

		} else
		{
			msg += HIC "$n" HIC "��$N" HIC "�⼸���������������Ҵ��⣬С��Ӧ����"NOR"\n";
			count = 0;
		}
		
		message_combatd(msg, me, target);
		me->add("neili", -200);

		for (i = 0; i < 4; i++)
		{
			if (! me->is_fighting(target))
				break;
			COMBAT_D->do_attack(me, target, weapon, 0);
		}

		me->add_temp("apply/attack", -count);
		me->start_busy(1 + random(3));

		return 1;
/*
        for(int i=0;i<4;i++)
        {
                // COMBAT_D->do_attack(me,target,TYPE_QUICK);
                COMBAT_D->do_damage(me,target, WEAPON_ATTACK, damage, 50);
        }
        
        if(random(target->query("force")) < me->query("force")/2)
        {
                target->apply_condition("weapon_bleeding", 5+random(3));
        }
        

        me->start_busy(3);
        return 1;*/
}
