//ningshenforce.c
//【蜀山剑派】by yushu 2001.2



inherit FORCE;

int valid_enable(string usage)
{ 
	return usage == "force"; 
}

int query_neili_improve(object me)
{
	int lvl;

	lvl = (int)me->query_skill("shushan-force", 1);
	return lvl * lvl * 15 * 25 / 100 / 200;
}

int valid_force(string force)
{
	return 1;
}

int valid_learn(object me) 
{ 
	int lvl = (int)me->query_skill("shushan-force", 1);

	if (me->query("gender") == "无性" && (int)me->query_skill("shushan-force", 1) > 49)
		return notify_fail("你无根无性，阴阳不调，难以领会高深的蜀山心法。\n");

	if ((int)me->query_skill("force", 1) < 100)
		return notify_fail("你的基本内功火候还不够，还不能学习蜀山心法。\n");

	if (me->query("int") < 30)
		return notify_fail("你觉得蜀山心法过于艰深，难以理解。\n");

	return ::valid_learn(me);
}


int practice_skill(object me)
{
        return notify_fail("蜀山心法只能用学的，或是从运用(exert)中增加熟练度。\n");
}
string exert_function_file(string func)
{
        return __DIR__"shushan-force/" + func;
}

