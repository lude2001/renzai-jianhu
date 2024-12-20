
#include <ansi.h>
inherit SKILL;
void throw_weapon(object,object,object,int);

mapping *action = ({
  ([
    "action":
"$N把"HIY"$w"NOR"平举起，脚一点地，全身螺旋般的旋起，朝着$n飞了过去!",
    "damage":      100,
    "dodge":      -20,
    "parry":      -10,
    "damage_type": "刺伤",
    "name":      "闪电惊虹",
    "lvl" :        10,
    ]),
  ([
    "action":
"$N一跃而起，在空中高举"HIY"$w"NOR"，大喝一声，对准$n的$l砸去！",
    "damage":   150,
    "dodge":   -20,
    "parry":   -20,
    "damage_type":   "劈伤",
    "name":     "雷霆万钧",
    "lvl" :        20,
    ]),
  ([
    "action":
"$N把"HIY"$w"NOR"拉得满满的，突然一放，只觉得一股劲气朝着$n呼啸而去!",
    "damage":   200,
    "dodge":       -10,
    "parry":       -10,
    "damage_type":   "刺伤",
    "name":     "虚张气势",
    "lvl" :        40,
    ]),
  ([
    "action":
"$N挥起手中的"HIY"$w"NOR"朝着$n的腹部击去，\n却突然把"HIY"$w"NOR"一横，想把$n的手套在弓上!",
    "damage":   250,
    "dodge":       -20,
    "parry":   10,
    "damage_type":   "刺伤",
    "name":     "声东击西",
    "lvl" :        60,
    ]),
  ([
    "action":
"只见$N按着八卦图形疾走，旋起一团尘土来扰乱$n的视线，\n然后握紧"HIY"$w"NOR"对准$n的$l砸去!",
    "damage":   300,
    "dodge":   10,
    "parry":   -10,
    "damage_type":   "砸伤",
    "name":     "雾里刺花",
    "lvl" :        80,
    ]),
  ([
    "action":
"$n纵身而起，正待凌空一击。$N的手臂一松，象灵蛇一样\n在$n的劲气中穿梭，然后拿起"HIY"$w"NOR"对准$n的防御盲区猛地刺去!",
    "damage":       500,
    "dodge":       -10,
    "parry":       -10,
    "damage_type":  "刺伤",
    "name":       "游刃有余",
    "lvl" :         100,
    ]),
});
 
int valid_learn(object me)
{
        object ob;
  
        if(me->query_skill("throwing",1) < 20)
                return notify_fail("你的基本暗器还不够纯熟。\n");
        if( (int)me->query("max_neili") < 100 )
                return notify_fail("你的内力不够，挥不动暗器！\n");
        if( (int)me->query_skill("yiqiguan-riyue",1) < 50 )
                return notify_fail("你对本门内功心法领悟的不够。\n");
        if( !(ob=me->query_temp("weapon")) || (string)ob->query("skill_type") != "throwing" )
                return notify_fail("手中无箭怎能领悟所学？\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("youren-jian",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 50, level)];
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

int valid_enable(string usage)
{
        return (usage=="throwing" || usage=="parry");
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon = me->query_temp("weapon"))
             ||      (string)weapon->query("skill_type") != "throwing" )
            return notify_fail("没有箭如何练？\n");
        if( (int)me->query("qi") < 40 || (int)me->query("neili") < 10)
                return notify_fail("你的体力不足，挥不动弓！\n");
        me->receive_damage("qi", 20);
        me->add("neili", -5);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"youren-jian/" + action;
}