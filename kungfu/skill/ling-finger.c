// This is player's own skill (Write by Lonely@nt2)
// Create by 段皇爷(Q702413605) at Wed Jun 29 09:39:56 2022
// 灵犀一指指(ling-finger.c)

#include <ansi.h>
inherit SKILL;	
		
int is_invent_skill() { return 1; }

mapping *action = ({
// ZHAOSHI : 0
([      "action" : "$N单手比了个耶，脚尖轻点飞向$n。$n只觉得身如千斤重，便是再也无法动弹",
	"attack" : 232,
	"damage" : 209,
	"force" : 217,
	"dodge" : 216,
	"parry" : 217,
	"lvl" : 0,
	"damage_type" : "瘀伤",
	"skill_name" : "灵犀一指"
 ]),
// ZHAOSHI : 1
});

int valid_learn(object me)
{
	if( me->query_temp("weapon") || me->query_temp("secondary_weapon") )
		return notify_fail("练"+"灵犀一指指"+"必须空手。\n");
	if( (int)me->query("max_neili") < 50 )
		return notify_fail("你的内力太弱，无法练"+"灵犀一指指"+"。\n");
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
	level = (int)me->query_skill("ling-finger",1);
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

	lvl = me->query_skill("ling-finger", 1);
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
	return __DIR__ + "ling-finger" + "/" + action; 
}

string query_description()
{
	return
 "据说此招式是融合了昔年九州王沈天君的乾坤第一指
和楚留香的教诲而成，不求杀人，以压制敌人为主，
是天下无双，万无一失的绝技。一旦被灵犀一指夹住，
便无法再动弹" ; 
}
