#include <ansi.h>
#include <combat.h>

#define SHENG "��" HIW "��������ҹ" NOR "��"
string query_name() { return "����"ZJBR"����ҹ"; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
                int i,lvl;
                lvl = me->query_skill("taisu-moon",1);

        if (! target) target = offensive_target(me);
        
        if( me->query_temp("weapon") || me->query_temp("secondary_weapon") )
                return notify_fail(query_name() + "ֻ�ܿ���ʹ�á�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(SHENG "ֻ����ս���жԶ���ʹ�á�\n");

        if (me->query_skill("taisu-moon", 1) < 150)
                return notify_fail("���̫������ʽ��Ϊ������Ҫ��150����������ʩչ" SHENG "��\n");

        if (me->query_skill_mapped("cuff") != "taisu-moon")
                return notify_fail("��û�м���̫������ʽ��������ʩչ" SHENG "��\n");

        if( me->query("neili")<400 )
                return notify_fail("������������Ҫ��400������������������ʩչ" SHENG "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "�����죬˫ȭ����������Ӱ��ͻȻ���飡�飡�������͵�ȭ������������$n" HIY "��\n" NOR;

        message_combatd(msg, me, target);

                me->add("neili", -200);

        me->start_busy(1 + random(4));

                for (i = 0; i < 6+random(lvl/100); i++)//��Ч1:���ʴ���������
                {
                        if (! me->is_fighting(target))break;

                        if (random(2))target->start_busy(1);//��Ч2������æ�ҶԷ�
                        if (!random(10))target->add("eff_qi",-lvl);//��Ч3�����ʴ���Է���Ѫ��
                        COMBAT_D->do_attack(me, target, weapon, 0);
                }


        return 1;
}
