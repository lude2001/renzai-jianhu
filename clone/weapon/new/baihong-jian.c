// baihongjian.c 白虹剑
// Last Modified by winder on Sep. 7 2001

#include <weapon.h>;
inherit SWORD;
inherit F_UNIQUE;

void create()
{
        set_name("白虹剑", ({ "baihong jian", "sword", "jian" }));
        set_weight(8000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "这是一口削铁如泥的宝剑。\n");
                set("value", 10000);
                set("material", "steel");
                set("weapon_prop/per", 8);
                set("wield_msg", "$N「唰」的一声抽出一柄寒光闪闪的$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n插回剑鞘。\n");
        }
        init_sword(100);
        setup();
}