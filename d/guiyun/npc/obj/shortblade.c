// shortblade.c

#include <weapon.h>

inherit THROWING;

void create()
{
	set_name("�̵�", ({ "short blade", "dao" }));
	set_weight(7000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("value", 0);
		set("base_unit", "��");
	      set("icon", "05049");
		set("base_weight", 300);
		set("base_value", 0);
		set("material", "iron");
		set("unit", "��");
		set("long", "����һ���ɵ���\n");
		set("value", 1000);
		set("material", "steel");
	}
	set_amount(18);
	init_throwing(25);
	setup();
}
