//ÁùÂöÉñ½£-ÁùÂö½£Æøpfm±¦Ê¯

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
	set_name(HIM "ÈÚÑ©" NOR, ({ "ronxue gem" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIM "Ò»¿é´¿°×É«µÄ±¦Ê¯¡£"NOR"\n");
		set("base_value", 20000);
		set("base_weight", 1);
		set("base_unit", "Æ¬");
		set("no_sell",1);
        set("no_give",1);
        set("no_drop",1);
        set("no_get",1);
        set("no_teal", 1);
		set("can_be_inlay",([
		"name":"ÈÚÑ©",
		"skill":"liuyang-zhang-rx",
		])
		);
	}
	set_amount(1);
	setup();
}
