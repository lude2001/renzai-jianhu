// yi.c �򽣹���

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
string query_name() { return "��"ZJBR"����"; }
string *pfm_type() { return ({ "sword", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;
	int damage;
 
	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ�þ��С�\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("�޽���������򽣹��ڣ�\n");

	if( me->query("family/family_name") && me->query("family/family_name") != "��ɽ��" &&
	    me->query("family/family_name") != "��ɽ����" && !lv_fa(me,"��ɽ��") && !lv_fa(me,"��ɽ����"))
	{
		return notify_fail("�ǻ�ɽ�����޷�������¾Ž����⾳��\n");
	}
	
	if ((int)me->query("neili") < 200)
		return notify_fail("�����ڵ������������޷�ʹ���򽣹��ڣ�\n");

	if ((int)me->query_skill("lonely-sword", 1) < 500)
		return notify_fail("��Ķ��¾Ž��������ң��޷�ʹ���򽣹��ڣ�\n");

	if ((int)me->query_skill("sword-cognize", 1) < 500)
		return notify_fail("��Ľ��������������ң��޷�ʹ���򽣹��ڣ�\n");

	if ((int)me->query_skill("martial-cognize", 1) < 500)
		return notify_fail("�����ѧ�����������ң��޷�ʹ���򽣹��ڣ�\n");

	// if ((int)me->query_skill("sword-heart", 1) < 500)
	// 	return notify_fail("��Ľ��������������ң��޷�ʹ���򽣹��ڣ�\n");

	if (me->query_skill_mapped("sword") != "lonely-sword") 
		return notify_fail("��û�м������¾Ž����޷�ʹ���򽣹��ڣ�\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");


		msg = HIM "��Բԣ���ãã�����洫���ġ�ֻ��$N����̧����һʱ�侹���ݻ��ŵ���Ӱ���ֱ�ʹ����"NOR";\n";
		msg += "���ܾ�ʽ��������������������ͬ�ˣ�ͬ�������С�\n
		���ƽ�ʽ����ת������ת������ת�\n
		���Ƶ�ʽ���ӳ�֮��������֮������δ֮����\n
		����ǹʽ��������һ�䣬ɽ����һ�䣬ˮ����һ�䡣\n
		���Ʊ�ʽ��Ǭ���༤������༤�������༤��\n
		������ʽ�����������塢�������ɾš�\n
		������ʽ����һ�����ǣ����������������ݰ��ԡ�\n
		���Ƽ�ʽ����غ���£����º���������ʱ�����򣬹�����伪�ס�\n
		������ʽ���޽�ʤ�н�������ʤ���У��������ڽ������ƾ۳���\n
		һʱ��Ž���һ������һ�����콣��������$n��Х��ȥ��\n";

	ap = me->query_skill("lonely-sword", 1) + me->query_skill("martial-cognize", 1) / 2 + me->query_skill("sword-cognize", 1) / 2;
	dp = target->query_skill("parry", 1) + target->query_skill("martial-cognize", 1) / 2;
	if (ap / 2 + random(ap) > dp)
	{
		damage = ap * 3 + random(ap) * (random(2) + 2);

		me->add("neili", -180);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
					   HIR "$n" HIR "����$P�򽣹��ڵİ��壬"
					   HIR "����ն�����̬��㱣����ǽ���������û���У������ش���"NOR"\n");
		if (weapon->query("magic/skill/lonely-sword"))
			skill_cd(me,"yi", 2);
		else
			me->start_busy(2);
	} else
	if (target->query_skill("martial-cognize", 1) + target->query_skill("lonely-sword", 1) > 150)
	{
		msg += CYN "Ȼ��$n" CYN "�����輱������ʯ������Զ������֮���ձܿ��⾪�콣������$N"
		       CYN "�Ĺ���ȫȻ���ܷ������á�\n";
		me->add("neili", -80);
		if (weapon->query("magic/skill/lonely-sword"))
			skill_cd(me,"gui", 5);
		else
		me->start_busy(3);
	} else
	{
		msg += CYN "$n" CYN "��Ȼ��֮վ�����Σ�ʹ��ʮ���ֹ�����Ѫ����ӿ֮�¿�ཀྵ�֣�����������ȥ���⾪�콣����$P"
		       CYN "������̾��"NOR"\n";
		me->add("neili", -60);
		if (weapon->query("magic/skill/lonely-sword"))
			skill_cd(me,"gui", 5);
		else
		me->start_busy(5);
	}
	message_combatd(msg, me, target);

	return 1;
}
