// ��ʮ��������ҹ by ����ҹ��

#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
//#include <balance.h>

#define HUN "��" HIW "��ʮ��������ҹ" NOR "��"
string query_name() { return "��ʮ����"ZJBR"����ҹ"; }
string final(object me, object target, int damage);

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage;

        if (! target)target = me->select_opponent();

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(HUN "ֻ�ܿ���ʩչ��\n");

        if (me->query_skill("taisu-moon", 1) < 300)
                return notify_fail("���̫������ʽ��������죬����ʩչ" HUN "��\n");

        if (me->query_skill_mapped("cuff") != "taisu-moon")
                return notify_fail("������û�м���̫������ʽΪȭ��������ʩչ" HUN "��\n");

        if (me->query_skill_mapped("force") != "taisu-force")
                return notify_fail("������û�м���̫���ľ�Ϊ�ڹ�������ʩչ" HUN "��\n");

        if (me->query_skill_mapped("dodge") != "taisu-dodge")
                return notify_fail("������û�м���ʹ��̫�����粽������ʩչ" HUN "��\n");

        if (me->query("neili") < 600)
                return notify_fail("�����������������ʩչ" HUN "��\n");
 
        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIG "\n$N" HIG "˫�ֺ�ʮ��˫Ŀ΢�գ�̫���������ĵ�ӿ������Ȼ�䣬$N"
              HIG "˫������ӿ���������������գ������ǰ������һ�����ҵ�ȭ������$n " HIG "��\n" NOR;
 
        ap = me->query_skill("cuff")*2 + me->query("str") * 15;

        dp = target->query_skill("force") + target->query("con") * 10;

        me->add("neili", -500);

        if (ap / 2 + random(ap) < dp)
        {
        target->add("neili",-500);//���ʧ�ܣ�����Է����������ĵ�ͬ����
                msg += HIY "Ȼ��$n" HIY "����ȫ������ȫ���ֵ������ڽ�$N" HIY
                       "������ȭ����ס��\n" NOR;
                me->start_busy(2);
        } else
        {
                me->add("neili", -1000);
                me->start_busy(3);
                damage =me->query_skill("taisu-moon",1)+me->query_skill("taosu-dodge",1)+me->query_skill("taisu-force",1);//�����˺�Ϊ̫��ȫ�ס�
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60 + random(5),
                                           (: final, me, target, damage :));

        }
        message_sort(msg, me, target);
        return 1;
}


string final(object me, object target, int damage)
{
        target->receive_damage("jing", damage / 2, me);
        target->receive_wound("jing", damage / 3, me);
        target->busy(2);
        return  HIR "$n" HIR "��æ��ܣ�����ȭ����"
                "�ü��켫�ͣ�ֻ��$p" HIR "һ���ҽУ�һ��ȭ"
                "���Ѿ��������ڣ���ʱ�ⲿ��Ѫ�ɽ���$n" HIR "��"
                "����ʹ�����и�����Ѫ��ӿ������\n" NOR;
}

