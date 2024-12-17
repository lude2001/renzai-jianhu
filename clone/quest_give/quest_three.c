// build_ling.c

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
	set_name(HIC"三级任务加速卡"NOR, ({"three card"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
	set("long", "这是一个可以加速三级跑环任务的加速卡。\n");
		set("base_unit", "个");
		set("base_value", 5000);
         set("no_sell",1);
		set("base_weight", 1);
	    set("quest_level", 3);
	}
	set_amount(1);
	setup();
}
