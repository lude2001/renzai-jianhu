// mie.c  回风拂柳剑法「济世剑气」

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "济世剑气"; }
string *pfm_type() { return ({
    "sword",
}); }

int perform(object me, object target)
{
    int damage;
    string msg;
    object weapon, duiyou, *team;
    int ap, dp, qixue;

    if (!target)
        target = offensive_target(me);

  //   if (!target || !me->is_fighting(target))
        // return notify_fail("「济世剑气」只能对战斗中的对手使用。\n");

    if (!objectp(weapon = me->query_temp("weapon")) ||
        (string)weapon->query("skill_type") != "sword")
        return notify_fail("没装备剑怎么使用「济世剑气」？\n");

    if ((int)me->query_skill("huifeng-jian", 1) < 60)
        return notify_fail("你的回风拂柳剑法不够娴熟，还使不出「济世剑气」。\n");


    if (me->query_skill_mapped("sword") != "huifeng-jian")
        return notify_fail("你没有激发回风拂柳剑法，不能使用「济世剑气」。\n");

    if ((int)me->query_skill("force") < 120)
        return notify_fail("你的内功火候不够，难以施展「济世剑气」。\n");

    if ((int)me->query("neili") < 200)
        return notify_fail("你现在真气不够，难以施展「济世剑气」。" NOR "\n");

    qixue = me->query_skill("huifeng-jian") + random(me->query_skill("force"));

    qixue *= 4;

    if (!weapon->query("magic/skill/huifeng-jian"))
    qixue /= 2;

    if (sizeof(team = me->query_team()))
        duiyou = team[random(sizeof(team))]; //什么意思呢？就是随机取一个玩家
    else
        duiyou = me;
    
    if (environment(me) != environment(duiyou))
        return notify_fail("这里没有这个人如何恢复伤势。\n");
        tell_object(environment(me),"只见" + me->name() + "轻轻一抹" + weapon->name() + "，一道绿色剑气进入了" + duiyou->name() + "体内。顿时伤势得到回复。\n");
        duiyou->add("qi", qixue);
        duiyou->add("eff_qi", qixue);
        
        //记录一下自己造成的恢复量
        me->set_temp("huifu",qixue);
        
        //不能超过最大气血
        if (duiyou->query("eff_qi") > duiyou->query("max_qi") + duiyou->query_gain_qi())
            duiyou->set("eff_qi", duiyou->query("max_qi") + duiyou->query_gain_qi());
        if (duiyou->query("qi") > duiyou->query("eff_qi"))
        duiyou->set("qi", duiyou->query("eff_qi"));
        
    skill_cd(me,"jishi", 3);
    //me->start_busy(2);
    me->add("neili", -200);
    return 1;
}
