// chaos-steps.c

inherit SKILL;

string *dodge_msg = ({
	"$n一个「醉卧云端」，躲过了$N这一招。\n",
	"$n身形向后一纵，使出一招「饮尽江河」，避过了$N的攻击。\n",
	"$n使出「千杯不倒」，恰好躲过了$N的攻势。\n"
       "但是$n身形飘忽,一招「笑看红尘」,轻轻一纵，早已避开。\n",
       "$n使出「与月共饮」,身随意转，倏地往一旁挪开了三尺，避过了这一招。\n",
       "$n一个「醉眼朦胧」,身形微晃，有惊无险地避开了$N这一招。\n"
});

int valid_enable(string usage)
{
	return (usage=="dodge");
}

int valid_learn(object me)
{
        if( (int)me->query("max_neili") < 50 )
		return notify_fail("你的内力不够，没有办法练醉仙望月步。\n");

	return 1;
}

string query_dodge_msg(string limb)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( (int)me->query("qi") < 30
        ||      (int)me->query("neili") < 30 )
		return notify_fail("你的气或内力不够，不能练醉仙望月步。\n");
        me->receive_damage("qi", 30);
        me->add("neili", -30);
	return 1;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
	mixed result;
	int ap, dp, mp;

	if ((int)me->query_skill("zuixian-steps", 1) < 100 ||
	    ! living(me))
		return;

	mp = ob->query_skill("count", 1);
	ap = ob->query_skill("dodge") + mp;
	dp = me->query_skill("dodge", 1) / 2 +
	     me->query_skill("zuixian-steps", 1);

	if (ap / 2 + random(ap) < dp)
	{
		result = ([ "damage": -damage ]);

		switch (random(4))
		{
		case 0:
			result += (["msg" : HIW "只见$n" HIW "微微一笑，身子轻轻晃动，$N"
					    HIW "眼前顿时出现了无数个$n" HIW "的幻影，令$N"
					    HIW "完全无法辨出虚实。"NOR"\n"]);
			break;
		case 1:
			result += (["msg" : HIW "$n" HIW "往旁边歪歪斜斜的迈出一步，却恰"
					    "好令$N" HIW "的攻击失之毫厘。"NOR"\n"]);
			break;
		case 2:
			result += (["msg" : HIW "$N" HIW "这一招来的好快，然后$n"
					    HIW "一闪，似乎不费半点力气，却将$N"
					    HIW "这一招刚好避开。"NOR"\n"]);
			break;
		default:
			result += (["msg" : HIW "但见$n" HIW "轻轻一跃，已不见了踪影，$N"
					    HIW "心中大骇，却又见$n" HIW "擦肩奔过，步法"
					    "之奇巧，当真令人思索菲仪。"NOR"\n"]);
			break;
		}
		return result;
	} else
	if (mp >= 100)
	{
		switch (random(4))
		{
		case 0:
			result = HIY "只见$n" HIY "微微一笑，身子轻轻晃动，"
				 "顿时出现了无数个$n" HIY "的幻影，可是$N"
				 HIY "精通易理，将其中虚实辨得清清楚楚。"NOR"\n";
			break;
		case 1:
			result = HIY "$n" HIY "往旁边歪歪斜斜的迈出一步，然而$N"
				 HIY "错步跟随，方位毫厘不差。"NOR"\n";
			break;
		case 2:
			result = HIY "$n" HIY "一闪，似乎不费半点力气，却将$N"
				 HIY "这一招刚好避开，可是$N"
				 HIY "招中有招，进攻却是不止。"NOR"\n";
			break;
		default:
			result = HIY "但见$n" HIY "轻轻一跃，已不见了踪影，$N"
				 HIY "不假思索，反身出招，更是巧妙无方。"NOR"\n";
			break;
		}
		COMBAT_D->set_bhinfo(result);
	}
}

int query_effect_dodge(object attacker, object me)
{
	int lvl;

	lvl = me->query_skill("zuixian-steps", 1);
	if (lvl < 50)  return 0;
	if (lvl < 100) return 30;
	if (lvl < 150) return 50;
	if (lvl < 200) return 80;
	if (lvl < 250) return 100;
	if (lvl < 300) return 120;
	if (lvl < 350) return 140;
	return 150;
}