// zu.c  by sinb

#include <ansi.h>

inherit F_CLEAN_UP;
string query_name() { return "̫��" ZJBR "��Ѫ"; }
int hui(object me, int skill);
int exert(object me, object target)
{
        int skill;
        if (me->query("eff_qi") >= me->query("max_qi"))
        {
                me->delete_temp("taisu");
                return notify_fail("��û�����ˣ�\n");
        }
        if (target != me)
                return notify_fail("��ֻ����̫���ľ��ָ��Լ�����Ѫ��\n");
        if ((int)me->query("neili") < 1000)
                return notify_fail("�������������\n");

        if (me->query_temp("taisu"))
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("taisu-force", 1);
        me->set_temp("taisu", 10);
        if (!me->is_fighting())
        {
                hui(me, skill);
        }
        else
        {
                call_out("hui", 5, me, skill);
                write("���ܵ��������Ѫ�����ܵ��ӳ�ѹ��\n");
        }
        return 1;
}

int hui(object me, int skill)
{
        if (me->query("eff_qi") >= me->query("max_qi"))
        {
                me->delete_temp("taisu");
                return notify_fail("��û�����ˣ�\n");
        }
        if (!me->query_temp("taisu"))
                return notify_fail("���Ѿ����˹���ϡ�\n");
        message_combatd(HIC "$N" HIC "���𡸻�Ѫ��������"
                            "��������һƬ��â���漴�ָ�����\n" NOR,
                        me);
        me->add("neili", -skill);
        me->add("eff_qi", skill);
        me->add("qi", skill);
        me->add_temp("taisu", -1);
        call_out("hui", 5, me, skill);
        return 1;
}