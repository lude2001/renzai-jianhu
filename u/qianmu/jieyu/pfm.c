#include <combat.h>

inherit F_SSERVER;

int perform(object me)
{
	int damage;
	object target;
	string msg;

	target = me->select_opponent();

	if (!target || !me->is_fighting(target))
		return 1;

	msg = HIR "$N步伐一变，瞬间贴近$n" HIR "的身体，一拳朝$n" HIR "的胸口打去。" NOR "\n";

	if (!random(3))
	{
		damage = me->query("max_skill_level") * 5;
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 180, 
			HIR "$N" HIR "的这一拳击中$n" HIR "，$n" HIR "的口中吐出一口鲜血。" NOR "\n");
	}
	else
	{
		msg += HIC "$n往旁边一闪，躲过了$N的攻击。\n";
	}

	message_combatd(msg, me, target);
	return 1;
}