// longsword.c ����

#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(HIR "ն��֮��" NOR, ({ "zhantian zhiren", "zhantian", "zhiren" }));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIR "��˵ն��֮�п��Կ���ٵأ��������ף��������ܡ�\n" NOR);
                set("no_drop",1);
                set("no_give",1);
                set("material", "tian jing");
                set("wield_msg", HIR "��ৡ���һ�����һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n��ؽ��ʡ�\n");
        }
        init_sword(1000);
        setup();
}
