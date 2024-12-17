// jade.c ôä´ä

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
	set_name(HIG "ôä´ä" NOR, ({ "jade" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIG "Ò»¿é±ÌÍ¸ÓûµÎµÄôä´ä¡£"NOR"\n");
		set("base_value", 50000);
		set("base_weight", 1);
		set("base_unit", "¿é");
		set("no_give",1);
		set("no_drop",1);
		set("no_get",1);
        set("no_sell",1);
		set("can_be_enchased", __DIR__"fjade");
		set("enchased_need", 3);
		set("magic/type", "cold");
		set("magic/power", 100);
	}
	set_amount(1);
	setup();
}
