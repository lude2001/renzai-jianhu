// This program is a part of NITAN MudLIB
// yanzi-blade.c (����˫�ɵ���)

#include <ansi.h>;
inherit SKILL;

mapping *action = ({
([      "action" : "$Nһʽ" HIM "������˫�ɡ�" NOR "���ط��֣�$w��β�����ϵ��������벻����λ������$n$l��ȥ",
        "force"  : 120,
        "attack" : 40,
        "dodge"  : 30,
        "parry"  : 15,
        "lvl"    : 0,
        "damage" : 40,
        "damage_type" : "����",
        "skill_name"  : "����˫��",
]),
([      "action" : "$NͻȻһ����Х��һ��" HIR "��˫��س���" NOR "����ʵʵ�����Ƕ��ǵĿ���$n��$l",
        "force"  : 150,
        "attack" : 45,
        "dodge"  : 40,
        "parry"  : 20,
        "lvl"    : 40,
        "damage" : 60,
        "damage_type" : "����",
        "skill_name"  : "˫��س�",
]),
([      "action" : "����$N��ζ�������Ȼ����$n�Ҳ���������," HIB "���������衹" NOR "���$w������$n��$l��ȥ",
        "force"  : 180,
        "attack" : 51,
        "dodge"  : 45,
        "parry"  : 25,
        "lvl"    : 60,
        "damage" : 80,
        "damage_type" : "����",
        "skill_name"  : "��������",
]),
([      "action" : "$N���е�$w����һ������Ȧ�ӣ�һ��" HIW"���췽��԰��" NOR"��$n��$l��ȥ",
        "force"  : 220,
        "attack" : 55,
        "dodge"  : 50,
        "parry"  : 30,
        "lvl"    : 80,
        "damage" : 95,
        "damage_type" : "����",
        "skill_name"  : "�췽��԰",
]),
});

int valid_enable(string usage){ return usage == "blade" || usage == "parry";}

int valid_learn(object me)
{     
        if ((int)me->query("dex") < 50)
                return notify_fail("���о��˰��죬ֻ�����Լ��������鶯�ԣ������޷���ϰ�����书��\n");

        if ((int)me->query("max_neili") < 800)
                return notify_fail("�������������\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ����̫ǳ��\n");

        if ((int)me->query_skill("blade", 1) < 120)
                return notify_fail("��Ļ�������������������������˫�ɵ�����\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("yanzi-blade", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷��������������˫�ɵ�����\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

int practice_skill(object me)
{
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon"))|| (string)weapon->query("skill_type") != "blade")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query("qi") < 80)
                return notify_fail("�����������������������˫�ɵ�����\n");

        if ((int)me->query("neili") < 120)
                return notify_fail("�����������������������˫�ɵ�����\n");

        me->receive_damage("qi", 64);
        me->add("neili", -84);
        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("yanzi-blade", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

string perform_action_file(string action)
{
        return __DIR__"yanzi-blade/" + action;
}