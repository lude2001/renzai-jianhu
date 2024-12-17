#include <ansi.h>
#include <combat.h>

#define XIAN "「" HIY "风林火山" NOR "」"
string query_name() { return "风林火山"; }
inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;
        int ap, dp;


        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(XIAN "只能对战斗中的对手使用。\n");
 
        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "blade")
                return notify_fail("你使用的武器不对，难以施展" XIAN "。\n");

    	if (me->query_skill("zuoyou-hubo", 1))
    	return notify_fail("左右互博和胡家刀法不兼容。\n");
	
        if ((int)me->query_skill("force") < 160)
                return notify_fail("你的内功火候不够，难以施展" XIAN "。\n");

        if ((int)me->query_skill("hujia-daofa", 1) < 500)
                return notify_fail("你的胡家刀法还不到家，难以施展" XIAN "。\n");

        if (me->query_skill_mapped("blade") != "hujia-daofa")
                return notify_fail("你没有激发胡家刀法，难以施展" XIAN "。\n");

        if ((int)me->query("neili") < 200)
                return notify_fail("你的真气不够，难以施展" XIAN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

    msg = HIY"黄金错刀白玉装
    夜穿窗扉出光芒
    丈夫五十功未立
    提刀独立顾八荒
    只见$N提起手中" + weapon->name() +  HIY "，单刃指天，似凝聚了天意四象。$N迸发全身劲力汇于一线朝前劈出，霎时间滔天刀气席卷八方，竟似携带了风林火山之势朝着$n席卷而去。刀气所过之处，金石碎裂，草木枯绝。
    【风】-诛天戮地！
    【林】-灭神绝仙！
    【火】-屠佛弑邪！
    【山】-销鬼杀将！
    单刀残躯饮寒风
    今朝有酒醉皇龙
    【刀】-毁身破甲"NOR"！";

        ap = me->query_skill("blade") + me->query_skill("force");
        dp = target->query_skill("force");

        if (ap / 2 + random(ap / 2) > dp)
	{
	        	damage = ap / 2 + random(ap / 2);
                me->add("neili", -damage / 3);
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi",damage / 4 + random(damage / 4), me);
		msg +=                     HIR "$n" HIR "何曾见过如此高明的刀法，"
                                           "一声惨叫，刀锋已入体三分，鲜血四处喷溅！\n" NOR;
		me->start_busy(2);
        if (ap / 3 + random(ap / 2) > dp && ! target->is_busy())
                        target->start_busy(ap / 60 + 2);
	} else 
	{
		msg += CYN "$p" CYN "大吃一惊，也不招架，当即向后"
                       "横移数尺，避开了$P" CYN "这一招。\n" NOR;
                me->add("neili", -150);
		me->start_busy(2);
	}
	message_combatd(msg, me, target);

	return 1;
}
