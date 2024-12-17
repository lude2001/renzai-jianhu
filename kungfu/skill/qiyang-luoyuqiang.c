inherit SKILL;

mapping *action = ({
([      "action":"$Nһ�С�ƽ���̡���˫���趯$w������$n�Ĵ�ȥ",
	"force" : 120,
	"attack": 25,
	"dodge" : 5,
	"parry" : 30,
	"damage": 10,
	"lvl"   : 0,
	"skill_name" : "ƽ����",
	"damage_type":"����"
]),
([      "action":"$N����$w�������������趯��Ȧ,һ�С�����ɨ����$w�͵ؾ���$n",
	"force" : 150,
	"attack": 37,
	"dodge" : 5,
	"parry" : 31,
	"damage": 15,
	"lvl"   : 40,
	"skill_name" : "����ɨ",
	"damage_type":"����"
]),
([      "action":"$Nһ�С��߽��߳���������$w��$n���ظ�����������",
	"force" : 180,
	"attack": 42,
	"dodge" : 5,
	"parry" : 37,
	"damage": 20,
	"lvl"   : 80,
	"skill_name" : "�߽��߳�",
	"damage_type":"����"
]),
([      "action":"$N���ֵ��ճ�ǹ��һ�С�ŭ��������$w���ƿ�֮���͵�����$n��ͷ��",
	"force" : 210,
	"attack": 43,
	"dodge" : 15,
	"parry" : 35,
	"damage": 25,
	"lvl"   : 100,
	"skill_name" : "ŭ����",
	"damage_type":"����"
]),
([      "action":"$Nһ�С���������������ǹ��һ��ǹ��Э�Ʒ�֮�ƣ���ͬ�����Ҷ�����$n��$l",
	"force" : 240,
	"attack": 49,
	"dodge" : 20,
	"parry" : 41,
	"damage": 30,
	"lvl"   : 120,
	"skill_name" : "��������",
	"damage_type":"����"
]),
([      "action":"$N˫���趯$�γ�һ��������״��ԲȦ��˫�ȷ��������벽,ֻ����һ�С����ǹ��ա���һǹ�������͵Ļ�����ײ��$n���ؿ�",
	"force" : 270,
	"attack": 58,
	"dodge" : 20,
	"parry" : 45,
	"damage": 35,
	"lvl"   : 140,
	"skill_name" : "���ǹ���",
	"damage_type":"����"
]),
([      "action":"$Nһ�С���籩�꡹����ǰ�����趯$w����$n��ȫ��",
	"force" : 300,
	"attack": 61,
	"dodge" : 25,
	"parry" : 52,
	"damage": 40,
	"lvl"   : 160,
	"skill_name" : "��籩��",
	"damage_type":"����"
]),
([      "action":"$N����$w���Ա���֮�Ƴ���$n���,����һ������,һ�С���̧ͷ��,�͵�����$n",
	"force" : 320,
	"attack": 63,
	"dodge" : 30,
	"parry" : 55,
	"damage": 50,
	"lvl"   : 180,
	"skill_name" : "��̧ͷ",
	"damage_type":"����"
]),
});

int valid_enable(string usage) { return usage == "club" || usage == "parry"; }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 20000)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 650)
		return notify_fail("����ڹ����̫ǳ��\n");

	if ((int)me->query_skill("qiang", 1) < (int)me->query_skill("qiyang-luoyuqiang", 1))
		return notify_fail("���ǹ����Ϊˮƽ���ޣ��޷������������������ǹ��\n");

	return 1;
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if (level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("qiyang-luoyuqiang", 1);
	for(i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	object weapon;

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "club")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 70)
		return notify_fail("���������������������ǹ��\n");

	if ((int)me->query("neili") < 70)
		return notify_fail("���������������������ǹ��\n");

	me->receive_damage("qi", 62);
	me->add("neili", -61);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"qiyang-luoyuqiang/" + action;
}
