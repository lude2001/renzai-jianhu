// crossbow.c

#include <ansi.h>

inherit __DIR__"bow";

void create()
{
        set_name(HIY "�̹ž޹�" NOR, ({ "pangu gong", "pangu", "gong" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "��");
                set("long", HIY "һ�ſ��ƷǷ��ľ޹���\n" NOR);
                set("value", 50000);
                set("accuracy", 300);   // ׼ȷ��150%
        }
        setup();
}

int query_autoload()
{
        return 1;
}