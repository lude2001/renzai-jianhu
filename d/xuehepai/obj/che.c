inherit ITEM;
//inherit F_RIDDING;
#include <ansi.h>
void create()
{
        set_name(HIR"Ѫ�ӳ�"NOR, ({ "xuehe che","che" }));
        set_weight(10000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long","���Ǻϻ��ڵ���������--Ѫ�ӳ���\n");
                set("value",100000);
                set("no_sell",1);
                set("material", "steel");
                set("no_get","����������\n");
              }
}

void init()
{
        add_action("do_ride","ride");
        add_action("do_enter","enter");
        add_action("do_xiache","xiache");
}

int do_ride(string arg)
{
        object me;object ob;
        mapping fam,famm;
        object *obb;
        int i;
        ob=this_object();
        me=this_player();
        fam=(mapping)me->query("family");

        if( !arg || (arg!="che" && arg!="Ѫ�ӳ�") ) return notify_fail("��Ҫ���\n"); 

        if (!me->query_temp("ask1") ) {
        if (fam && fam["family_name"]=="�ϻ���" && present("ren kuang",environment(me)))
                return notify_fail("�ο�û��Ӧ���㿪�ء�\n");
       if (fam && fam["family_name"]=="�ϻ���" && ((int)me->query("combat_exp")<500000))
              return notify_fail("��ľ���̫���ˣ���ѳ�Ū���ģ�\n");
        if(!fam || fam["family_name"]!="�ϻ���") {
                message_vision("$N������ŵ����Ѫ�ӳ����ߣ�\n",me);
                obb=all_inventory(environment(me));
                for(i=0; i<sizeof(obb); i++) {
                        if (obb[i]->is_character() )
                        {
                                famm=(mapping)obb[i]->query("family");

                                if (famm && famm["family_name"]=="�ϻ���") 
                                {
                                        message_vision("$N����$n���һ��������͵�ﱾ�ɱ��\n",obb[i],me);
                                        obb[i]->kill_ob(me);
                                        me->kill_ob(obb[i]);
                                }
                        }                               
                }
                if (!(me->is_fighting()))
                {
                message_vision("$N����Χû���˺ϻ��ڵ��ӣ����Ĵ󵨵�Ծ��Ѫ�ӳ��ĳ��ᣡ\n",me);
                me->set_temp("xueheche",1);
                return 1;
                }
                return notify_fail("���ȰѺϻ��ڵ��ӽ����ȥ�ݳ�Ҳ���١�\n");
        }
        }
 
        if (me->query_temp("xueheche"))
                 return notify_fail("���Ѿ��ڳ����ˡ�\n");
        if (query("ride"))
                return notify_fail("�⳵���Ѿ�������ȥ�ˡ�\n");
        message_vision("$Nһ��Ծ��,������Ѫ�ӳ�����ǰ�����Ρ�\n",me);
        set("ride",1);
		ob->move("/d/xuehepai/tanbian");
        me->move("/d/xuehepai/tanbian");
        me->set_temp("xueheche",1);
        return 1;
}

int do_enter(string arg)
{
        object *obb;
        object me;
        mapping fam,famm;
        int i;

        me=this_player();
        fam=(mapping)me->query("family");
        
        if( !arg || (arg!="che" && arg!="Ѫ�ӳ�") ) return notify_fail("��Ҫ���\n"); 

        if (me->query_temp("xueheche"))
                return notify_fail("�����ڼݳ������ܽ����ᡣ\n");
        if(!fam || fam["family_name"]!="�ϻ���")
        {
                message_vision("$N������ŵ������Ѫ�ӳ���\n",me);
                obb=all_inventory(environment(me));
                for(i=0; i<sizeof(obb); i++) {
                        if (obb[i]->is_character() )
                        {
                                famm=(mapping)obb[i]->query("family");

                                if (famm && famm["family_name"]=="�ϻ���") 
                                {
                                        message_vision("$N����$n���һ��������͵�ﱾ�ɱ��\n",obb[i],me);
                                        obb[i]->kill_ob(me);
                                        me->kill_ob(obb[i]);
                                }
                        }                               
                }
                if (!(me->is_fighting()))
                {
                message_vision("$N����Χû���˺ϻ��ڵ��ӣ����Ĵ󵨵Ľ���Ѫ�ӳ���\n",me);
                me->move("/d/xuehepai/chenei");
                }
                return notify_fail("���ȰѺϻ��ڵ��ӽ�����ٽ�ȥҲ���١�\n");
        }
        message_vision("$N��ҡ��ڵ������Ѫ�ӳ���\n",me);
        me->move("/d/xuehepai/chenei");
        return 1;
}

int do_xiache()
{
        object ob;
        mapping fam;
        
        ob=this_player();
        fam=(mapping)ob->query("family");

        if (!(ob->query_temp("xueheche")))
                return notify_fail("ʲô��\n"); 

        if (environment(this_object())!=environment(ob))
                return notify_fail("ʲô��\n"); 

        message_vision("$Nһ��Ծ��,��Ѫ�ӳ�����ǰ������������������\n",ob);
        message_vision(HIG"Ȼ��$N����з���һ�������֪ͨ����ȡ��Ѫ�ӳ���\n"NOR,ob);
        message_vision(HIY"ͻȻ�������Ӷ�$N���ͷ����Ѫ�ӳ�����ȥ�ˡ�\n"NOR,ob);

        this_object()->move("/d/xuehepai/xueheting");

        set("ride",0);
        ob->delete_temp("xueheche");
        ob->delete_temp("ask1");
        return 1;
}

