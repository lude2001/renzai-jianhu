#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIM "צ�����" NOR; }

int perform(object me, string skill)
{
	return notify_fail("����ܿ���������צ��������\n");
}

string explain()
{
return "�������������������츳�������е�צ�������и�ǿ������";
}
