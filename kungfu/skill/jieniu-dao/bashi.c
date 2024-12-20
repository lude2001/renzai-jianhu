//解牛八式
// by mudwu
#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>
inherit F_SSERVER;

string query_name() { return "解牛八式"; }

int perform(object me, object target)
{
        object weapon, ob;
    string msg;
        if( !me->is_fighting() )
            return notify_fail("「"+HIY"解牛八式"NOR+"」只能在战斗中使用。\n");
        if (!objectp(weapon = me->query_temp("weapon"))
                || (string)weapon->query("skill_type") != "blade")
                        return notify_fail("你使用的武器不对。\n");
        if((int)me->query_str() < 40)
                return notify_fail("你的臂力不够, 还不能使用这项绝技! \n");
        if((int)me->query_skill("blade",1) < 250)
                return notify_fail("你的基本刀法的火候还不到家, 不能使用这一绝技 !\n");
          if (me->query_skill_mapped("blade") != "jieniu-dao")  
                return notify_fail("你没有激发解牛刀，无法施展「解牛八式」。\n"); 
        if((int)me->query_skill("jieniu-dao",1) < 250)
                return notify_fail("你的井中八法的火候还不到家, 不能使用这一绝技 !\n");
        if( (int)me->query("neili") < 5000 )
                return notify_fail("你的真气不够！\n");
        if( (int)me->query("max_neili") < 5000 )
                return notify_fail("你的内力修为不够！\n");
    msg = 
HIW "\n$N凌空飞起,手中兵器发出奇异的光芒，接着一片片如实质般刀光狂涌向对手。\n" NOR;
        message_vision(msg, me);
        me->clean_up_enemy();
        ob = me->select_opponent();
        COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 0);
        COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 0);
        COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 0);
        COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 0);
        COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 0);
        COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 0);
        COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 0);
        COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 0);
        me->add("neili",-random(2500)-150);
                  me->start_busy(3+random(1));
    return 1;
}


