// 宝石

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
	set_name(HIM "蓝色翡翠" NOR, ({ "lanse gem" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIM "一片蓝色的水晶宝石，听说对胡家刀法有很强的加成。"NOR"\n");
		set("base_value", 20000);
		set("base_weight", 1);
		set("base_unit", "片");
		set("no_sell",1);
        set("no_give",1);
        set("no_drop",1);
        set("no_get",1);
        set("no_teal", 1);
		set("can_be_inlay",([
		"name":"蓝色翡翠",
		"skill":"hujia-daofa",
		])
		);
	}
	set_amount(1);
	setup();
}
