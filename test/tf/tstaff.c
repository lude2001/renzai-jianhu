#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIM "�ȷ����" NOR; }

int perform(object me, string skill)
{
	return notify_fail("����ܿ����������ȷ�������\n");
}

string explain()
{
return "�������������������츳�������е��ȷ������и�ǿ������";
}
