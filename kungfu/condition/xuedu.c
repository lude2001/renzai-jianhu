// sanyin.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "xuedu"; }

string chinese_name() { return "Ѫ��"; }

string update_msg_others()
{
       return "Ѫ��������$N���һ��ͻ��һ��Ѫ��\n";
}

string update_msg_self()
{
	return HIB "��ֻ����һ�ɹ����������������ڣ���ʹ���̣�"NOR"\n";
}

