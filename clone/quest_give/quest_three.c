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
	set_name(HIC"����������ٿ�"NOR, ({"three card"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
	set("long", "����һ�����Լ��������ܻ�����ļ��ٿ���\n");
		set("base_unit", "��");
		set("base_value", 5000);
         set("no_sell",1);
		set("base_weight", 1);
	    set("quest_level", 3);
	}
	set_amount(1);
	setup();
}
