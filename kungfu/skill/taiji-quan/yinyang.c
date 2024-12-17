// yingyang 显阴阳
// updated force->neili, force_factor->jiali (by xbd)

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
string query_name() { return "显阴阳"; }
string *pfm_type() { return ({ "unarmed", }); }
string *taiji_msg = ({
    "揽雀尾",
    "单鞭",
    "提手上势",
    "白鹤亮翅",
    "搂膝勾步",
    "白蛇吐信",
    "高探马",
    "伏虎式",
    "揽月势",
    "金鸡独立",
    "玉女穿梭",
    "进步七星",
    "弯弓射虎",
    "抱虎归山",
});
int perform(object me, object target)
{
    string msg;
    int extra, damage;
    int orforce;
    object weapon;
    int force;
    string *limbs;
    object *obs = me->query_enemy();
    int mz = me->query_skill("force") / 2 + random(me->query_skill("force") / 2 + me->query_skill("martial-cognize", 1) / 2);
    if (me->is_busy())
        return notify_fail("你现在没空！！\n");
    if ((int)me->query("neili") < 2000)
        return notify_fail("你的内力不够。\n");

    if ((int)me->query("neili") < me->query("max_neili") / 7 + 200)
        return notify_fail("你的内力不够。\n");

    if (!wizardp(me) && (int)me->query_skill("taiji-quan", 1) < 500)
        return notify_fail("你的本门外功（太极拳）不够!不能贯通使用！\n");

    if (!wizardp(me) && (int)me->query_skill("taiji-jian", 1) < 500)
        return notify_fail("你的本门外功(太极剑)不够!不能贯通使用！\n");
        
    if (!wizardp(me) && (int)me->query_skill("martial-cognize", 1) < 300)
    return notify_fail("你的武学修养不够!不能贯通使用！\n");

    if (!wizardp(me) && (int)me->query_skill("taiji-shengong", 1) < 500)
        return notify_fail("你的本门内功（太极神功）不够高!不能贯通使用！\n");

    if (!wizardp(me) && me->query_skill_mapped("force") != "taiji-shengong")
        return notify_fail("不使用本门内功，如何使用本门绝学!\n");

    extra = 100 + me->query_skill("unarmed") / 3 * 2 + me->query_skill("martial-cognize", 1);
    if (!target)
        target = offensive_target(me);
    if (!target || !target->is_character() || !me->is_fighting(target))
        return notify_fail("这门绝学只能对战斗中的对手使用。\n");

    //me->add("jiali", extra / 3);
    
    if (!playerp(target))
    {
        mz *= 2;
        extra *= 3;    
    }
    
    orforce = (int)me->query("force");
    weapon = me->query_temp("weapon");
    me->add_temp("apply/attack", extra / 6);
    me->add_temp("apply/damage", 300);

    msg = HBWHT "$N贯通武当武学，使出了武当的绝学之精髓！\n" NOR;
    message_vision(msg, me, target);



    if (random(2) == 0)
        target->start_busy(3);
  
    if (mz > target->query_skill("force"))
    {
        int qi;

        qi = target->query("qi");
        
        for (int i = 0; i < 6; i++)
    	{
    		if (! me->is_fighting(target))
    			break;
    		if (random(5) < 2 && ! target->is_busy())
    			target->start_busy(1);
    
    		COMBAT_D->do_attack(me, target, 0, 0);
    	}
    	
        msg = MAG "$N双手抱了个太极式的圆圈，纯以意行太极，已达形神合一，心动气动的境界，！\n" NOR;
        message_vision(msg, me, target);
        msg = WHT "「乱环诀」！阴" NOR;
        msg += HIY "\n结果$n脸色一下变得惨白，昏昏沉沉接连退了好几步！\n" NOR;
        message_vision(msg, me, target);
        msg = MAG "「乱环诀」！阳" NOR;
        msg += HIY "\n结果$n脸色一下变得惨白，昏昏沉沉接连退了好几步！\n" NOR;
        target->receive_wound("qi", random(extra) + extra / 2 ,me);
        message_vision(msg, me, target);
        msg = WHT "「阴阳诀」！阴" NOR;
        msg += HIY "\n结果$n脸色一下变得惨白，昏昏沉沉接连退了好几步！\n" NOR;
        message_vision(msg, me, target);
        msg = MAG "「阴阳诀」！阳" NOR;
        msg += HIY "\n结果$n脸色一下变得惨白，昏昏沉沉接连退了好几步！\n" NOR;
        target->receive_wound("qi", random(extra) + extra / 2 ,me);
        message_vision(msg, me, target);
        msg = WHT "「动静诀」！阴" NOR;
        msg += HIY "\n结果$n脸色一下变得惨白，昏昏沉沉接连退了好几步！\n" NOR;
        message_vision(msg, me, target);
        msg = MAG "「动静诀」！阳" NOR;
        msg += HIY "\n结果$n脸色一下变得惨白，昏昏沉沉接连退了好几步！\n" NOR;
        target->receive_wound("qi", random(extra) + extra / 2 ,me);
        message_vision(msg, me, target);
        msg = WHT "「两仪诀」！阴" NOR;
        msg += HIY "\n结果$n脸色一下变得惨白，昏昏沉沉接连退了好几步！\n" NOR;
        message_vision(msg, me, target);
        msg = MAG "「两仪诀」！阳" NOR;
        msg += HIY "\n结果$n脸色一下变得惨白，昏昏沉沉接连退了好几步！\n" NOR;
        target->receive_wound("qi", random(extra) + extra / 2 ,me);
        message_vision(msg, me, target);
        msg = WHT "「刚柔诀」！阴" NOR;
        msg += HIY "\n结果$n脸色一下变得惨白，昏昏沉沉接连退了好几步！\n" NOR;
        target->receive_wound("qi", random(extra) + extra / 2 ,me);
        message_vision(msg, me, target);
        msg = MAG "「刚柔诀」！阳" NOR;
        msg += HIY "\n结果$n脸色一下变得惨白，昏昏沉沉接连退了好几步！\n" NOR;
        target->receive_wound("qi", random(extra) + extra / 2 ,me);
        message_vision(msg, me, target);

        msg = WHT "              阴阳双环           !!\n" NOR;
        msg += MAG "「沾黏诀」「挤字诀」「引字诀」「按字诀」!!\n" NOR;
        target->receive_damage("qi", (int)me->query_skill("taiji-quan", 1) * 4,me);
        target->receive_wound("qi", (int)me->query_skill("taiji-quan", 1) * 2,me);
        if (damage < 300)
            msg += HIY "\n结果$n脸色一下变得惨白，昏昏沉沉接连退了好几步！\n" NOR;
        else if (damage < 400)
            msg += HIY "\n结果重重地击中，$n「哇」地一声吐出一口鲜血！\n" NOR;
        else if (damage < 500)
            msg += RED "\n结果「轰」地一声，$n全身气血倒流，口中鲜血狂喷而出！\n" NOR;
        else
            msg += HIR "\n结果只听见几声喀喀轻响，$n一声惨叫，像滩软泥般塌了下去！！\n" NOR;
        message_vision(msg, me, target);
        tell_object(me,HIY"对敌方造成"HIR + (qi - target->query("qi")) + HIY"点伤害"NOR"。\n");
    }
    else
    message_vision(HIM "然而没有任何人受了$N"
    HIM "的影响。"NOR"\n", me, 0, obs);

    me->add_temp("apply/attack", -extra / 6);
    me->add_temp("apply/damage", -300);
    me->add("neili", -me->query("max_neili") / 7);
    me->start_busy(4);

    return 1;
}
