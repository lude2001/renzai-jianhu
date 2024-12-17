// crystal.c 水晶

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
	set_name(HIM "水晶" NOR, ({ "crystal" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIM "一块粉色的水晶。"NOR"\n");
		set("base_value", 50000);
		set("base_weight", 1);
		set("base_unit", "块");
		set("no_give",1);
		set("no_drop",1);
		//set("no_get",1);
        set("no_sell",1);
		set("can_be_enchased", __DIR__"fcrystal");
		set("enchased_need", 3);
		set("magic/type", "magic");
		set("magic/power", 60);
	}
	set_amount(1);
	setup();
}
