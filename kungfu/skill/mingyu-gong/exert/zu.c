// zu.c  by sinb

#include <ansi.h>

inherit F_CLEAN_UP;
string query_name() { return "明玉"ZJBR"气足"; }
int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("你只能用明玉功恢复自己的气血。\n");

        if ((int)me->query("neili") < me->query("max_neili") / 2)
            return notify_fail("你的真气不够！\n");
            
        if ((int)me->query("jing") < me->query("max_jing") / 2)
            return notify_fail("你的精力不够。\n");
            
        if (me->query_condition("mingyu_qizu"))
                return notify_fail("你已经在运功中了。\n");
        if (!me->is_fighting())
            return notify_fail("明玉气足仅能在战斗中使用。\n");
        
        skill = me->query_skill("mingyu-gong", 1);

        /*me->add("neili", -1500);
        me->add("jing", -1500);*/
        
        me->add("neili", -me->query("max_neili") / 2);
        me->add("jing", -me->query("max_jing") / 2);
        me->set("eff_qi", me->query("max_qi"));     
        me->set("qi", me->query("eff_qi"));
        message_combatd(HIC "$N" HIC "运起「气足」奇功，"
                        "眼中闪过一片青芒，随即恢复正常\n" NOR, me);


        //me->apply_condition("mingyu_qizu", skill / 100);
        if (me->is_fighting()) me->start_busy(5);

        return 1;
}

