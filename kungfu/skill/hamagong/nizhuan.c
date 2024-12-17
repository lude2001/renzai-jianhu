// This program is a part of NITAN MudLIB
// nizhuan.c

#include <ansi.h>

inherit F_CLEAN_UP;
string query_name() { return "����"ZJBR"����"; }
void remove_effect(object me, int amount);

int exert(object me, object target)
{
        object weapon;
        int skill;
        string msg;

        if((int)me->query_skill("hamagong", 1) < 200)
                return notify_fail("��ĸ�󡹦������죬������ת������\n");

        if( me->query("neili")<500 )
                return notify_fail("�������������\n");

        if( me->query("jingli")<500 )
                return notify_fail("��ľ���������\n");

        if( me->query_temp("hmg_nizhuan") )
                return notify_fail("���Ѿ������˾�����\n");

        skill = me->query_skill("hamagong", 1);
        msg = HIB "$N" HIB "˫�ֳŵأ����з���һ���ܵͺ�����һ�ɹ��ھ�����ʹ$N" HIB "˫����أ���ͷ������֮�ơ���\n" NOR;
        message_combatd(msg, me);
        tell_object(me, HIW "��о����ڸ�󡹦�������ת�������йɾ޴������Ҫ��������һ����\n" NOR);

        me->add_temp("apply/ap_power", 50);
        me->add_temp("apply/add_damage", 50);
        me->add_temp("apply/attack", skill);
        me->add_temp("apply/avoid_xuruo", 50);
        me->add_temp("apply/str", skill/10);
        me->set_temp("hmg_nizhuan", skill);
        me->add("neili", -300);
        me->add("jingli", -50);
        me->start_call_out( (: call_other, this_object(), "remove_effect", me, skill :), skill);
        if(me->is_fighting())
                me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( !me ) return;

        me->add_temp("apply/str", -amount/10);
        me->add_temp("apply/attack", -amount);
        me->add_temp("apply/ap_power", -50);
        me->add_temp("apply/add_damage", -50);
        me->add_temp("apply/avoid_xuruo", -50);
        me->delete_temp("hmg_nizhuan");

        tell_object(me, HIW "����ת�����˹����ã������ֽ�����ԭ��\n" NOR);
}
