// jinsheng by yushu 2001.2
#include <ansi.h>
inherit F_SSERVER;
string query_name() { return "����" ZJBR "����"; }
int perform(object me, object target)
{
        string msg;
        object weapon;
        int damage, qi, ap, dp, qixue, eff_qi, max_qi, qi_pcg;

        weapon = me->query_temp("weapon");

        if (!target)
                target = offensive_target(me);

        if (!target || !target->is_character() || !me->is_fighting(target) || !living(target))
                return notify_fail(HIW "��ֻ����ս����ʹ�á�\n" NOR);

        qi = me->query("eff_jing");

        if (me->query("family/family_name") != "��ɽ��")
                return notify_fail("������ɽ�Ĳ����á�������������\n");

        //    if(me->query("shushan/jinsheng_perform")!=1)
        //           return notify_fail("�㻹û��ᡸ������������\n");

        if ((int)me->query("max_neili") < 100000)
                return notify_fail("����ڹ�̫�\n");

        if ((int)me->query_skill("martial-cognize") < 300)
                return notify_fail("�����ѧ�������㡣\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("����������㣡\n");

        if ((int)me->query_skill("sword", 1) < 120)
                return notify_fail("��Ļ��������ȼ�����������ʹ����һ�У�\n");

        me->set("jing", 0);
        me->set("eff_jing", 0);
        me->set("qi", 0);
        me->set("eff_qi", 0);
        me->set("neili", 0);

        message_vision(HIB "\n$N�ۼ����У������˷�����������ʫ������Ĭ�", me, target);
        message_vision(HIG "\n\n���е���һ�ж�ֻ�еȴ�������......", me, target);
        message_vision(HIB "\n\n$Nһ��ˣ�������" + weapon->name() + NOR + HIB "��Ϊһ��ֱ��$n���������� \n\n" NOR, me, target);

        ap = me->query_skill("sword");
        ap = ap * ap * ap / 10;
      //  ap = ap + (int)me->query("combat_exp");
        dp = target->query_skill("dodge");
        dp = dp * dp * dp / 10;
       // dp = dp + target->query("combat_exp");
        dp = dp * qi_pcg / 50;
        if (random(2) + (random(ap + dp) < dp))
        {
                message_vision(HIB "\n\n$nһ�����Ʋ��ƴ�������Խ����Ȼ���Ǳ�����֮�ʽ��ҵض������ƴ����һʽ������\n\n" NOR, me, target);
                target->start_busy(5 + random(3));
        }
        else
        {
                target->die();
                message_vision(HIB "\n\n$n����$N��˾�������Ȼ����������˲��һ����������$n���ϵ��ش���������\n\n" NOR, target, me);
        }
        message_vision(HIR "\n\n����д���һ����̾������ҡ��������� \n\n" NOR, me);
        me->unconcious();
        return 1;
}
