#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(HIR "�㽣" NOR, ({ "chi jian" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", NOR + HIR "����һ�ѻ�����Ľ����������ио������ޱȡ�\n" NOR);
                set("material", "tian jing");
                set("wield_msg", "$N��ৡ���һ�����һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n��ؽ��ʡ�\n");
                set("value", 100000);
        }
        init_sword(300);
        setup();
}
