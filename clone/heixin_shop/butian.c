// butian.c ����ʯ

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIM "����ʯ����" NOR, ({"magic stone", "butian shi", "shi"}));
	set_weight(6000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "��˵����Ů洲���ʣ�µ����ʯ����֪�����Ǽ١���������װ����\n");
		set("spectxt", "����װ���Ĳ��ϡ�\n");
		set("unit", "��");
		set("value", 8000000);
		set("yuanbao", 800);
		set("no_sell",1);
        set("no_give",1);
		set("no_put", 1);
        set("no_drop",1);
        set("no_get",1);
        set("no_teal", 1);
		set("item_origin", 1);
		set("material_attrib", "magic stone");
		set("material_name", HIM "����" NOR);
		set("can_make", "all");
		set("not_make", ({ "ս��", "����", "����" }));
		set("power_point", 100);
	}
}

int query_autoload() { return 1; }