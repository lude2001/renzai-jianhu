// l��������ս���ܱ�ר�ù�

#include <ansi.h>

inherit __DIR__"bow";

void create()
{
        set_name(HIW "��Į֮ӥ" NOR, ({ "damo bow", "bow", "damo", "gong" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "��");
                set("long", HIW "һ���ûƽ����ĳ�������������һֻ�����ӥ���˹����Դ�Į�����񹭡�\n");
                set("value", 80000);
                set("accuracy", 100000);   // ׼ȷ�ȣ�����100%����
        }
        setup();
}

