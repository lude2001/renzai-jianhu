// fumo.c 狂纵风雨

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "狂纵"ZJBR"风雨"; }
string *pfm_type() { return ({ "club", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;
	int damage;
 
	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("「狂纵风雨」只能在战斗中对对手使用。\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	      (string)weapon->query("skill_type") != "club")
		return notify_fail("你使用的武器不对。\n");

	if (me->query_skill("force") < 200)
		return notify_fail("你的内功的修为不够，难以使用这一绝技！\n");

	if (me->query_skill("qiyang-luoyuqiang", 1) < 400)
		return notify_fail("你的七阳落雨枪修为不够，目前不能使用狂纵风雨！\n");

	if (me->query("neili") < 800)
		return notify_fail("你的真气不够，不能使用狂纵风雨！\n");

	if (me->query_skill_mapped("club") != "qiyang-luoyuqiang")
		return notify_fail("你没有激发七阳落雨枪，不能使用狂纵风雨！\n");

	if (me->query("int") < 30)
		return notify_fail("你悟性不足，难以理解狂纵风雨的精髓。\n");

       if (! living(target))
	      return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

	msg = HIY "$N" HIY "神色激昂,手中的" + weapon->name() +
	      HIY "如同狂风暴雨纵向击出前，\n一时间漫天枪影团团笼罩住$n" + HIY "！"NOR"\n";

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
					   HIR "结果只听$p" HIR "全身被戳出无数伤口，枪尖在$P"
					   "身上处处打中经脉要害，漫血不止！"NOR"\n");

	} else
	{
		me->add("neili", -1000);
		me->start_busy(2);
		msg += CYN "可是$p" CYN "全身内功真气激荡$P"
		       CYN "，真气护体竟硬生生的挡住了$P" CYN "狂风暴雨般的攻式！"NOR"\n";
	}
	message_combatd(msg, me, target);

	return 1;
}
