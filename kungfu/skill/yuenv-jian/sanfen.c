#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
string query_name() { return "越女"ZJBR"三分"; }

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
		return notify_fail("「越女三分」只能在战斗中对对手使用。\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("你使用的武器不对。\n");

	if (me->query_skill("sanfen-jianshu", 1) < 180)
		return notify_fail("你的三分剑术修为不足，无法使用越女三分。\n");

	if (userp(me) && ! me->query("can_perform/yuenv-jian/pengxin"))
		return notify_fail("使用「越女三分」得先学会西子捧心！\n");

	if (me->query_dex() < 35)
		return notify_fail("你的身法不够，目前还不能使用这项绝技！\n");

	if (me->query_skill("sword", 1) < 100)
		return notify_fail("你的剑术修为不够，目前不能使用「越女三分」！\n");

	if (me->query_skill("yuenv-jian", 1) < 100)
		return notify_fail("你的越女剑术的修为不够，不能使用这一绝技！\n");

	if (me->query_skill("dodge") < 150)
		return notify_fail("你的轻功修为不够，无法使用「越女三分」！\n");
 
	if (me->query("neili") < 200)
		return notify_fail("你的真气不够！\n");

       if (! living(target))
	      return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

	if (me->query("gender") == "女性" &&
	    target->query("gender") == "女性")
		delta = target->query("per") - me->query("per");
	else
		delta = 0;

	msg = HIG "$N" HIG "幽幽一声长叹，手中的" + weapon->name() +
	      HIG "就如闪电般刺向$n的胸口。"NOR"\n";
	if (delta > 0)
		msg += HIY "$n" HIY "只觉得$N" HIY "眼神中隐然透出"
		       "一股冰冷的寒意，心中不禁一颤。"NOR"\n";
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
				((i == 1)?(HIR "$n" HIR "大惊失色，想要躲避。奈何到此剑气来势之快，已无处闪躲。\n"
					"只听一声惨叫，剑气划过$n的胸口，深可见骨" NOR "\n"):("$n重伤之下破绽百出，$P剑"
					"随心动再次刺出一剑，$p伤上加伤，痛苦不堪。" NOR "\n")));
		}
		else
		{
			msg += HIC "$n" HIC "见状身形急退，避开了$N" HIC "的无形剑气的凌厉一击！"NOR"\n";
		}
	} 


	me->start_busy(2 + random(i));
	message_combatd(msg, me, target);

	return 1;
}
