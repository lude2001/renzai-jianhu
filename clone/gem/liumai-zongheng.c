//六脉神剑-剑气纵横pfm宝石

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
	set_name(HIM "青冥" NOR, ({ "six_zongheng gem" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIM "一块青色的宝石。"NOR"\n");
		set("base_value", 20000);
		set("base_weight", 1);
		set("base_unit", "片");
		set("no_sell",1);
        set("no_give",1);
        set("no_drop",1);
        set("no_get",1);
        set("no_teal", 1);
		set("can_be_inlay",([
		"name":"青冥",
		"skill":"six-finger-zongheng",
		])
		);
	}
	set_amount(1);
	setup();
}
