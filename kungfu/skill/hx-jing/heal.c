// heal.c

#include <ansi.h>

string query_name() { return "疗伤"; }

int exert(object me, object target)
{
        if( me->is_fighting() )
                return notify_fail("战斗中运功疗伤？找死吗？\n");

        if ((int)me->query_skill("hx-jing", 1) < 40)
                return notify_fail("你的欢喜转轮经修为还不够。\n");
        if( (int)me->query("neili") < 50  || (int)me->query("max_neili") < 50 )
                return notify_fail("你的内力不够。\n");

        if( (int)me->query("eff_qi") < (int)me->query("max_qi") / 2 )
                return notify_fail("你已经受伤过重，只怕一运真气便有生命危险！\n");
        if( ((int)me->query("eff_qi") / (int)me->query("max_qi")) > (95/100) )
                return notify_fail("你已经不需要疗伤了！\n");

        write( HIW "你全身放松，坐下来开始运功疗伤。\n" NOR);
        message("vision",
                HIW + me->name() + "吐出一口瘀血，脸色看起来好多了。\n" NOR,
                environment(me), me);

        me->receive_curing("qi", 10 + (int)me->query_skill("force")/3 );
        me->add("neili", -50);
        me->set("jiali", 0);
      me->start_busy(4);

        return 1;
}


