
#include <weapon.h>
#include <ansi.h>

inherit BLADE;

void create()
{
        set_name(HIY "����֮��" NOR, ({ "jueming zhiren",}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIY "����һ������������ۼ����ɵķ���֮�У��ƺ���Ӧ�������˼䡣\n" NOR);
                set("value", 1);
                set("material", "steel");
                set("wield_msg", "");
                set("unwield_msg", "");
        }
        init_blade(100);
        setup();
}

