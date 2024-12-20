// This is player's own skill (Write by Lonely@nt2)
// Create by 叶倾仙(Qw18675630) at Sat Aug 27 15:29:04 2022
// 惟我独帝斩道剑(byyqx-sword.c)

#include <ansi.h>
inherit SKILL;	
		
int is_invent_skill() { return 1; }

mapping *action = ({
// ZHAOSHI : 0
([      "action" : "[1;31m$N身旁缓缓凝聚大帝法则，手中$w突然穿越时间长河，一剑断尽诸天万界天道法则，斩破因果轮回，$n感觉到这一剑独断万古，无人能挡！！！",
	"attack" : 226,
	"damage" : 168,
	"force" : 168,
	"dodge" : 168,
	"parry" : 168,
	"lvl" : 0,
	"damage_type" : "刺伤",
	"skill_name" : "斩天道"
 ]),
// ZHAOSHI : 1
});

int valid_learn(object me)
{
	object weapon; 
	
	if (! objectp(weapon = me->query_temp("weapon"))
		|| (string)weapon->query("skill_type") != "sword") 
		return notify_fail("你使用的武器不对。\n");
		
	if ((int)me->query("max_neili") < 50)
		return notify_fail("你的内力太弱，无法练" + "惟我独帝斩道剑" + "。\n");
		
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
	level = (int)me->query_skill("byyqx-sword",1);
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

	lvl = me->query_skill("byyqx-sword", 1);
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
	return __DIR__ + "byyqx-sword" + "/" + action; 
}

string query_description()
{
	return
 "天断山，一剑扫，圣灵血溅百万山。羽化朝，翻手灭，
帝皇喋血殒中州。斩落天道，断绝轮回，杀破诸天，
戮尽万古。我即是道，道即是帝，帝即是我，我即无
敌...." ; 
}
