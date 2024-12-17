#include <ansi.h>
#include <weapon.h>
inherit BLADE;

void create()
{
        set_name(NOR + HIC "暗月刀" NOR, ({ "anyue dao", "anyue", "dao" }));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("no_sell",1);
                set("no_drop",1);
                set("no_give",1);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一声抽出一把$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n插回刀鞘。\n");
        }
        init_blade(500);
        setup();
}
