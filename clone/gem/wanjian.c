// 宝石

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
	set_name(HIM "万剑石" NOR, ({ "wanjian shi" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIM "一块万剑石，听说对松鹤剑法有很大的加成。"NOR"\n");
		set("base_value", 20000);
		set("base_weight", 1);
		set("base_unit", "片");
		set("no_sell",1);
        set("no_give",1);
        set("no_drop",1);
        set("no_get",1);
        set("no_teal", 1);
		set("can_be_inlay",([
		"name":"万剑石",
		"skill":"songhe-sword",
		])
		);
	}
	set_amount(1);
	setup();
}
