// �ܱ�ר�ü�
 
#include <weapon.h>
#include <ansi.h>

inherit THROWING;

int is_arrow() { return 1; }
int is_arrow_zhebie() { return 1;} // ���� /clone/weapon/bow.c ����

void create()
{
        set_name(HIR "������" NOR, ({ "arrow", "jian" }));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIR "һ���������ë���ɵļ��������ޱȣ�ֻ���ɹ��ܱ����ӵ�С�\n" NOR);
                set("unit", "��");
                set("base_unit", "��");
                set("base_weight", 100);
                set("base_value", 200);
                       set("wound_percent", 300);                       
        }

        set_amount(1);
        init_throwing(3000);
        setup();

        set("no_wield", "�ⲻ������װ���ġ�\n");
}
