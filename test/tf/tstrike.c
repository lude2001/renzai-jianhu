#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIM "�Ʒ����" NOR; }

int perform(object me, string skill)
{
	return notify_fail("����ܿ����������Ʒ�������\n");
}

string explain()
{
return "�������������������츳�������е��Ʒ������и�ǿ������";
}
