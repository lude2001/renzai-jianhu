
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N面对$n而立，面无惧色，一式「披襟当风」，$w平平递了出去",
        "damage" : 100,
        "parry"  : 0,
        "force"  : 100,
        "lvl"  : 0,
        "dodge"  : 0,
        "skill_name" : "披襟当风",
        "damage_type" : "刺伤"
]),
([      "action" : "$N步伐轻灵，绕着$n游走，突然一停，手中$w一式「云绕巫山」飞斩$n而去",
        "damage" : 100,
        "parry"  : 0,
        "force"  : 100,
        "lvl"  : 0,
        "dodge"  : 0,
        "skill_name" : "云绕巫山",
        "damage_type" : "划伤"
]),
([      "action" : "$N展臂急挥$w，划出万道光霞，一式「千水一流」，万光合一钉向$n的$l",
        "damage" : 100,
        "parry"  : 0,
        "force"  : 100,
        "lvl"  : 0,
        "dodge"  : 0,
        "skill_name" : "千水一流",
        "damage_type" : "刺伤"
]),
([      "action" : "$N人越半空，$w凌空击下点出片片剑光，一式「雪花太山」真如雪花满天无处可躲",
        "damage" : 100,
        "parry"  : 0,
        "force"  : 100,
        "lvl"  : 0,
        "dodge"  : 0,
        "skill_name" : "雪花太山",
        "damage_type" : "划伤"
]),
([      "action" : "$N一式「山水飘摇」，剑无形、人无影，如缕轻烟飘飘然向$n攻了过去",
        "damage" : 100,
        "parry"  : 0,
        "force"  : 100,
        "lvl"  : 0,
        "dodge"  : 0,
        "skill_name" : "山水飘摇",
        "damage_type" : "划伤"
]),
([      "action" : "$N左手捏一剑诀，右手$w高举，一式「观澜瀑剑」向$n横斩过去",
        "damage" : 100,
        "parry"  : 0,
        "force"  : 100,
        "lvl"  : 0,
        "dodge"  : 0,
        "skill_name" : "观澜瀑剑",
        "damage_type" : "刺伤"
]),
([      "action" : "$N脚下乱踏倒七星，手中$w使一式「星摇斗晃」，摇摆中出手，竟然看不出目标何在",
        "damage" : 100,
        "parry"  : 0,
        "force"  : 100,
        "lvl"  : 0,
        "dodge"  : 0,
        "skill_name" : "星摇斗晃",
        "damage_type" : "划伤"
]),
([      "action" : "$N脚一点地，飞旋而起，一式「天河飞遁」，人剑合一逼出道道剑芒，直扑$n而去",
        "damage" : 100,
        "parry"  : 0,
        "force"  : 100,
        "lvl"  : 0,
        "dodge"  : 0,
        "skill_name" : "天河飞遁",
        "damage_type" : "刺伤"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; } 

int valid_learn(object me)
{
        mapping myfam;
        myfam = (mapping)me->query("family");

        if ((int)me->query("max_neili") < 300)
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("sword", 1) < 50)
                return notify_fail("你的剑法火候太浅。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
        if(level >= action[i]["lvl"])
                return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;

        level   = (int) me->query_skill("tianhe-jian",1);

        for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"])
                return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");
        if ((int)me->query("qi") < 50)
                return notify_fail("你的体力不够练“天河剑法”。\n");
        me->receive_damage("qi", 30);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"tianhe-jian/" + action;
}


mixed hit_ob(object me, object victim, int damage_bonus)
{
        object obb;
        string msg;
        
        if( damage_bonus < 100 ) return 0;
        if (!(me->query("yiqiguan-riyue"))) return 0;
        if( random(damage_bonus/2) > victim->query_str() ) {        
                if (me->query("yiqiguan-riyue")==1) {
                        victim->receive_wound("qi", (damage_bonus - 100) / 2 );
                        msg= WHT "$n一个不防，被剑气中夹杂的「从心所欲」内劲所伤。\n" NOR;
                }
                if (me->query("yiqiguan-riyue")==2) {
                        victim->receive_wound("qi",damage_bonus/2 );
                        msg= CYN "$n一个不防，被剑气中夹杂的「登峰造极」内劲所伤。\n" NOR;
                }
                return msg;
        }
}
