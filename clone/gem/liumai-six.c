//������-��������pfm��ʯ

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
	set_name(HIM "����" NOR, ({ "six_six gem" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIM "һ�鵭��ɫ�ı�ʯ��"NOR"\n");
		set("base_value", 20000);
		set("base_weight", 1);
		set("base_unit", "Ƭ");
		set("no_sell",1);
        set("no_give",1);
        set("no_drop",1);
        set("no_get",1);
        set("no_teal", 1);
		set("can_be_inlay",([
		"name":"����",
		"skill":"six-finger-six",
		])
		);
	}
	set_amount(1);
	setup();
}