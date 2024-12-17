// fdiamond.c 精美钻石

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
	set_name(HIW "精美钻石" NOR, ({ "flawless diamond" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIW "一颗精光闪闪的精美钻石，华丽异常。"NOR"\n");
		set("base_value", 100000);
		set("base_weight", 1);
		set("base_unit", "颗");
		set("no_give",1);
		set("no_drop",1);
		set("no_get",1);
        set("no_sell",1);
		set("can_be_enchased", __DIR__"mdiamond");
		set("enchased_need", 3);
		set("magic/type", "lighting");
		set("magic/power", 100);
	}
	set_amount(1);
	setup();
}
