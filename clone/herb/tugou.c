// tugou.c

#include "herb.h"

void create()
{
	set_name(YEL "����" NOR, ({ "tu gou", "herb_tugou" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "������ҩҩ�ġ�\n");
		set("base_unit", "��");
		set("base_value", 8000);
		set("base_weight", 80);
	}
	setup();
}
