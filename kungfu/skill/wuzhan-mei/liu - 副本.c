// liu.c
// 流花掠影 liu

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill;
		int damage;
        object weapon;

        if (userp(me) && ! me->query("can_perform/wuzhan-mei/liu")) 
                return notify_fail("你还没有受过高人指点，无法施展「流花掠影」。\n"); 
                
        if((skill = me->query_skill("wuzhan-mei",1)) < 100)
                return notify_fail("你的五展梅剑法不够纯熟，无法使用『流花掠影』。\n");

        if( !target ) target = offensive_target(me);

        if( !target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("『流花掠影』只能对战斗中的对手使用。\n");

        if(me->query("neili") < 400 )
                return notify_fail("你目前的内力不足，无法施展『流花掠影』。\n");

        if(!(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "wuzhan-mei")
                return notify_fail("你必须在使用剑时才能使出『流花掠影』。\n");

        me->add("neili",-300);

        message_vision(HIR"$N手中乱抖，幻出一片青光，施展出唐门绝学『流花掠影』。\n\n"NOR,me);

        for(int i=0;i<4;i++)
        {
                // COMBAT_D->do_attack(me,target,TYPE_QUICK);
                COMBAT_D->do_damage(me,target, WEAPON_ATTACK, damage, 50);
        }
        /*
        if(random(target->query("force")) < me->query("force")/2)
        {
                target->apply_condition("weapon_bleeding", 5+random(3));
        }
        */

        me->start_busy(3);
        return 1;
}

