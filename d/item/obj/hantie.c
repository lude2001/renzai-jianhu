// hantie.c ��������

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(WHT "��������" NOR, ({"ice steel", "han tie", "tie"}));
	set_weight(5000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ���������Ľ�������˵�����Ϲ��������������ĺ�����\n");
		set("unit", "��");
		set("yuanbao", 300);
		set("value", 10000);
		set("item_origin", 1);
		set("material_attrib", "steel");
		set("material_name", WHT "�Ϲź���" NOR);
		set("can_make", "all");
		set("not_make", ({ "��", "ս��", "����", "����" }));
		set("power_point", 70);
	}
}
int query_autoload() { return 1; }