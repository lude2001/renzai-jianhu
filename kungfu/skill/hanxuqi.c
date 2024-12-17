// literate.c 读书写字
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>
inherit SKILL;

string type() { return "knowledge"; }

int valid_learn(object me)
{
	if (me->query_skill("hanxuqi") > 500)
	return notify_fail("你的涵虚气等级已经达到最高了！\n");
	return 1;
}

int help(object me)
{
	write(HIC"\n涵虚气："NOR"\n");
	write(@HELP

    吐纳术。
	学习要求：
		无
HELP
	);
	return 1;
}

