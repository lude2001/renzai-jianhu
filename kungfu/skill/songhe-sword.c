inherit SKILL;
#include <ansi.h>
mapping *action = ({
	([	"name":			"����ӭ��",
		"action":
"$N��������,����$w���գ���$n��ȥ�������ƿ�ɽ��һ�㣬��һ�����ۺ��"HIC"������ӭ�͡�"NOR"",
		"dodge":		-10,
		"parry":		20,
		"damage":		25,
		"damage_type":		"����"
	]),
	([	"name":			"�ƹȺ׷�",
		"action":
"ֻ��$N���ָ�����������轣������$w��$n��ȫ��ȥ\n"
"����һ��"HIR"���ƹȺ׷塹"NOR"��",
		"dodge":		  24,
		"parry":		-19,
		"damage":		  25,
		"damage_type":		"����"
	]),
        ([      "name":                 "��ɽ����",
                "action":
"$N������ǰ������$w���裬һ��"HIM"����ɽ������"NOR"�ó����Ž�â����$n������������",
		    "dodge":		 -15,
                "parry":           -15,
                "damage":          35,
                "damage_type":          "����"
        ]),
        ([      "name":                 "�׺�����",
                "action":
"$N���˷��������һ����Х������$w������$n��$l��ȥ������ɽ����Х���"HIG"���׺�����"NOR"��ȫ��$n������",
                "dodge":                15,
                "parry":                15,
                "damage":               35,
                "damage_type":          "����"
        ]),
        ([      "name":                 "Я������",
                "action":
"ֻ��$N������أ�ʹ��һ��"HIW"��Я�����ơ�"NOR"������$w���ٷɽ���������㽣����ֱ��$n��$l��ȥ",
                "dodge":                -10,
                "parry":                -10,
                "damage":               25,
                "damage_type":          "����"
        ]),
        ([      "name":                 "��������",
                "action":
"$N����ǰ����һʽ"HIB"���������硹"NOR"�����潣����$nȫ���������â������������������$n�������ܵù�",
		"dodge":	          -15,
		"parry":		15,
		"damage":		20,
		"damage_type":		"����"
	])
});
int valid_learn(object me)
{
	object ob;

	if( (int)me->query("max_neili") < 50000 )
		return notify_fail("���������Ϊ������޷�ѧϰ�ɺ׽�����\n");
	if (!(ob = me->query_temp("weapon"))
	   || (string)ob->query("skill_type") != "sword" )
		return notify_fail("���������һ����������ϰ������\n");
	return 1;
}

int practice_skill(object me)
{
	int dod=(int)me->query_skill("dodge",1);
	int swo=(int)me->query_skill("songhe-sword",1);

	if (dod<swo/2)
		return notify_fail("����������Ͻ���������ȥ�ܿ��ܻ��˵��Լ���\n");
	if ((int)me->query("qi") < 30)
		return notify_fail("������Ƿ�ѣ�ǿ���ɺ׽����к����档\n");
	if ((int)me->query("neili") < 5)
		return notify_fail("���������㣬ǿ���ɺ׽������߻���ħ��Σ�ա�\n");
	me->receive_damage("qi", 30);
	me->add("neili", -5);
//	message_vision("$NĬĬ������һ�����Ȼ������һ���ɺ׽�����\n", me);
	return 1;
}

int valid_enable(string usage)
{
	return usage=="sword"||usage=="parry";
}

mapping query_action(object me, object weapon)
{
	return action[random(sizeof(action))];
}

string perform_action_file(string action)
{
    return __DIR__"songhe-sword/" + action;
}
