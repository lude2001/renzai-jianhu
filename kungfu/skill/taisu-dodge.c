// taisu-dodge.c
// ̫�����粽��by ����ҹ��
 
#include <ansi.h> 
      
inherit SKILL; 
	
string *dodge_msg = ({ 
	"����$n���м��٣�$N��һ�в��˳���\n", 
	"ȴ��$n����΢�Σ���������֮�⡣\n", 
	"$n�����㣬�����ܿ���$N��һ�С�\n", 
	"$n�߸߰����ڿ�����ת��Ȧ�����������ɿ��⡣\n", 
	"$n����ת�����𾢷磬�Ƶ�$N�޷�����\n", 
	"$N��һ���ۿ���Ҫ���У�����$n��һ�����ܹ�$N�ľ�����ʵ��������˼��\n", 
	"$n���˷�������$N���������ǡǡ�ܿ���һ�С�\n", 
}); 
       
int valid_enable(string usage)  
{  
	return usage == "dodge"; 
} 
       
int valid_learn(object me) 
{ 
	int lvl; 
       
	lvl = me->query_skill("taisu-dodge", 1); 
	if (lvl > 300) lvl = 300; 
//if (lvl <150)
//		return notify_fail("���̫�����粽�ȼ���150���������������̫�����粽��\n");       
	if (me->query("max_neili") < 1000 + lvl * 10) 
		return notify_fail("���������Ϊ��Ƿ���\n");
 

	if (me->query("dex") < 25)
		return notify_fail("��������,ѧ������"
				   "�˸�����Ṧ��\n"); 

	return 1; 
} 
       
string query_dodge_msg(string limb) 
{ 
	return dodge_msg[random(sizeof(dodge_msg))]; 
} 
       
mixed valid_damage(object ob, object me, int damage, object weapon) 
{ 
	mixed result; 
	int ap, dp; 
       
	if ((int)me->query_skill("taisu-dodge", 1) < 100 || 
	    ! living(me)) 
		return; 
	
	ap = ob->query_skill("dodge") * 4 / 3; 
	dp = me->query_skill("dodge", 1) / 2 + 
	     me->query_skill("taisu-dodge", 1); 
       
	if (ap / 2 + random(ap) < dp) 
	{ 
		result = ([ "damage": -damage ]); 
       
		switch (random(4)) 
		{ 
		case 0: 
			result += (["msg" : HIW "����$n" HIW "��¶΢Ц������һ����$N" 
					    HIW "ֻ����ǰһ�����ƺ�������ǧ�ٸ��縡��Ʈ�ڰ���е�" 
					    HIW "��Ӱ��"NOR"\n"]); 
			break; 
		case 1: 
			result += (["msg" : HIW "$N" HIW "ֻ����ǰһ����Ӱ��һ��һ�Σ�"
					    HIW "$n��ƽ�������Ӻ��ƣ���������ˮ��������޳���˲��ʧȥ���Ρ�"NOR"\n"]); 
			break; 
		case 2: 
			result += (["msg" : HIW "$N" HIW "��һ��Ѹ���ޱȣ�Ȼ��$n" 
					    HIW "û�ж�����ԥ��������ǰһƮ�����������㽫" 
					    HIW "$N��һ�ж��˿�ȥ��"NOR"\n"]); 
			break; 
		default: 
			result += (["msg" : HIW "����$n" HIW "����һ������󵹷ɳ�ȥ��$N" 
					    HIW "�����͹���ȴ�ּ�$n" HIW "�����Ӷ�����ӰƮ��" 
					    "$N��󣬵������˷�����˼��"NOR"\n"]); 
			break; 
		} 
		return result; 
	}
 
} 
      
int query_effect_dodge(object attacker, object me) 
{ 
	int lvl; 
      
	lvl = me->query_skill("taisu-dodge", 1); 
	if (lvl < 50)  return 0; 
	if (lvl < 100) return 40; 
	if (lvl < 150) return 60; 
	if (lvl < 200) return 90; 
	if (lvl < 250) return 110; 
	if (lvl < 300) return 130; 
	if (lvl < 350) return 150; 
	return 160; 
} 
      
int practice_skill(object me) 
{ 
	int cost;

	cost = 60 + (int) me->query_skill("taisu-dodge", 1) / 3;
	if ((int)me->query("qi") < 70) 
		return notify_fail("�������̫���ˣ�������ϰ̫�����粽��\n"); 
     
	if ((int)me->query("neili") < cost) 
		return notify_fail("������������ˣ��޷���ϰ̫�����粽��\n"); 
      
	me->receive_damage("qi", 50); 
	me->add("neili", -cost); 
	return 1; 
} 
      
string perform_action_file(string action) 
{ 
	return __DIR__"taisu-dodge/" + action; 
} 

void skill_improved(object me)
{
	int lvl;
	lvl = me->query_skill("taisu-dodge", 1);

	if (lvl < 270)
	{
		me->apply_condition("taisu-except", lvl / 2 +
				    (int)me->query_condition("taisu-except"));
	}
}	     

int diffcult_level() { return 200; }