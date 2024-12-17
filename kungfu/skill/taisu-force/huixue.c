// zu.c  by sinb

#include <ansi.h>

inherit F_CLEAN_UP;
string query_name() { return "太素" ZJBR "回血"; }
int hui(object me, int skill);
int exert(object me, object target)
{
        int skill;
        if (me->query("eff_qi") >= me->query("max_qi"))
        {
                me->delete_temp("taisu");
                return notify_fail("你没有受伤！\n");
        }
        if (target != me)
                return notify_fail("你只能用太素心经恢复自己的气血。\n");
        if ((int)me->query("neili") < 1000)
                return notify_fail("你的真气不够！\n");

        if (me->query_temp("taisu"))
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("taisu-force", 1);
        me->set_temp("taisu", 10);
        if (!me->is_fighting())
        {
                hui(me, skill);
        }
        else
        {
                call_out("hui", 5, me, skill);
                write("你受到打击，回血劲道受到延迟压制\n");
        }
        return 1;
}

int hui(object me, int skill)
{
        if (me->query("eff_qi") >= me->query("max_qi"))
        {
                me->delete_temp("taisu");
                return notify_fail("你没有受伤！\n");
        }
        if (!me->query_temp("taisu"))
                return notify_fail("你已经在运功完毕。\n");
        message_combatd(HIC "$N" HIC "运起「回血」劲道，"
                            "眼中闪过一片青芒，随即恢复正常\n" NOR,
                        me);
        me->add("neili", -skill);
        me->add("eff_qi", skill);
        me->add("qi", skill);
        me->add_temp("taisu", -1);
        call_out("hui", 5, me, skill);
        return 1;
}