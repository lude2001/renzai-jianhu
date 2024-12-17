inherit ITEM;
#include <ansi.h>

void create()
{
	set_name("ÖìÉ°", ({"zhu sha"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("value", 1000000);
		set("unit", "¹Ş");
		set("long","Ò»¹ŞÓÃÀ´»­·ûµÄÖìÉ°¡£\n");
	}
}

int query_autoload() { return 1; }
