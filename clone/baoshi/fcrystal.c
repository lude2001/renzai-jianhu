// fcrystal.c 稀世水晶

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
	set_name(HIM "稀世水晶" NOR, ({ "flawless crystal" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIM "一块光彩照人的大水晶，美仑美奂，世所罕有。"NOR"\n");
		set("base_value", 100000);
		set("base_weight", 1);
		set("base_unit", "块");
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
