// qimai.c ��������

#include <ansi.h>

inherit F_SSERVER;
 
string query_name() { return "����"ZJBR"����"; }
string *pfm_type() { return ({ "cuff", }); }

int perform(object me, object target)
{
	string msg;
	int ap, dp;
	int count;
	int i, busy_count = 0;
 
	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("���������ˡ�ֻ����ս���жԶ���ʹ�á�\n");
 
//	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
//		return notify_fail("���������ˡ�ֻ�ܿ���ʹ�á�\n");
		
	if (me->query("max_neili") < 2000)
		return notify_fail("���������Ϊ���������޷�ʩչ���������ˡ���\n");

	if ((int)me->query("neili") < 500)
		return notify_fail("�������������\n");

	if ((int)me->query("qi") < 800)
		return notify_fail("����������ڲ�����\n");

	if ((int)me->query_skill("qishang-quan", 1) < 150)
		return notify_fail("�������ȭ��򲻹����޷�ʹ�á��������ˡ���\n");

	if ((int)me->query_skill("force") < 300)
		return notify_fail("����ڹ���Ϊ�������޷�ʹ�á��������ˡ���\n");
//����׼��
//	if (me->query_skill_prepared("cuff") != "qishang-quan")
	//	return notify_fail("������û��׼��ʹ������ȭ���޷�ʹ�á��������ˡ���\n");

	if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "�������������������ľ��Ƹ���ʫ�����ˣ�"
	      "�ܾ���ɲ�Ǽ䣬����һ����������ȭ��"NOR"\n";
	
	message_vision(msg, me, target);
	for (i = 0; i < 6; i++)
	{
	    if(random(3))
	    {
	        ap = me->query_skill("cuff") / 2 + me->query("con") * 6;
	        dp = target->query_skill("force", 1);
	        count = ap - dp;
	        if (count < 0)    count = random(100);
	        target->receive_wound("qi", count, me);
	        msg = HIY "$n���$P���Ѹ����ȭ������ȫû���������أ����顱���ؿ�Ӳ��һȭ��" NOR "\n" HIR "�����ھ�-" + count + "��" NOR "\n";
	        if (random(3))
	        {
	            msg += HIY "$P�ܵ�������ȭ���ɡ�" NOR "\n";
	            busy_count++;
	            me->receive_damage("qi", count / 10 * 7, target);
	        }
	        
	        message_vision(msg, me, target);
	    }
	    else
	    {
	        msg = HIW "$n�����񣬻�����$P����ʽ��" NOR "\n";
	        
	        message_vision(msg, me, target);
	    }
	}
	
	me->add("neili", -500);
	me->add("qi", -500);
	me->start_busy(busy_count);
    
    skill_cd(me,"qimaj",8);

	return 1;
}
