#include <ansi.h>
#include <weapon.h>
inherit BLADE;

void create()
{
        set_name(NOR + WHT "���µ�" NOR, ({ "ningyue dao", "ningyue", "dao", "blade" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", NOR + WHT "����һ�����λεı��������¹����Եø���ҫ�ۡ�\n" NOR);
                set("material", "steel");
                set("wield_msg", "$N��ৡ���һ�����һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n��ص��ʡ�\n");
                set("no_sell",1);
                set("no_drop",1);
                set("no_give",1);
        }
        init_blade(500);
        setup();
}