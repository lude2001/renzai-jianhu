// mie.c  �ط��������������������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "��������"; }
string *pfm_type() { return ({
    "sword",
}); }

int perform(object me, object target)
{
    int damage;
    string msg;
    object weapon, duiyou, *team;
    int ap, dp, qixue;

    if (!target)
        target = offensive_target(me);

  //   if (!target || !me->is_fighting(target))
        // return notify_fail("������������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

    if (!objectp(weapon = me->query_temp("weapon")) ||
        (string)weapon->query("skill_type") != "sword")
        return notify_fail("ûװ������ôʹ�á�������������\n");

    if ((int)me->query_skill("huifeng-jian", 1) < 60)
        return notify_fail("��Ļط��������������죬��ʹ������������������\n");


    if (me->query_skill_mapped("sword") != "huifeng-jian")
        return notify_fail("��û�м����ط��������������ʹ�á�������������\n");

    if ((int)me->query_skill("force") < 120)
        return notify_fail("����ڹ���򲻹�������ʩչ��������������\n");

    if ((int)me->query("neili") < 200)
        return notify_fail("��������������������ʩչ��������������" NOR "\n");

    qixue = me->query_skill("huifeng-jian") + random(me->query_skill("force"));

    qixue *= 4;

    if (!weapon->query("magic/skill/huifeng-jian"))
    qixue /= 2;

    if (sizeof(team = me->query_team()))
        duiyou = team[random(sizeof(team))]; //ʲô��˼�أ��������ȡһ�����
    else
        duiyou = me;
    
    if (environment(me) != environment(duiyou))
        return notify_fail("����û���������λָ����ơ�\n");
        tell_object(environment(me),"ֻ��" + me->name() + "����һĨ" + weapon->name() + "��һ����ɫ����������" + duiyou->name() + "���ڡ���ʱ���Ƶõ��ظ���\n");
        duiyou->add("qi", qixue);
        duiyou->add("eff_qi", qixue);
        
        //��¼һ���Լ���ɵĻָ���
        me->set_temp("huifu",qixue);
        
        //���ܳ��������Ѫ
        if (duiyou->query("eff_qi") > duiyou->query("max_qi") + duiyou->query_gain_qi())
            duiyou->set("eff_qi", duiyou->query("max_qi") + duiyou->query_gain_qi());
        if (duiyou->query("qi") > duiyou->query("eff_qi"))
        duiyou->set("qi", duiyou->query("eff_qi"));
        
    skill_cd(me,"jishi", 3);
    //me->start_busy(2);
    me->add("neili", -200);
    return 1;
}
