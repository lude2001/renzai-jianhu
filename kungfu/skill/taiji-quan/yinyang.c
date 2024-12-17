// yingyang ������
// updated force->neili, force_factor->jiali (by xbd)

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
string query_name() { return "������"; }
string *pfm_type() { return ({ "unarmed", }); }
string *taiji_msg = ({
    "��ȸβ",
    "����",
    "��������",
    "�׺�����",
    "§ϥ����",
    "��������",
    "��̽��",
    "����ʽ",
    "������",
    "�𼦶���",
    "��Ů����",
    "��������",
    "�乭�仢",
    "������ɽ",
});
int perform(object me, object target)
{
    string msg;
    int extra, damage;
    int orforce;
    object weapon;
    int force;
    string *limbs;
    object *obs = me->query_enemy();
    int mz = me->query_skill("force") / 2 + random(me->query_skill("force") / 2 + me->query_skill("martial-cognize", 1) / 2);
    if (me->is_busy())
        return notify_fail("������û�գ���\n");
    if ((int)me->query("neili") < 2000)
        return notify_fail("�������������\n");

    if ((int)me->query("neili") < me->query("max_neili") / 7 + 200)
        return notify_fail("�������������\n");

    if (!wizardp(me) && (int)me->query_skill("taiji-quan", 1) < 500)
        return notify_fail("��ı����⹦��̫��ȭ������!���ܹ�ͨʹ�ã�\n");

    if (!wizardp(me) && (int)me->query_skill("taiji-jian", 1) < 500)
        return notify_fail("��ı����⹦(̫����)����!���ܹ�ͨʹ�ã�\n");
        
    if (!wizardp(me) && (int)me->query_skill("martial-cognize", 1) < 300)
    return notify_fail("�����ѧ��������!���ܹ�ͨʹ�ã�\n");

    if (!wizardp(me) && (int)me->query_skill("taiji-shengong", 1) < 500)
        return notify_fail("��ı����ڹ���̫���񹦣�������!���ܹ�ͨʹ�ã�\n");

    if (!wizardp(me) && me->query_skill_mapped("force") != "taiji-shengong")
        return notify_fail("��ʹ�ñ����ڹ������ʹ�ñ��ž�ѧ!\n");

    extra = 100 + me->query_skill("unarmed") / 3 * 2 + me->query_skill("martial-cognize", 1);
    if (!target)
        target = offensive_target(me);
    if (!target || !target->is_character() || !me->is_fighting(target))
        return notify_fail("���ž�ѧֻ�ܶ�ս���еĶ���ʹ�á�\n");

    //me->add("jiali", extra / 3);
    
    if (!playerp(target))
    {
        mz *= 2;
        extra *= 3;    
    }
    
    orforce = (int)me->query("force");
    weapon = me->query_temp("weapon");
    me->add_temp("apply/attack", extra / 6);
    me->add_temp("apply/damage", 300);

    msg = HBWHT "$N��ͨ�䵱��ѧ��ʹ�����䵱�ľ�ѧ֮���裡\n" NOR;
    message_vision(msg, me, target);



    if (random(2) == 0)
        target->start_busy(3);
  
    if (mz > target->query_skill("force"))
    {
        int qi;

        qi = target->query("qi");
        
        for (int i = 0; i < 6; i++)
    	{
    		if (! me->is_fighting(target))
    			break;
    		if (random(5) < 2 && ! target->is_busy())
    			target->start_busy(1);
    
    		COMBAT_D->do_attack(me, target, 0, 0);
    	}
    	
        msg = MAG "$N˫�ֱ��˸�̫��ʽ��ԲȦ����������̫�����Ѵ������һ���Ķ������ľ��磬��\n" NOR;
        message_vision(msg, me, target);
        msg = WHT "���һ���������" NOR;
        msg += HIY "\n���$n��ɫһ�±�òҰף��������������˺ü�����\n" NOR;
        message_vision(msg, me, target);
        msg = MAG "���һ���������" NOR;
        msg += HIY "\n���$n��ɫһ�±�òҰף��������������˺ü�����\n" NOR;
        target->receive_wound("qi", random(extra) + extra / 2 ,me);
        message_vision(msg, me, target);
        msg = WHT "��������������" NOR;
        msg += HIY "\n���$n��ɫһ�±�òҰף��������������˺ü�����\n" NOR;
        message_vision(msg, me, target);
        msg = MAG "��������������" NOR;
        msg += HIY "\n���$n��ɫһ�±�òҰף��������������˺ü�����\n" NOR;
        target->receive_wound("qi", random(extra) + extra / 2 ,me);
        message_vision(msg, me, target);
        msg = WHT "��������������" NOR;
        msg += HIY "\n���$n��ɫһ�±�òҰף��������������˺ü�����\n" NOR;
        message_vision(msg, me, target);
        msg = MAG "��������������" NOR;
        msg += HIY "\n���$n��ɫһ�±�òҰף��������������˺ü�����\n" NOR;
        target->receive_wound("qi", random(extra) + extra / 2 ,me);
        message_vision(msg, me, target);
        msg = WHT "�����Ǿ�������" NOR;
        msg += HIY "\n���$n��ɫһ�±�òҰף��������������˺ü�����\n" NOR;
        message_vision(msg, me, target);
        msg = MAG "�����Ǿ�������" NOR;
        msg += HIY "\n���$n��ɫһ�±�òҰף��������������˺ü�����\n" NOR;
        target->receive_wound("qi", random(extra) + extra / 2 ,me);
        message_vision(msg, me, target);
        msg = WHT "�������������" NOR;
        msg += HIY "\n���$n��ɫһ�±�òҰף��������������˺ü�����\n" NOR;
        target->receive_wound("qi", random(extra) + extra / 2 ,me);
        message_vision(msg, me, target);
        msg = MAG "�������������" NOR;
        msg += HIY "\n���$n��ɫһ�±�òҰף��������������˺ü�����\n" NOR;
        target->receive_wound("qi", random(extra) + extra / 2 ,me);
        message_vision(msg, me, target);

        msg = WHT "              ����˫��           !!\n" NOR;
        msg += MAG "��մ���������־��������־��������־���!!\n" NOR;
        target->receive_damage("qi", (int)me->query_skill("taiji-quan", 1) * 4,me);
        target->receive_wound("qi", (int)me->query_skill("taiji-quan", 1) * 2,me);
        if (damage < 300)
            msg += HIY "\n���$n��ɫһ�±�òҰף��������������˺ü�����\n" NOR;
        else if (damage < 400)
            msg += HIY "\n������صػ��У�$n���ۡ���һ���³�һ����Ѫ��\n" NOR;
        else if (damage < 500)
            msg += RED "\n������䡹��һ����$nȫ����Ѫ������������Ѫ���������\n" NOR;
        else
            msg += HIR "\n���ֻ���������������죬$nһ���ҽУ���̲�����������ȥ����\n" NOR;
        message_vision(msg, me, target);
        tell_object(me,HIY"�Եз����"HIR + (qi - target->query("qi")) + HIY"���˺�"NOR"��\n");
    }
    else
    message_vision(HIM "Ȼ��û���κ�������$N"
    HIM "��Ӱ�졣"NOR"\n", me, 0, obs);

    me->add_temp("apply/attack", -extra / 6);
    me->add_temp("apply/damage", -300);
    me->add("neili", -me->query("max_neili") / 7);
    me->start_busy(4);

    return 1;
}
