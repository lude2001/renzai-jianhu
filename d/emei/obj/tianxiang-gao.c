// tianxiang-gao.c
inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_smear", "smear");
}

void create()
{
	set_name(HIC "���������" NOR, ({"tianxiang gao", "gao"}));
	set("unit", "��");
	set("long", "����һ�к�ɫ�����˸�ҩ�����Բ�Ϳ��smear����\n");
	setup();
}

int do_smear(string arg)
{
	if (!id(arg))  return notify_fail("���Ϳʲô��\n");

	if ( this_player()->qeury("eff_qi") >= this_player()->qeury("max_qi") )
		return notify_fail("��ʲô����������û���ˣ��ò���Ϳ����\n");

	this_player()->receive_curing("qi", 250);
	tell_object(this_player(), HIG "��Ѻ�ɫ�ĸ�ҩͿ�����˿��ϣ���ʱ����һ������֮��
����ȫ����"NOR"\n" );
	destruct(this_object());
	return 1;
}