// fumo.c ���ݷ���

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"����"; }
string *pfm_type() { return ({ "club", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;
	int damage;
 
	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("�����ݷ��꡹ֻ����ս���жԶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	      (string)weapon->query("skill_type") != "club")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if (me->query_skill("force") < 200)
		return notify_fail("����ڹ�����Ϊ����������ʹ����һ������\n");

	if (me->query_skill("qiyang-luoyuqiang", 1) < 400)
		return notify_fail("�����������ǹ��Ϊ������Ŀǰ����ʹ�ÿ��ݷ��꣡\n");

	if (me->query("neili") < 800)
		return notify_fail("�����������������ʹ�ÿ��ݷ��꣡\n");

	if (me->query_skill_mapped("club") != "qiyang-luoyuqiang")
		return notify_fail("��û�м�����������ǹ������ʹ�ÿ��ݷ��꣡\n");

	if (me->query("int") < 30)
		return notify_fail("�����Բ��㣬���������ݷ���ľ��衣\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "��ɫ����,���е�" + weapon->name() +
	      HIY "��ͬ��籩���������ǰ��\nһʱ������ǹӰ��������ס$n" + HIY "��"NOR"\n";

	ap = me->query_skill("qiang");

	ap += me->query_skill("club"); 
	dp = target->query_skill("force");

	if (ap / 2 + random(ap) > dp)
	{
		int attack_time,i;

		attack_time = (me->query_skill("qiang") + me->query_skill("club")) / 100;


		damage = ap + random(ap);

		damage *= 2;

		me->add_temp("apply/attack", ap);

		me->add("neili", -2000);
		me->start_busy(1);

		for (i = 0; i < attack_time; i++)
		{
			if (! me->is_fighting(target))
				break;
			COMBAT_D->do_attack(me, target, weapon, 0);
		}

		me->add_temp("apply/attack", -ap);

		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 65,
					   HIR "���ֻ��$p" HIR "ȫ�����������˿ڣ�ǹ����$P"
					   "���ϴ������о���Ҫ������Ѫ��ֹ��"NOR"\n");

	} else
	{
		me->add("neili", -1000);
		me->start_busy(2);
		msg += CYN "����$p" CYN "ȫ���ڹ���������$P"
		       CYN "���������徹Ӳ�����ĵ�ס��$P" CYN "��籩���Ĺ�ʽ��"NOR"\n";
	}
	message_combatd(msg, me, target);

	return 1;
}
