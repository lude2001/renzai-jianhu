// This program is a part of NITAN MudLIB
// nizhuan.c

#include <ansi.h>

inherit F_CLEAN_UP;
string query_name() { return "逆运"ZJBR"九阴"; }
void remove_effect(object me, int amount);

int exert(object me, object target)
{
        object weapon;
        int skill;
        string msg;

        if((int)me->query_skill("hamagong", 1) < 200)
                return notify_fail("你的蛤蟆功不够娴熟，不会逆转九阴。\n");

        if( me->query("neili")<500 )
                return notify_fail("你的内力不够。\n");

        if( me->query("jingli")<500 )
                return notify_fail("你的精力不够。\n");

        if( me->query_temp("hmg_nizhuan") )
                return notify_fail("你已经逆运了九阴。\n");

        skill = me->query_skill("hamagong", 1);
        msg = HIB "$N" HIB "双手撑地，口中发出一连窜低喉声，一股股内劲勃发使$N" HIB "双足离地，呈头下足上之势。。\n" NOR;
        message_combatd(msg, me);
        tell_object(me, HIW "你感觉体内蛤蟆功随九阴逆转，好像有股巨大的力量要崩发出来一样。\n" NOR);

        me->add_temp("apply/ap_power", 50);
        me->add_temp("apply/add_damage", 50);
        me->add_temp("apply/attack", skill);
        me->add_temp("apply/avoid_xuruo", 50);
        me->add_temp("apply/str", skill/10);
        me->set_temp("hmg_nizhuan", skill);
        me->add("neili", -300);
        me->add("jingli", -50);
        me->start_call_out( (: call_other, this_object(), "remove_effect", me, skill :), skill);
        if(me->is_fighting())
                me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( !me ) return;

        me->add_temp("apply/str", -amount/10);
        me->add_temp("apply/attack", -amount);
        me->add_temp("apply/ap_power", -50);
        me->add_temp("apply/add_damage", -50);
        me->add_temp("apply/avoid_xuruo", -50);
        me->delete_temp("hmg_nizhuan");

        tell_object(me, HIW "你逆转九阴运功过久，经脉又渐渐复原。\n" NOR);
}
