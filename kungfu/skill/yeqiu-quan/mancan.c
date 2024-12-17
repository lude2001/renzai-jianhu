// xue.c 胡搅蛮缠

#include <ansi.h>

inherit F_SSERVER;
 
string query_name() { return "胡搅"ZJBR"蛮缠"; }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int i;
 
	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("「胡搅蛮缠」只能对战斗中的对手使用。\n");
		
 
	if (objectp(weapon = me->query_temp("weapon")))
		return notify_fail("「胡搅蛮缠」必须空手！\n");

	/*if ((int)me->query("neili") < 100)
		return notify_fail("你的真气不够！\n");

	if ((int)me->query_skill("force") < 80)
		return notify_fail("你的内功火候不够！\n");
*/
	if ((int)me->query_skill("yeqiu-quan", 1) < 1)
		return notify_fail("你的野球拳还不到家，无法使用胡搅蛮缠！\n");

       if (! living(target))
	      return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

	msg = HIW "$N" HIW "使出致命绝技「胡搅蛮缠」，招式变得不清不楚！"NOR"\n";
	message_combatd(msg, me);
	//me->add("neili", -100);
	//只对自己的师门npc有秒杀效果
 if (target->query_temp("quester")==getuid(me)&&me->query("combat_exp")<1000000)//师门怪物直接死
 {
 target->receive_wound("qi", 5, me);
  target->die(me);
  	message_combatd("结果$N一击致命，$n吐血不止，立刻身亡！\n", me);
  }
  else
  {
  	target->receive_wound("qi", 1, me);
  	message_combatd("$N使出野球拳绝技胡搅蛮缠，对敌人没有任何伤害。\n", me);
  }/*
	for (i = 0; i < 5; i++)
	{
		if (! me->is_fighting(target))
			break;
		COMBAT_D->do_attack(me, target, weapon, 0);
	}*/

	me->start_busy(1 + random(4));
	return 1;
}
