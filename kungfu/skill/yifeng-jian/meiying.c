#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;
string query_name() { return "����"ZJBR"��Ӱ"; }
int perform(object me, object target)
{
      int damage, damage2;
        string msg,wn;
        object weapon;

        if (!target ) target = offensive_target(me);
        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
        return notify_fail(RED"��ʲô��Ц��ûװ��������ʹ��������Ӱ����\n"NOR);
      if (!target || !target->is_character() || !me->is_fighting(target) )
        return notify_fail("��������Ӱ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
      if ((int)me->query_skill("yifeng-jian", 1) < 150 )
        return notify_fail(WHT"����Ʒ罣��������죬��ʹ������������Ӱ����\n"NOR);
      if ((int)me->query_skill("sword", 1) < 150 )
        return notify_fail(WHT"���������ò�����������ʹ����������Ӱ����\n"NOR);
      if ((int)me->query_skill("force", 1) < 100 )
        return notify_fail(RED"����ڹ�����������ˣ������������Ӱ����\n"NOR);
      if ((int)me->query_skill("dodge", 1) < 100 )
        return notify_fail(RED"��������������������򲻵���������Ӱ����\n"NOR);
      if ((int)me->query("max_neili")<500)
        return notify_fail(RED"���������Ϊ���㣬�޷����㡸������Ӱ����������\n"NOR);
      if ((int)me->query("neili")<200)
        {
        return notify_fail(HIC"����������������û�ܽ���������Ӱ��ʹ�꣡\n"NOR);
        }

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");
        wn = weapon->name();

        msg = HIC "\n$N" HIC "��Ȼ����̬��ǧ������Ʈ�ݣ�����һ�����"
              "���˵�Ů�����������һ����\n����$N����" + wn + HIC "ȴ"
              "������������ӯ�ػζ������ƺ����·���ȴ��������������"
              "������ʽ��\n" NOR;
		if (random(me->query_skill("force"))>target->query_skill("force")/3)
        {
                me->start_busy(2);
                target->start_busy(random(3));
				damage = (int)me->query_skill("yifeng-jian", 1)*5+(int)me->query_skill("force",1)*2;
				damage = damage + random(damage);
				if (damage<target->query("max_qi",1)/8 && me->query("max_neili",1) > target->query("max_neili",1)/2) damage = random (target->query("max_qi",1)/5);
				if (damage>target->query("max_qi",1)/3) damage = random (target->query("max_qi",1)/3);


				// damage2 = (int)me->query_skill("yifeng-jian", 1)*5+(int)me->query_skill("force",1)*2;
				// damage2 = damage2 + random(damage2);
                target->receive_damage("qi", damage/2, me);
                target->receive_wound("qi", damage/2, me);
				msg += HIY"$n����$N��һ������ۣ�ȫȻ�޷��ֵ���һ���֮���Ѿ�����һ���̵���Ѫ�ɽ���\n"NOR;
				me->add("neili", -50);
        } else
        {
            me->start_busy(random(3));
                msg += CYN "����$n" CYN "������$N" CYN "���������У���"
                      "ʱһ˿���ң���������\n" NOR;
                me->add("neili", -50);
        }
		message_combatd(msg, me, target);
//        if(!target->is_fighting(me)) target->fight_ob(me);
//      if(userp(target)) target->fight_ob(me);
//      else if( !target->is_killing(me) ) target->kill_ob(me);
        return 1;
}

