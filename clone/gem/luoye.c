// 宝石

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
	set_name(HIM "罗叶石" NOR, ({ "luoye shi" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIM "一片罗叶石，听说蕴含了多罗叶指的极意。"NOR"\n");
		set("base_value", 20000);
		set("base_weight", 1);
		set("base_unit", "片");
		set("no_sell",1);
        set("no_give",1);
        set("no_drop",1);
        set("no_get",1);
        set("no_teal", 1);
		set("can_be_inlay",([
		"name":"罗叶石",
		"skill":"duoluoye-zhi",
		])
		);
	}
	set_amount(1);
	setup();
}
