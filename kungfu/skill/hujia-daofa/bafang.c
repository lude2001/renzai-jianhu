// bafang.c 八方藏刀式

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
 
string query_name() { return "八方"ZJBR"藏刀"; }
string *pfm_type() { return ({ "blade", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int count=0;
	int i,lianji,ap,dp;
	lianji = 4+ random(4);
 
	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("「八方藏刀式」只能对战斗中的对手使用。\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "blade")
		return notify_fail("手中没刀还使什么「八方藏刀式」！\n");

	if ((int)me->query("neili") < 200)
		return notify_fail("你的真气不够！\n");

	if ((int)me->query_skill("force") < 100)
		return notify_fail("你的内功火候不够！\n");

	if ((int)me->query_skill("hujia-daofa", 1) < 100)
		return notify_fail("你的胡家刀法还不到家，无法使用「八方藏刀式」！\n");

	if (me->query_skill_mapped("blade") != "hujia-daofa")
		return notify_fail("你没有激发胡家刀法，无法使用「八方藏刀式」！\n");

       if (! living(target))
	      return notify_fail("对方都已经这样了，用不着这么费力吧？\n");
	      //默认
ap = random(me->query_skill("blade"));
dp = target->query_skill("parry") / 2;

	msg = HIW "$N" HIW "轻舒猿臂，手中的" + weapon->name() +
	      HIW "吞吞吐吐，变化莫测，笼罩了$n" HIW "周身要害！"NOR"\n";
	      
           if (weapon->query("magic/skill/hujia-daofa"))//拥有胡家专属宝石的加成
		{
			      //宝石加强后效果后定
ap = random(me->query_skill("blade"))+me->query_skill("hujia-daofa");
dp = target->query_skill("parry") / 3;
lianji += 2;
count += me->query_skill("hujia-daofa", 1) / 6;//再叠加一次count，相当于1/3
		tell_object(me,"只见一声脆响，你感觉"+weapon->name()+"上的蓝色翡翠爆发出强烈的光芒，顿时对八方藏刀式的感悟加深\n");
		}
		
	if (ap > dp)
	{
		msg += HIY "$n" HIY "见来招实在是变幻莫测，不由得心"
		       "生惧意，招式登时出了破绽！"NOR"\n";
		count += me->query_skill("hujia-daofa", 1) / 6;
	} else
	{
		msg += HIC "$n" HIC "心底微微一惊，打起精神小心接招。"NOR"\n";
		count = 0;
	}

	message_combatd(msg, me, target);
	me->add("neili", -150);
	me->add_temp("apply/attack", count);

	for (i = 0; i < lianji; i++)
	{
		if (! me->is_fighting(target))
			break;
		if (random(3) == 1 && ! target->is_busy())
			target->start_busy(1);
		COMBAT_D->do_attack(me, target, weapon, 0);
	}

        if (weapon->query("magic/skill/hujia-daofa-daopo"))//拥有胡家专属宝石的加成
        {
                	    int damage = ap;
                	    string msgs = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 25,
							   HIB "\n$n" HIB "身形摇晃间，感觉到"
							   + weapon->name() + HIB + 
							   "上一阵刺骨的寒气侵入体内，复又喷出"
							   "一口鲜血！"NOR"\n");
							
						target->receive_damage("qi", damage / 2, me);
					   target->receive_wound("qi",
					   damage / 4 + random(damage / 4), me);
					   	message_sort(msgs, me, target);
            	        
        }
	me->add_temp("apply/attack", -count);
	if (weapon->query("magic/skill/hujia-daofa"))//拥有胡家专属宝石的加成
	skill_cd(me,"bafang",1+random(6));//随机一到6秒。
	else
		me->start_busy(1 + random(6));
	return 1;
}
