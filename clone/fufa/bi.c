inherit ITEM;
#include <ansi.h>

void create()
{
	set_name("狼毫笔", ({"langhao bi"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("value", 1000000);
		set("unit", "支");
		set("long","一支用来画符的狼毫笔。\n");
	}
}

int query_autoload() { return 1; }
