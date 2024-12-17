//六脉神剑-无形剑气pfm宝石

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
	set_name(HIM "青隐" NOR, ({ "six_qi gem" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIM "一块微微发青的透明宝石。"NOR"\n");
		set("base_value", 20000);
		set("base_weight", 1);
		set("base_unit", "片");
		set("no_sell",1);
        set("no_give",1);
        set("no_drop",1);
        set("no_get",1);
        set("no_teal", 1);
		set("can_be_inlay",([
		"name":"青隐",
		"skill":"six-finger-qi",
		])
		);
	}
	set_amount(1);
	setup();
}
