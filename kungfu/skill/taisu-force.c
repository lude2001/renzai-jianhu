// taisu-force.c 太素心经
// by 潇湘夜雨

inherit FORCE;

int valid_enable(string usage)
{
	return usage == "force";
}

int query_neili_improve(object me)
{
	int lvl;

	lvl = (int)me->query_skill("taisu-force", 1);
	return lvl * lvl * 15 * 22 / 100 / 200;
}

int valid_force(string force)
{
	return 1;
}

int valid_learn(object me)
{
	int lvl = (int)me->query_skill("taisu-force", 1);
//	if ((int)me->query_skill("taisu-force", 1) <150)
		//return notify_fail("你的太素心经等级＜150级，难以领会高深的太素心经。\n");
	if ((int)me->query_skill("force", 1) < 200)
		return notify_fail("你的基本内功火候还不够，还不能学习太素心经。\n");

	if (me->query("int") < 25)
		return notify_fail("你觉得太素心经过于艰深，以你的悟性难以理解。\n");

	if (me->query("con") < 25)
		return notify_fail("你的根骨不好，难以运转太素心经。\n");

	return ::valid_learn(me);
}

int practice_skill(object me)
{
		if ((int)me->query("qi") < 70)
		return notify_fail("你的体力太低了。\n");
	if ((int)me->query("neili") < 70)
		return notify_fail("你的内力不够练太素心经。\n");

	me->receive_damage("qi", 61);
	me->add("neili", -57);
	return 1;
}

string exert_function_file(string func)
{
	return __DIR__"taisu-force/" + func;
}

int diffcult_level() { return 200; }
