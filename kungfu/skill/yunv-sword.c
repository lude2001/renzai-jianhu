// This is player's own skill (Write by Lonely@nt2)
// Create by 苏沫鸢(Alse) at Mon Jun 20 19:28:28 2022
// 玉女素心喵喵喵剑(yunv-sword.c)

#include <ansi.h>
inherit SKILL;	
		
int is_invent_skill() { return 1; }

mapping *action = ({
// ZHAOSHI : 0
([      "action" : "喵喵喵喵喵喵喵",
	"attack" : 214,
	"damage" : 187,
	"force" : 198,
	"dodge" : 187,
	"parry" : 198,
	"lvl" : 0,
	"damage_type" : "刺伤",
	"skill_name" : "喵喵喵"
 ]),
// ZHAOSHI : 1
([      "action" : "miao",
	"attack" : 214,
	"damage" : 187,
	"force" : 198,
	"dodge" : 187,
	"parry" : 198,
	"lvl" : 12,
	"damage_type" : "刺伤",
	"skill_name" : "大喵一声"
 ]),
// ZHAOSHI : 2
([      "action" : "moi",
	"attack" : 214,
	"damage" : 187,
	"force" : 198,
	"dodge" : 187,
	"parry" : 198,
	"lvl" : 20,
	"damage_type" : "刺伤",
	"skill_name" : "连喵两声"
 ]),
// ZHAOSHI : 3
});

int valid_learn(object me)
{
	object weapon; 
	
	if (! objectp(weapon = me->query_temp("weapon"))
		|| (string)weapon->query("skill_type") != "sword") 
		return notify_fail("你使用的武器不对。\n");
		
	if ((int)me->query("max_neili") < 50)
		return notify_fail("你的内力太弱，无法练" + "玉女素心喵喵喵剑" + "。\n");
		
	return 1;
}

int valid_enable(string usage) { 
	return usage == "sword" || 
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
	level = (int)me->query_skill("yunv-sword",1);
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

	lvl = me->query_skill("yunv-sword", 1);
	if (lvl < 80)  return 0;
	if (lvl < 200) return 50;
	if (lvl < 280) return 80;
	if (lvl < 350) return 100;
	return 120;
}

int practice_skill(object me)
{
	object weapon; 
	if (!objectp(weapon = me->query_temp("weapon")) || 
		(string)weapon->query("skill_type") != "sword") 
		return notify_fail("你使用的武器不对。\n");     
	
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
	return __DIR__ + "yunv-sword" + "/" + action; 
}
