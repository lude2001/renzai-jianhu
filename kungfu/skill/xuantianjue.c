// literate.c ����д��
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>
inherit SKILL;

string type() { return "knowledge"; }

int valid_learn(object me)
{
	if (me->query_skill("xuantianjue") > 500)
	return notify_fail("���������ȼ��Ѿ��ﵽ����ˣ�\n");
	return 1;
}

int help(object me)
{
	write(HIC"\n�������"NOR"\n");
	write(@HELP

    ��������
	ѧϰҪ��
		��
HELP
	);
	return 1;
}

