// yi.c 万剑归宗

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
string query_name() { return "万剑"ZJBR"归宗"; }
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
		return notify_fail("你只能对战斗中的对手使用绝招。\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("无剑如何运用万剑归宗？\n");

	if( me->query("family/family_name") && me->query("family/family_name") != "华山派" &&
	    me->query("family/family_name") != "华山剑宗" && !lv_fa(me,"华山派") && !lv_fa(me,"华山剑宗"))
	{
		return notify_fail("非华山弟子无法领悟独孤九剑的意境！\n");
	}
	
	if ((int)me->query("neili") < 200)
		return notify_fail("你现在的真气不够，无法使用万剑归宗！\n");

	if ((int)me->query_skill("lonely-sword", 1) < 500)
		return notify_fail("你的独孤九剑还不到家，无法使用万剑归宗！\n");

	if ((int)me->query_skill("sword-cognize", 1) < 500)
		return notify_fail("你的剑道修养还不到家，无法使用万剑归宗！\n");

	if ((int)me->query_skill("martial-cognize", 1) < 500)
		return notify_fail("你的武学修养还不到家，无法使用万剑归宗！\n");

	// if ((int)me->query_skill("sword-heart", 1) < 500)
	// 	return notify_fail("你的剑心修炼还不到家，无法使用万剑归宗！\n");

	if (me->query_skill_mapped("sword") != "lonely-sword") 
		return notify_fail("你没有激发独孤九剑，无法使用万剑归宗！\n");

       if (! living(target))
	      return notify_fail("对方都已经这样了，用不着这么费力吧？\n");


		msg = HIM "天苍苍，地茫茫，神剑真传起洪荒。只见$N轻手抬剑，一时间竟是演化九道身影，分别使出："NOR";\n";
		msg += "【总诀式】归妹趋无妄，无妄趋同人，同人趋大有。\n
		【破剑式】甲转丙，丙转庚，庚转癸。\n
		【破刀式】子丑之交、辰巳之交、午未之交。\n
		【破枪式】风雷是一变，山泽是一变，水火是一变。\n
		【破鞭式】乾坤相激、震兑相激、离巽相激。\n
		【破索式】三增而成五、五增而成九。\n
		【破掌式】天一生两仪，两仪生四象，四象演八卦。\n
		【破箭式】天地合其德，日月合其明，四时合其序，鬼神合其吉凶。\n
		【破气式】无剑胜有剑，无招胜有招，万物凝于剑，天势聚成招\n
		一时间九剑归一，化作一道惊天剑气，朝着$n呼啸而去！\n";

	ap = me->query_skill("lonely-sword", 1) + me->query_skill("martial-cognize", 1) / 2 + me->query_skill("sword-cognize", 1) / 2;
	dp = target->query_skill("parry", 1) + target->query_skill("martial-cognize", 1) / 2;
	if (ap / 2 + random(ap) > dp)
	{
		damage = ap * 3 + random(ap) * (random(2) + 2);

		me->add("neili", -180);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
					   HIR "$n" HIR "看到$P万剑归宗的奥义，"
					   HIR "眼神空洞，神态恍惚，被那剑气长河淹没其中，遭受重创！"NOR"\n");
		if (weapon->query("magic/skill/lonely-sword"))
			skill_cd(me,"yi", 2);
		else
			me->start_busy(2);
	} else
	if (target->query_skill("martial-cognize", 1) + target->query_skill("lonely-sword", 1) > 150)
	{
		msg += CYN "然而$n" CYN "身形骤急，电光火石间提气远闪，险之又险避开这惊天剑气，让$N"
		       CYN "的攻击全然不能发挥作用。\n";
		me->add("neili", -80);
		if (weapon->query("magic/skill/lonely-sword"))
			skill_cd(me,"gui", 5);
		else
		me->start_busy(3);
	} else
	{
		msg += CYN "$n" CYN "淡然处之站稳身形，使出十二分功力，血气翻涌之下苦苦僵持，终是勉力化去了这惊天剑气，$P"
		       CYN "不由赞叹。"NOR"\n";
		me->add("neili", -60);
		if (weapon->query("magic/skill/lonely-sword"))
			skill_cd(me,"gui", 5);
		else
		me->start_busy(5);
	}
	message_combatd(msg, me, target);

	return 1;
}
