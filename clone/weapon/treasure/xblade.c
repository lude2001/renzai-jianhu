// xue-dao.c Ѫ��
// Last Modified by winder on Sep. 7 2001

#include <ansi.h>;
#include <weapon.h>;
inherit BLADE;
inherit F_UNIQUE;

void create()
{
        set_name( HIR"Ѫ��"NOR , ({ "blood blade", "blade", "dao" }));
        set_weight(30000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIR "����һ�Ѳ�������ı�����������ŵ�����ѪӰ��\n" NOR );
                set("value", 1000);
                set("material", "steel");
                set("wield_msg", "$N��ৡ���һ�����һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n��ص��ʡ�\n");
        }
        init_blade(200);
        setup();
}
/*
void init()
{
        add_action("do_wield", "wield");
        add_action("do_unwield", "unwield");
}

int do_wield(string arg)
{
        object me=this_player();

        object ob;
        string str;
        int i, count;

        if (!id(arg)) return notify_fail("��Ҫװ��ʲô��\n");

        if( !objectp(ob = present(arg, me)) )
                return notify_fail("������û������������\n");

        if( query("equipped", ob) )
                return notify_fail("���Ѿ�װ�����ˡ�\n");


        if( ob->wield() ) {
              if( !stringp(str=query("wield_msg", ob)) )
                        str = "$Nװ��$n��������\n";
              message_vision(str, me, ob);
              if ( me->query_skill("xue-dao")
              && me->query_skill_mapped("blade") == "xue-dao" )
                        addn_temp("apply/damage", 380, me);

              return 1;
        }
        else
                return 0;
}

int do_unwield(string arg)
{
        object me=this_player();
        object ob, *inv;
        string str;
        int i;

        if( !arg ) return notify_fail("��Ҫ�ѵ�ʲô��\n");

        if( !objectp(ob = present(arg, me)) )
                return notify_fail("������û������������\n");

        if( query("equipped", ob) != "wielded" )
                return notify_fail("�㲢û��װ������������Ϊ������\n");

        if( ob->unequip() ) {
                if( !stringp(str=query("unwield_msg", ob)) )
                        str = "$N�������е�$n��\n";
                message_vision(str, me, ob);
                if ( me->query_skill("xue-dao")
                        && me->query_skill_mapped("blade") == "xue-dao" )
                        addn_temp("apply/damage", -380, me);
                return 1;
        } else return 0;
}
*/