// This is player's own skill (Write by Lonely@nt2)
// Create by 段天尊(Lmyrq) at Sat Sep 17 00:22:15 2022
// 无影棍(wuying-club.c)

#include <ansi.h>
inherit SKILL;	
		
int is_invent_skill() { return 1; }

mapping *action = ({
// ZHAOSHI : 0
([      "action" : "快速抖动手臂，变为无数枪一般，为无影神枪。",
	"attack" : 258,
	"damage" : 190,
	"force" : 190,
	"dodge" : 190,
	"parry" : 190,
	"lvl" : 0,
	"damage_type" : "瘀伤",
	"skill_name" : "无影神枪"
 ]),
// ZHAOSHI : 1
});

int valid_learn(object me)
{
	if( (int)me->query("max_neili") < 50 )
		return notify_fail("你的内力太弱，无法练"+"无影棍"+"。\n");
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
		return notify_fail("你的体力不够了，休息一下再练吧。\n");
	if( (int)me->query("neili") < 3 )
		return notify_fail("你的内力不够了，休息一下再练吧。\n");
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
 "无影棍乃是七阳落雨枪使用之后体悟出的绝顶棍法，
远远超过七阳落雨枪。" ; 
}
