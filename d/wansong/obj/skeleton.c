inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIW"白骨"NOR, ({ "bone" , "白骨"}) );
        set_weight(50000+random(60000));
       // set_max_encumbrance(400000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "具");
                set("long", "一具不知是小动物还是人的森森白骨。\n");
                set("value", 1);
        }
        setup();
}
int is_container() { return 1; }
