// bigaxe
#include <ansi.h>
#include <weapon.h>
inherit AXE;
void create()
{
        set_name(HIW "�޸�" NOR, ({"big axe","axe"}));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "�����̹���������ٵصľ޸�����˵�������������\n");
                set("flag", 1);
                set("no_sell",1);
                set("no_drop",1);
                set("no_give",1);
                set("material", "steel");
                set("wield_msg", "$N�ӱ��ϰγ�һ��"+HIW+"�޸�"+NOR+"���������С�\n");
                set("unwield_msg", "$N��һ��"+HIW+"�޸�"+NOR+"���ڱ��ϡ�\n");
        }  
        init_axe(1000);
        setup();
}   