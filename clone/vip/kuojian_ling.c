
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
	set_name(HIR "������" NOR, ({"kuojian ling"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "��������ڰ�������İ��������\n");
		set("base_unit", "��");
//		set("no_shop", 1);
		set("yuanbao", 500);
		set("base_value", 50000);
		set("base_weight", 1);
	}
	setup();
}
