#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(NOR + CYN "���" NOR, ({ "qinggang jian", "qinggang", "jian" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", NOR + CYN "����һ����������ͭ����ɵı�������Ϊ������\n" NOR);
                set("material", "steel");
                set("wield_msg", "$N��ৡ���һ�����һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n��ؽ��ʡ�\n");
                set("value", 100000);
        }
        init_sword(300);
        setup();
}

int query_autoload()
{
        return 1;
}