// bafang.c �˷��ص�ʽ

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
 
string query_name() { return "�˷�"ZJBR"�ص�"; }
string *pfm_type() { return ({ "blade", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int count=0;
	int i,lianji,ap,dp;
	lianji = 4+ random(4);
 
	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("���˷��ص�ʽ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "blade")
		return notify_fail("����û����ʹʲô���˷��ص�ʽ����\n");

	if ((int)me->query("neili") < 200)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 100)
		return notify_fail("����ڹ���򲻹���\n");

	if ((int)me->query_skill("hujia-daofa", 1) < 100)
		return notify_fail("��ĺ��ҵ����������ң��޷�ʹ�á��˷��ص�ʽ����\n");

	if (me->query_skill_mapped("blade") != "hujia-daofa")
		return notify_fail("��û�м������ҵ������޷�ʹ�á��˷��ص�ʽ����\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");
	      //Ĭ��
ap = random(me->query_skill("blade"));
dp = target->query_skill("parry") / 2;

	msg = HIW "$N" HIW "����Գ�ۣ����е�" + weapon->name() +
	      HIW "�������£��仯Ī�⣬������$n" HIW "����Ҫ����"NOR"\n";
	      
           if (weapon->query("magic/skill/hujia-daofa"))//ӵ�к���ר����ʯ�ļӳ�
		{
			      //��ʯ��ǿ��Ч����
ap = random(me->query_skill("blade"))+me->query_skill("hujia-daofa");
dp = target->query_skill("parry") / 3;
lianji += 2;
count += me->query_skill("hujia-daofa", 1) / 6;//�ٵ���һ��count���൱��1/3
		tell_object(me,"ֻ��һ�����죬��о�"+weapon->name()+"�ϵ���ɫ��䱬����ǿ�ҵĹ�â����ʱ�԰˷��ص�ʽ�ĸ������\n");
		}
		
	if (ap > dp)
	{
		msg += HIY "$n" HIY "������ʵ���Ǳ��Ī�⣬���ɵ���"
		       "�����⣬��ʽ��ʱ����������"NOR"\n";
		count += me->query_skill("hujia-daofa", 1) / 6;
	} else
	{
		msg += HIC "$n" HIC "�ĵ�΢΢һ����������С�Ľ��С�"NOR"\n";
		count = 0;
	}

	message_combatd(msg, me, target);
	me->add("neili", -150);
	me->add_temp("apply/attack", count);

	for (i = 0; i < lianji; i++)
	{
		if (! me->is_fighting(target))
			break;
		if (random(3) == 1 && ! target->is_busy())
			target->start_busy(1);
		COMBAT_D->do_attack(me, target, weapon, 0);
	}

        if (weapon->query("magic/skill/hujia-daofa-daopo"))//ӵ�к���ר����ʯ�ļӳ�
        {
                	    int damage = ap;
                	    string msgs = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 25,
							   HIB "\n$n" HIB "����ҡ�μ䣬�о���"
							   + weapon->name() + HIB + 
							   "��һ��̹ǵĺ����������ڣ��������"
							   "һ����Ѫ��"NOR"\n");
							
						target->receive_damage("qi", damage / 2, me);
					   target->receive_wound("qi",
					   damage / 4 + random(damage / 4), me);
					   	message_sort(msgs, me, target);
            	        
        }
	me->add_temp("apply/attack", -count);
	if (weapon->query("magic/skill/hujia-daofa"))//ӵ�к���ר����ʯ�ļӳ�
	skill_cd(me,"bafang",1+random(6));//���һ��6�롣
	else
		me->start_busy(1 + random(6));
	return 1;
}
