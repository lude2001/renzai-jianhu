// yeqiu-quan 野球拳

inherit SKILL;

mapping *action = ({
([	"action" : "只见$N双拳紧握，如临大敌一般盯着$n！突然小跑两步对着$n的$l一顿组合拳",
	"force"  : 120,
	"dodge"  : 10,
	"damage" : 2,
	"lvl"    : 0,
	"skill_name" : "石头",
	"damage_type" : "瘀伤"
]),
([	"action" : "$N对着$n上上下下打量一番，出奇不易直插$n双眼",
	"force"  : 140,
	"dodge"  : 12,
	"damage" : 5,
	"lvl"    : 20,
	"skill_name" : "剪刀",
	"damage_type" : "瘀伤"
]),
([	"action" : "$N跺了跺脚，冲上去一手抓住$n得头发，一手对着$n得脸颊左右狂扇",
	"force"  : 150,
	"dodge"  : 16,
	"damage" : 15,
	"lvl"    : 40,
	"skill_name" : "布",
	"damage_type" : "瘀伤"
]),
});

int valid_enable(string usage) { return usage == "cuff" || usage == "parry"; }

//int valid_combine(string combo) { return combo == "canhe-zhi"; }

int valid_learn(object me)
{
	if (objectp(me))
		return notify_fail("野球拳不能升级。\n");

/*	if ((int)me->query_skill("force") < 30)
		return notify_fail("你的内功火候不够，无法练野球拳。\n");

	if ((int)me->query("max_neili") < 120)
		return notify_fail("你的内力太弱，无法练野球拳。\n");

	if (me->query_skill("cuff", 1) < me->query_skill("yeqiu-quan", 1))
		return notify_fail("你的基本拳法造诣有限，无法领会更高深的野球拳。\n");
*/
	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("yeqiu-quan", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i - 1]["lvl"])
			return action[NewRandom(i, 20, level  /5)];
}

int practice_skill(object me)
{

if (objectp(me))
		return notify_fail("野球拳不能升级。\n");

	if ((int)me->query("qi") < 50)
		return notify_fail("你的体力太低了。\n");

	if ((int)me->query("neili") < 30)
		return notify_fail("你的内力不够练野球拳。\n");

	me->receive_damage("qi", 36);
	me->add("neili", -18);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"yeqiu-quan/" + action;
}

