#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIM "�������" NOR; }

int perform(object me, string skill)
{
	return notify_fail("����ܿ��������Ե���������\n");
}

string explain()
{
return "�������������������츳�������еĵ��������и�ǿ������";
}
