//bingfu.c

#include <armor.h>

inherit CLOTH;

void create()
{
	set_name("����", ({"cloth", "bingfu"}));
	set_weight(3000);
	if (clonep())
		set_default_object(__FILE__);
	else 
	{
		set("long", "һ��������ǰ����ͭ�����ģ��м�����һ�����֣�\n");
		set("material", "cloth");
		set("value", 300);
		set("unit", "��");
		set("armor_prop/armor", 10);
	}
	setup();
}