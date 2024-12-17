// This is player's own skill (Write by Lonely@nt2)
// Create by 独孤星夜(Snow) at Mon Jun 27 16:22:19 2022
// 金乌神掌(jinwu-strike.c)

#include <ansi.h>
inherit SKILL;	
		
int is_invent_skill() { return 1; }

mapping *action = ({
// ZHAOSHI : 0
([      "action" : "$N一跃而起，手腕一抖，舞出漫天掌影，飞向$n。只见$N掌势如排云倒海，打向$n，$n只觉一股针劲穿心而过，奇经八脉，如寸寸断裂，所受之苦，直比开腔剖肺，还要痛楚。",
	"attack" : 293,
	"damage" : 313,
	"force" : 293,
	"dodge" : 293,
	"parry" : 293,
	"lvl" : 0,
	"damage_type" : "内伤",
	"skill_name" : "薪尽火传"
 ]),
// ZHAOSHI : 1
});

int valid_learn(object me)
{
	if( me->query_temp("weapon") || me->query_temp("secondary_weapon") )
		return notify_fail("练"+"金乌神掌"+"必须空手。\n");
	if( (int)me->query("max_neili") < 50 )
		return notify_fail("你的内力太弱，无法练"+"金乌神掌"+"。\n");
	return 1;
}

int valid_enable(string usage) { 
	return usage == "strike" || 
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
	level = (int)me->query_skill("jinwu-strike",1);
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

	lvl = me->query_skill("jinwu-strike", 1);
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
	return __DIR__ + "jinwu-strike" + "/" + action; 
}

string query_description()
{
	return
 "是一种极厉害的掌法，本来是一种酷刑时逼供的手段，
但独孤星夜活用了，当作普通招法来用。用时印堂、
太阳穴、人中三穴同时黑气陡现，掌力摧动下，犹如
干针万针直刺，直椎人心窝…" ; 
}
