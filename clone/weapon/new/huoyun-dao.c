#include <ansi.h>
#include <weapon.h>
inherit BLADE;

void create()
{
        set_name(NOR + HIR "���Ƶ�" NOR, ({ "huoyun dao", "huoyun", "dao" }));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("no_sell",1);
                set("no_drop",1);
                set("no_give",1);
                set("material", "steel");
                set("wield_msg", "$N��ৡ���һ�����һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n��ص��ʡ�\n");
        }
        init_blade(1200);
        setup();
}

