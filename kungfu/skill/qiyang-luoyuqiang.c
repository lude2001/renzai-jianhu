inherit SKILL;

mapping *action = ({
([      "action":"$N一招「平阳刺」，双手舞动$w，猛向$n的刺去",
	"force" : 120,
	"attack": 25,
	"dodge" : 5,
	"parry" : 30,
	"damage": 10,
	"lvl"   : 0,
	"skill_name" : "平阳刺",
	"damage_type":"挫伤"
]),
([      "action":"$N手握$w，以腰发力，舞动三圈,一招「落雨扫」，$w猛地卷向$n",
	"force" : 150,
	"attack": 37,
	"dodge" : 5,
	"parry" : 31,
	"damage": 15,
	"lvl"   : 40,
	"skill_name" : "落雨扫",
	"damage_type":"挫伤"
]),
([      "action":"$N一招「七进七出」，紧握$w向$n的胸腹间连戳七下",
	"force" : 180,
	"attack": 42,
	"dodge" : 5,
	"parry" : 37,
	"damage": 20,
	"lvl"   : 80,
	"skill_name" : "七进七出",
	"damage_type":"刺伤"
]),
([      "action":"$N单手倒握长枪，一招「怒阳击」，$w以破空之声猛的砸向$n的头部",
	"force" : 210,
	"attack": 43,
	"dodge" : 15,
	"parry" : 35,
	"damage": 25,
	"lvl"   : 100,
	"skill_name" : "怒海击",
	"damage_type":"挫伤"
]),
([      "action":"$N一招「击雨破阳」，人枪合一，枪尖协破风之势，如同雨落荷叶般击向$n的$l",
	"force" : 240,
	"attack": 49,
	"dodge" : 20,
	"parry" : 41,
	"damage": 30,
	"lvl"   : 120,
	"skill_name" : "击雨破阳",
	"damage_type":"挫伤"
]),
([      "action":"$N双手舞动$形成一个落日形状的圆圈，双腿发力蓄力半步,只见其一招「流星贯日」，一枪从中心猛的击出，撞向$n的胸口",
	"force" : 270,
	"attack": 58,
	"dodge" : 20,
	"parry" : 45,
	"damage": 35,
	"lvl"   : 140,
	"skill_name" : "流星贯日",
	"damage_type":"刺伤"
]),
([      "action":"$N一招「狂风暴雨」，往前三步舞动$w击向$n的全身",
	"force" : 300,
	"attack": 61,
	"dodge" : 25,
	"parry" : 52,
	"damage": 40,
	"lvl"   : 160,
	"skill_name" : "狂风暴雨",
	"damage_type":"挫伤"
]),
([      "action":"$N反握$w，以爆发之势冲向$n身后,翻身一个跳劈,一招「龙抬头」,猛的砸向$n",
	"force" : 320,
	"attack": 63,
	"dodge" : 30,
	"parry" : 55,
	"damage": 50,
	"lvl"   : 180,
	"skill_name" : "龙抬头",
	"damage_type":"挫伤"
]),
});

int valid_enable(string usage) { return usage == "club" || usage == "parry"; }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 20000)
		return notify_fail("你的内力不够。\n");

	if ((int)me->query_skill("force") < 650)
		return notify_fail("你的内功火候太浅。\n");

	if ((int)me->query_skill("qiang", 1) < (int)me->query_skill("qiyang-luoyuqiang", 1))
		return notify_fail("你的枪法修为水平有限，无法领会更高深的七阳落雨枪。\n");

	return 1;
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if (level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("qiyang-luoyuqiang", 1);
	for(i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	object weapon;

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "club")
		return notify_fail("你使用的武器不对。\n");

	if ((int)me->query("qi") < 70)
		return notify_fail("你的体力不够练七阳落雨枪。\n");

	if ((int)me->query("neili") < 70)
		return notify_fail("你的体力不够练七阳落雨枪。\n");

	me->receive_damage("qi", 62);
	me->add("neili", -61);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"qiyang-luoyuqiang/" + action;
}
