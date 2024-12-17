
// qianzhu-wandushou.c  ǧ������
// by star

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N����һ�ζ�����һ�С�С�����꡹��˫�ƴ���һ���ȷ�����$n��ǰ��",
        "dodge": 10,
        "force": 200,
        "lvl" : 0,
        "damage_type": "����"
]),
([      "action": "$N���λ���һ����������$n��ת��һ�С������ֻ֡���˫�ƻó�������Ӱ����$n",
        "dodge": 40,
        "force": 250,
        "lvl" : 20,
        "damage_type": "����"
]),
([	"action": "$N���һ����һ�С�������š���������޸���ɽ����һ���ȷ�������$n������",
	"dodge": -20,
	"force": 300,
	"lvl" : 50,
	"damage_type": "����"
]),
([	"action": "$Nһ����Ц��һ�С����߾�ת��������һ��������һ�������ĳ����ֱ�����\n�޹ǣ��Ƶ���;������ű䣬����Ȱ�ӡ��$n��$l",
	"dodge": 60,
	"lvl" : 80,
	"force": 350,
	"damage_type": "����"
]),
([	"action": "$N������ǰ��һ�С��ظ����硹��˫�������ĳ���һ���Ƴ��ǵĺ���������\n͸������$n��Χ�Ŀ�����������",
	"dodge": 10,
	"force": 400,
	"lvl" : 120,
	"damage_type": "����"
]),
([	"action": "$N����һ�������κ����������򣬷���ײ��$n��һ�С��Ʒ��´̡������罣��\nֱ��$n������",
	"dodge": 80,
	"lvl" : 150,
	"force": 450,
	"damage_type": "����"
]),
([	"action": "$Nһ���������������𣬰����һʽ��������β�������ֻ���$n��$l",
	"dodge": 40,
	"lvl" : 200,
	"force": 500,
	"damage_type": "����"
]),
([	"action": "$N���һ���������嶾�񹦣�һ�С������������ɲ�Ǽ�ȫ��ë�����̣�һ\n�Ա��̵�˫צ�����ĳ�$n��$lץȥ",
	"dodge": 20,
	"lvl" : 250,
	"force": 600,
	"damage_type": "����"
]),
});

int valid_enable(string usage) { return usage=="hand" || usage=="parry"; }


mapping query_action(object me, object weapon)
{
    mapping a_action;
    int i, level;
    level   = (int) me->query_skill("qianzhu-wandushou", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"]){
                        a_action = action[NewRandom(i, 5, level/5)];
                        break;
                }
    a_action["parry"]  = 0-level/3;
    a_action["attack"]  = level/3;
    a_action["damage"] = level/2;
    return a_action;

}

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("��ǧ�����ֱ�����֡�\n");
	if ((int)me->query_skill("wudu-shengong", 1) < 10)
		return notify_fail("����嶾�񹦻�򲻹����޷���ǧ�����֡�\n");
	if ((int)me->query("max_neili") < 100)
		return notify_fail("�������̫�����޷���ǧ������");
	return 1;
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 30)
		return notify_fail("�������̫���ˡ�\n");
	if ((int)me->query("neili") < 100)
		return notify_fail("�������������ǧ�����֡�\n");
	me->receive_damage("qi", 25);
//	me->add("neili", -5);
	return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
      if( random(me->query_skill("qianzhu-wandushou",1)) > 50 ) 
	  victim->receive_wound("qi", damage_bonus/3);
      if ( victim->query("family/family_name")!= "�嶾��" && me->query_skill("wudu-shengong",1)>100) {
	 switch( random(5) ) {
		case 0:
            victim->apply_condition("snake_poison", (me->query_skill("wudu-shengong"))/8 +
			victim->query_condition("snake_poison"));
			break;
		case 1:
            victim->apply_condition("zhizhu_poison", (me->query_skill("wudu-shengong"))/8 +
			victim->query_condition("zhizhu_poison"));
			break;
		case 2:
            victim->apply_condition("wugong_poison", (me->query_skill("wudu-shengong"))/8 +
			victim->query_condition("wugong_poison"));
			break;
		case 3:
            victim->apply_condition("xiezi_poison", (me->query_skill("wudu-shengong"))/8 +
			victim->query_condition("xiezi_poison"));
			break;
		case 4:
            victim->apply_condition("chanchu_poison", (me->query_skill("wudu-shengong"))/8 +
			victim->query_condition("chanchu_poison"));
			break;
	}
        return HIR "$nֻ�����˴�һ���飬�ƺ��ж��ˡ�\n" NOR;
   }
}
void skill_improved(object me)
{
  if(random(15) < 1 && me->query("per") > 5){
       tell_object(me, HIR "���Ȼ�������ڶ�����ܣ����϶�ʱ����һ�������\n" NOR );
       me->add("per", -1);
  }
}

string perform_action_file(string action)
{
	return __DIR__"qianzhu-wandushou/" + action;
}