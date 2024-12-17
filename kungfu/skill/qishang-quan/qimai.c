// qimai.c 七脉皆伤

#include <ansi.h>

inherit F_SSERVER;
 
string query_name() { return "七脉"ZJBR"皆伤"; }
string *pfm_type() { return ({ "cuff", }); }

int perform(object me, object target)
{
	string msg;
	int ap, dp;
	int count;
	int i, busy_count = 0;
 
	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("「七脉皆伤」只能在战斗中对对手使用。\n");
 
//	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
//		return notify_fail("「七脉皆伤」只能空手使用。\n");
		
	if (me->query("max_neili") < 2000)
		return notify_fail("你的内力修为还不够，无法施展「七脉皆伤」。\n");

	if ((int)me->query("neili") < 500)
		return notify_fail("你的真气不够！\n");

	if ((int)me->query("qi") < 800)
		return notify_fail("你的体力现在不够！\n");

	if ((int)me->query_skill("qishang-quan", 1) < 150)
		return notify_fail("你的七伤拳火候不够，无法使用「七脉皆伤」！\n");

	if ((int)me->query_skill("force") < 300)
		return notify_fail("你的内功修为不够，无法使用「七脉皆伤」！\n");
//无需准备
//	if (me->query_skill_prepared("cuff") != "qishang-quan")
	//	return notify_fail("你现在没有准备使用七伤拳，无法使用「七脉皆伤」！\n");

	if (! living(target))
	      return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

	msg = HIY "$N" HIY "凝神屏气，口中念着四句似歌似诗的七伤，"
	      "总诀，刹那间，跨上一步，连出几拳！"NOR"\n";
	
	message_vision(msg, me, target);
	for (i = 0; i < 6; i++)
	{
	    if(random(3))
	    {
	        ap = me->query_skill("cuff") / 2 + me->query("con") * 6;
	        dp = target->query_skill("force", 1);
	        count = ap - dp;
	        if (count < 0)    count = random(100);
	        target->receive_wound("qi", count, me);
	        msg = HIY "$n面对$P如此迅疾的拳法，完全没有闪躲的余地，“砰”，胸口硬接一拳。" NOR "\n" HIR "七伤内劲-" + count + "。" NOR "\n";
	        if (random(3))
	        {
	            msg += HIY "$P受到了七伤拳反噬。" NOR "\n";
	            busy_count++;
	            me->receive_damage("qi", count / 10 * 7, target);
	        }
	        
	        message_vision(msg, me, target);
	    }
	    else
	    {
	        msg = HIW "$n打起精神，化解了$P的招式。" NOR "\n";
	        
	        message_vision(msg, me, target);
	    }
	}
	
	me->add("neili", -500);
	me->add("qi", -500);
	me->start_busy(busy_count);
    
    skill_cd(me,"qimaj",8);

	return 1;
}
