// literate.c ����д��
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>
inherit SKILL;

string type() { return "knowledge"; }

int valid_learn(object me)
{
	if (me->query_skill("zhenwujing") > 500)
	return notify_fail("������侭�ȼ��Ѿ��ﵽ����ˣ�\n");
	return 1;
}

int help(object me)
{
	write(HIC"\n���侭��"NOR"\n");
	write(@HELP

    ��������
	ѧϰҪ��
		��
HELP
	);
	return 1;
}

