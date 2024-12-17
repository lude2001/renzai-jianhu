// This is player's own skill (Write by Lonely@nt2)
// Create by 砚寒清(Q695693419) at Thu Oct 20 03:40:38 2022
// 啸穹刀(xiaoqiong-blade.c)

#include <ansi.h>
inherit SKILL;	
		
int is_invent_skill() { return 1; }

mapping *action = ({
// ZHAOSHI : 0
([      "action" : "一刀斩出，犹如虎啸空山，百兽俯首！",
	"attack" : 263,
	"damage" : 232,
	"force" : 232,
	"dodge" : 269,
	"parry" : 232,
	"lvl" : 0,
	"damage_type" : "割伤",
	"skill_name" : "虎啸空山"
 ]),
// ZHAOSHI : 1
([      "action" : "在靠近敌人时，利用细碎的步伐，调整身形，制造快速旋身的效果，自意料不到的角度出刀，但绝杀的一刀，是转向重步的一刀。",
	"attack" : 263,
	"damage" : 232,
	"force" : 232,
	"dodge" : 269,
	"parry" : 232,
	"lvl" : 12,
	"damage_type" : "割伤",
	"skill_name" : "碎梦"
 ]),
// ZHAOSHI : 2
([      "action" : "在靠近敌人时，利用细碎的步伐，调整身形，制造快速旋身的效果，自意料不到的角度出刀，但绝杀的一刀，是转向重步的一刀。",
	"attack" : 263,
	"damage" : 232,
	"force" : 232,
	"dodge" : 269,
	"parry" : 232,
	"lvl" : 20,
	"damage_type" : "割伤",
	"skill_name" : "惊鸿"
 ]),
// ZHAOSHI : 3
([      "action" : "刀宗禁忌绝学，运使此招太久，最终会陷入疯狂失控的状态，七分清醒三分醉，生在醉中，死在梦中。",
	"attack" : 263,
	"damage" : 232,
	"force" : 232,
	"dodge" : 269,
	"parry" : 232,
	"lvl" : 30,
	"damage_type" : "割伤",
	"skill_name" : "醉生梦死"
 ]),
// ZHAOSHI : 4
});

int valid_learn(object me)
{
	object weapon; 
	
	if (! objectp(weapon = me->query_temp("weapon"))
		|| (string)weapon->query("skill_type") != "blade") 
		return notify_fail("你使用的武器不对。\n");
		
	if ((int)me->query("max_neili") < 50)
		return notify_fail("你的内力太弱，无法练" + "啸穹刀" + "。\n");
		
	return 1;
}

int valid_enable(string usage) { 
	return usage == "blade" || 
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
	level = (int)me->query_skill("xiaoqiong-blade",1);
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

	lvl = me->query_skill("xiaoqiong-blade", 1);
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
		(string)weapon->query("skill_type") != "blade") 
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
	return __DIR__ + "xiaoqiong-blade" + "/" + action; 
}
