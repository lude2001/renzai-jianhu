// 宝石

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
	set_name(HIM "侠客意" NOR, ({ "xiake yi" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIM "一片侠客意，听说蕴含了白首太玄经的极意。"NOR"\n");
		set("base_value", 20000);
		set("base_weight", 1);
		set("base_unit", "片");
		set("no_sell",1);
        set("no_give",1);
        set("no_drop",1);
        set("no_get",1);
        set("no_teal", 1);
		set("can_be_inlay",([
		"name":"侠客意",
		"skill":"taixuan-gong",
		])
		);
	}
	set_amount(1);
	setup();
}
