#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
string query_name() { return "ԽŮ"ZJBR"����"; }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;
	int damage;
	int delta;
	int i;

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("��ԽŮ���֡�ֻ����ս���жԶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if (me->query_skill("sanfen-jianshu", 1) < 180)
		return notify_fail("������ֽ�����Ϊ���㣬�޷�ʹ��ԽŮ���֡�\n");

	if (userp(me) && ! me->query("can_perform/yuenv-jian/pengxin"))
		return notify_fail("ʹ�á�ԽŮ���֡�����ѧ���������ģ�\n");

	if (me->query_dex() < 35)
		return notify_fail("�����������Ŀǰ������ʹ�����������\n");

	if (me->query_skill("sword", 1) < 100)
		return notify_fail("��Ľ�����Ϊ������Ŀǰ����ʹ�á�ԽŮ���֡���\n");

	if (me->query_skill("yuenv-jian", 1) < 100)
		return notify_fail("���ԽŮ��������Ϊ����������ʹ����һ������\n");

	if (me->query_skill("dodge") < 150)
		return notify_fail("����Ṧ��Ϊ�������޷�ʹ�á�ԽŮ���֡���\n");
 
	if (me->query("neili") < 200)
		return notify_fail("�������������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	if (me->query("gender") == "Ů��" &&
	    target->query("gender") == "Ů��")
		delta = target->query("per") - me->query("per");
	else
		delta = 0;

	msg = HIG "$N" HIG "����һ����̾�����е�" + weapon->name() +
	      HIG "������������$n���ؿڡ�"NOR"\n";
	if (delta > 0)
		msg += HIY "$n" HIY "ֻ����$N" HIY "��������Ȼ͸��"
		       "һ�ɱ���ĺ��⣬���в���һ����"NOR"\n";
	else
		delta = 0;

	me->add("neili", -150);
	ap = (me->query_skill("sword") + me->query_skill("dodge")) / 2;
	dp = target->query_skill("dodge");

	for (i = 1; i <= 5; i++)
	{
		if (ap / 2 + random(ap) > dp)
		{
			damage = ap / 2 + random(ap / 2) + delta * 50;
			msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
				((i == 1)?(HIR "$n" HIR "��ʧɫ����Ҫ��ܡ��κε��˽�������֮�죬���޴����㡣\n"
					"ֻ��һ���ҽУ���������$n���ؿڣ���ɼ���" NOR "\n"):("$n����֮�������ٳ���$P��"
					"���Ķ��ٴδ̳�һ����$p���ϼ��ˣ�ʹ�಻����" NOR "\n")));
		}
		else
		{
			msg += HIC "$n" HIC "��״���μ��ˣ��ܿ���$N" HIC "�����ν���������һ����"NOR"\n";
		}
	} 


	me->start_busy(2 + random(i));
	message_combatd(msg, me, target);

	return 1;
}
