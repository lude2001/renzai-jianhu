#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(HIC "��������" NOR, ({ "landie jian", "landie", "jian" }));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIC "����һ��������˵�ı�������������ɾ����������ӵ������������ɰ����������������̲��ž޴��������\n" NOR);
                set("no_sell",1);
                set("no_drop",1);
                set("no_give",1);
                set("material", "steel");
                set("wield_msg", "һ����ɫ�Ľ�â������ֻ����â����һֱ��ɫ�ĺ�������â��ȥ$N" HIC "����ȴ����һ�ѱ�����\n");
                set("unwield_msg", HIC "$N" HIC "һ����̾��$n����һ����ɫ������ʧ�ˡ�\n" NOR);
        }
        init_sword(2000);
        setup();
}
