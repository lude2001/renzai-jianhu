// mdiamond.c ��֮��ʯ

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
	set_name(HIW "��֮��ʯ" NOR, ({ "magic diamond" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIW "һ�Ż���������Ĺ�ʵ���ʯ�������Բ�ͬѰ���ĸо���"NOR"\n");
		set("base_value", 200000);
		set("base_weight", 1);
		set("base_unit", "��");
		set("no_give",1);
		set("no_drop",1);
		set("no_get",1);
        set("no_sell",1);
		set("can_be_enchased", __DIR__"god_eyes");
		set("enchased_need", ({
			(["id":"magic agate","name":"��֮���"]),
			(["id":"magic crystal","name":"��֮ˮ��"]),
			(["id":"magic jade","name":"��֮���"]), 
		}));
		set("magic/type", "lighting");
		set("magic/power", 150);
	}
	set_amount(1);
	setup();
}
