// fcrystal.c ϡ��ˮ��

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
	set_name(HIM "ϡ��ˮ��" NOR, ({ "flawless crystal" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIM "һ�������˵Ĵ�ˮ����������ۼ���������С�"NOR"\n");
		set("base_value", 100000);
		set("base_weight", 1);
		set("base_unit", "��");
		set("no_give",1);
		set("no_drop",1);
		set("no_get",1);
        set("no_sell",1);
		set("can_be_enchased", __DIR__"mcrystal");
		set("enchased_need", 3);
		set("magic/type", "magic");
		set("magic/power", 125);
	}
	set_amount(1);
	setup();
}
