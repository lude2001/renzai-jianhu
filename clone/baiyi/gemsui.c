// jinsha.c

#include <ansi.h>
inherit COMBINED_ITEM;
string query_autoload() { return query_amount() + ""; }

void autoload(string param)
{
	int amt;

	if (sscanf(param, "%d", amt) == 1)
		set_amount(amt);
}

void setup()
{
	set_amount(1);
	::setup();
}

void create()
{
	set_name(HIW "宝石碎片" NOR, ({ "gem suipian" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "用来合成宝石的宝石碎片。\n");
		set("base_unit", "粒");
		set("base_value", 500);
		set("yuanbao", 10);
		set("base_weight", 1);
	}
	setup();
}

