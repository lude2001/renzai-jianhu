// yeqiu-quan Ұ��ȭ

inherit SKILL;

mapping *action = ({
([	"action" : "ֻ��$N˫ȭ���գ����ٴ��һ�㶢��$n��ͻȻС����������$n��$lһ�����ȭ",
	"force"  : 120,
	"dodge"  : 10,
	"damage" : 2,
	"lvl"    : 0,
	"skill_name" : "ʯͷ",
	"damage_type" : "����"
]),
([	"action" : "$N����$n�������´���һ�������治��ֱ��$n˫��",
	"force"  : 140,
	"dodge"  : 12,
	"damage" : 5,
	"lvl"    : 20,
	"skill_name" : "����",
	"damage_type" : "����"
]),
([	"action" : "$N���˶�ţ�����ȥһ��ץס$n��ͷ����һ�ֶ���$n���������ҿ���",
	"force"  : 150,
	"dodge"  : 16,
	"damage" : 15,
	"lvl"    : 40,
	"skill_name" : "��",
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "cuff" || usage == "parry"; }

//int valid_combine(string combo) { return combo == "canhe-zhi"; }

int valid_learn(object me)
{
	if (objectp(me))
		return notify_fail("Ұ��ȭ����������\n");

/*	if ((int)me->query_skill("force") < 30)
		return notify_fail("����ڹ���򲻹����޷���Ұ��ȭ��\n");

	if ((int)me->query("max_neili") < 120)
		return notify_fail("�������̫�����޷���Ұ��ȭ��\n");

	if (me->query_skill("cuff", 1) < me->query_skill("yeqiu-quan", 1))
		return notify_fail("��Ļ���ȭ���������ޣ��޷����������Ұ��ȭ��\n");
*/
	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("yeqiu-quan", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i - 1]["lvl"])
			return action[NewRandom(i, 20, level  /5)];
}

int practice_skill(object me)
{

if (objectp(me))
		return notify_fail("Ұ��ȭ����������\n");

	if ((int)me->query("qi") < 50)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 30)
		return notify_fail("�������������Ұ��ȭ��\n");

	me->receive_damage("qi", 36);
	me->add("neili", -18);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"yeqiu-quan/" + action;
}

