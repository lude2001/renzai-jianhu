// zu.c  by sinb

#include <ansi.h>

inherit F_CLEAN_UP;
string query_name() { return "����"ZJBR"����"; }
int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("��ֻ�������񹦻ָ��Լ�����Ѫ��\n");

        if ((int)me->query("neili") < me->query("max_neili") / 2)
            return notify_fail("�������������\n");
            
        if ((int)me->query("jing") < me->query("max_jing") / 2)
            return notify_fail("��ľ���������\n");
            
        if (me->query_condition("mingyu_qizu"))
                return notify_fail("���Ѿ����˹����ˡ�\n");
        if (!me->is_fighting())
            return notify_fail("�������������ս����ʹ�á�\n");
        
        skill = me->query_skill("mingyu-gong", 1);

        /*me->add("neili", -1500);
        me->add("jing", -1500);*/
        
        me->add("neili", -me->query("max_neili") / 2);
        me->add("jing", -me->query("max_jing") / 2);
        me->set("eff_qi", me->query("max_qi"));     
        me->set("qi", me->query("eff_qi"));
        message_combatd(HIC "$N" HIC "�������㡹�湦��"
                        "��������һƬ��â���漴�ָ�����\n" NOR, me);


        //me->apply_condition("mingyu_qizu", skill / 100);
        if (me->is_fighting()) me->start_busy(5);

        return 1;
}

