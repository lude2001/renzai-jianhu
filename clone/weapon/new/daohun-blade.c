
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
                set("no_sell",1);
                set("no_drop",1);
                set("no_give",1);
                set("material", "steel");
        }
        init_blade(800);
        setup();
}

