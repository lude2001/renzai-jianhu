//baijie.c

#include <armor.h>

inherit FINGER;

void create()
{
	set_name("�׽��ָ", ({ "bai jie", "baijie", "ring" }));
	set("weight", 400);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "��");
		set("value", 10000);
		set("material", "gold");
		set("armor_prop/armor", 1);
		set("armor_prop/personality", 1);
	}
	setup();
}
