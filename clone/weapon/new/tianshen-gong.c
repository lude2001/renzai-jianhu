// longbow.c

#include <ansi.h>

inherit __DIR__"bow";

void create()
{
        set_name(HIY "����" NOR, ({ "tianshen gong", "bow", "tianshen", "gong" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "��");
                set("long", "����һ�ž޴�Ĺ�����Ի�����񣬴�˵���������ɼ�˼���ı����˵�˹��ٷ����У������鷢����\n");
                set("value", 10000);
                set("accuracy", 2000);   // ׼ȷ��150%
        }
        setup();
}
