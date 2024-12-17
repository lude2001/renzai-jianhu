// This is player's own skill (Write by Lonely@nt2)
// Create by 人麻了(Yyd057) at Thu Sep  1 20:59:42 2022
// 小夜叉棍(xyc-club.c)

#include <ansi.h>
inherit SKILL;	
		
int is_invent_skill() { return 1; }

mapping *action = ({
// ZHAOSHI : 0
([      "action" : "维护众生界",
	"attack" : 227,
	"damage" : 245,
	"force" : 217,
	"dodge" : 213,
	"parry" : 217,
	"lvl" : 0,
	"damage_type" : "瘀伤",
	"skill_name" : "小夜叉"
 ]),
// ZHAOSHI : 1
});

int valid_learn(object me)
{
	if( (int)me->query("max_neili") < 50 )
		return notify_fail("你的内力太弱，无法练"+"小夜叉棍"+"。\n");
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
	level = (int)me->query_skill("xyc-club",1);
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

	lvl = me->query_skill("xyc-club", 1);
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
	return __DIR__ + "xyc-club" + "/" + action; 
}

string query_description()
{
	return
 "小夜叉棍,其棍法多变，以扫、拨、云、架、撩、戳、
劈、舞花、挑、点为主要技法，尤其挑点戳棍法较多，
体现了少林棍谱中讲的“三分棍法七分枪法”的棍法
要旨，是不可多得的精华套路。" ; 
}
