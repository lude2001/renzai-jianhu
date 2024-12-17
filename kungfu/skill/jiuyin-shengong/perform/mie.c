// lei.c 九阴绝灭

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
string query_name() { return "九阴"ZJBR"绝灭"; }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;
 
	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("九阴绝灭只能在战斗中对对手使用。\n");

	if (me->query_skill("jiuyin-shengong", 1) < 150)
		return notify_fail("你的不败神功还不够娴熟，不能使用九阴绝灭！\n");


	if (me->query("neili") < 300)
		return notify_fail("你的真气不够！\n");

    if (! living(target))
	    return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

	msg = HIY "$N" HIY "微微一笑，施展出九阴神功之九阴绝灭，忽的抓向$n"HIY "的周身要害！"NOR"\n";

	ap = me->query_skill("jiuyin-shengong", 1);
	dp = target->query("combat_exp") / 10000;
	me->add("neili", -60);
	me->start_busy(1 + random(2));

	me->want_kill(target);
	if (dp >= 100)
	{
		msg += HIY "$n" HIY "使出平生所学，奋力化解，没出一点差错。"NOR"\n";
	} else
	if (random(ap) > dp)
	{
		msg += HIR "$n" HIR "平生何曾见过这样的招数，全然无法化解，"
		       HIR "顿时被击中数处要害，颓然倒地！"NOR"\n";
		message_combatd(msg, me, target);
		target->die(me);
		return 1;
	} else
	{
		msg += HIM "$n" HIM "大吃一惊，连忙胡乱抵挡，居"
		      "然没有一点伤害，侥幸得脱！"NOR"\n";
	}

	message_combatd(msg, me, target);

	return 1;
}
