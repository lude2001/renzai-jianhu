// This is player's own skill (Write by Lonely@nt2)
// Create by ������(Lmyrq) at Sat Sep 17 00:22:15 2022
// ��Ӱ��(wuying-club.c)

#include <ansi.h>
inherit SKILL;	
		
int is_invent_skill() { return 1; }

mapping *action = ({
// ZHAOSHI : 0
([      "action" : "���ٶ����ֱۣ���Ϊ����ǹһ�㣬Ϊ��Ӱ��ǹ��",
	"attack" : 258,
	"damage" : 190,
	"force" : 190,
	"dodge" : 190,
	"parry" : 190,
	"lvl" : 0,
	"damage_type" : "����",
	"skill_name" : "��Ӱ��ǹ"
 ]),
// ZHAOSHI : 1
});

int valid_learn(object me)
{
	if( (int)me->query("max_neili") < 50 )
		return notify_fail("�������̫�����޷���"+"��Ӱ��"+"��\n");
	return 1;
}

int valid_enable(string usage) { 
	return usage == "club" || 
	       usage == "parry"; 
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int)me->query_skill("wuying-club",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

mixed *query_actions() { return action; }

int query_effect_parry(object attacker, object me)
{
	int lvl;

	if (me->query_temp("weapon"))
		return 0;

	lvl = me->query_skill("wuying-club", 1);
	if (lvl < 80)  return 0;
	if (lvl < 200) return 50;
	if (lvl < 280) return 80;
	if (lvl < 350) return 100;
	return 120;
}
 
int practice_skill(object me)
{
	if( (int)me->query("qi") < 25 )
		return notify_fail("������������ˣ���Ϣһ�������ɡ�\n");
	if( (int)me->query("neili") < 3 )
		return notify_fail("������������ˣ���Ϣһ�������ɡ�\n");
	me->receive_damage("qi", 25);
	me->add("neili", -3);
	return 1;
} 

string perform_action_file(string action) 
{
	return __DIR__ + "wuying-club" + "/" + action; 
}

string query_description()
{
	return
 "��Ӱ��������������ǹʹ��֮��������ľ���������
ԶԶ������������ǹ��" ; 
}
