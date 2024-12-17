// agate.c Âêè§

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
	set_name(HIR "Âêè§" NOR, ({ "agate" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIR "Ò»¿é¾§Ó¨ÌŞÍ¸µÄ°µºìÉ«Âêè§¡£"NOR"\n");
		set("base_value", 50000);
		set("base_weight", 1);
		set("base_unit", "¿é");
		set("no_give",1);
		set("no_drop",1);
		set("no_get",1);
        set("no_sell",1);
		set("can_be_enchased", __DIR__"fagate");
		set("enchased_need", 3);
		set("magic/type", "fire");
		set("magic/power", 100);
	}
	set_amount(1);
	setup();
}
