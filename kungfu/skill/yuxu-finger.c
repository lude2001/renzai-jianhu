// This is player's own skill (Write by Lonely@nt2)
// Create by 砚寒清(Q695693419) at Sat Sep 24 01:38:10 2022
// 无相驭虚指(yuxu-finger.c)

#include <ansi.h>
inherit SKILL;	
		
int is_invent_skill() { return 1; }

mapping *action = ({
// ZHAOSHI : 0
([      "action" : "$N凌空一指，数道气劲霎时封住$n所有退路。紧接着一记「相无离火」直指$n命门要穴而来！",
	"attack" : 251,
	"damage" : 183,
	"force" : 183,
	"dodge" : 183,
	"parry" : 183,
	"lvl" : 0,
	"damage_type" : "瘀伤",
	"skill_name" : "相无离火"
 ]),
// ZHAOSHI : 1
});

int valid_learn(object me)
{
	if( me->query_temp("weapon") || me->query_temp("secondary_weapon") )
		return notify_fail("练"+"无相驭虚指"+"必须空手。\n");
	if( (int)me->query("max_neili") < 50 )
		return notify_fail("你的内力太弱，无法练"+"无相驭虚指"+"。\n");
	return 1;
}

int valid_enable(string usage) { 
	return usage == "finger" || 
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
	level = (int)me->query_skill("yuxu-finger",1);
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

	lvl = me->query_skill("yuxu-finger", 1);
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
	return __DIR__ + "yuxu-finger" + "/" + action; 
}

string query_description()
{
	return
 "由上任天下第一指所遗留的《无相驭虚指》残章中领
悟出的独属于砚寒清的「无相驭虚指」。相无离火" ; 
}
