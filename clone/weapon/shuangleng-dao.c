#include <ansi.h>
#include <weapon.h>
inherit BLADE;

void create()
{
        set_name(NOR + CYN "˪�䱦��" NOR, ({ "shuangleng dao", "shuangleng", "dao" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", NOR + CYN "�����ϵ�С׭д�ţ�����˪ѩ������֮���������ꡣ����֮ʱ����Ѫ���飬ʮ��֮�ڣ�˭�����棡��\n"
                                                      "�˵�Ϊ�׻Ʒ��������������������λ��\n" NOR);
                set("material", "steel");
                set("wield_msg", NOR + CYN "$n����һ������Ȼ���ʡ�\n" NOR);
                set("unwield_msg", NOR + CYN "$n���ʣ���ض�ʱ������\n" NOR);
                                set("value", 100000);
        }
        init_blade(800);
        setup();
}

int query_autoload()
{
        return 1;
}