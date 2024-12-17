// ̫������ʽ��һ�ֳɳ����书

inherit SKILL;

mapping *action = ({
([
	"action" : "$Nһ�С��������ա���ȭ���������͹���ǰ������$n��$l",
	"lvl" : 0,       
	"damage_type" : "����"
]),
([
	"action" : "$N��ü΢��˫ȭֱ����һ�С��������ġ���ȭ���ɹ�͸��������$n��$l",
	"lvl" : 10,
	"damage_type" : "����"
]),
([
	"action" : "$Nʹһ�С��������¡�����������һ�����������ȭ�����±�����ȭ������ӿ$n��$l",
	"lvl" : 20,
	"damage_type" : "����"
]),
([
	"action" : "$Nһʽ�����º��ǡ���$n��$l��ȥ������֮��,��������",
	"lvl" : 30,
	"damage_type" : "����"
]),
([
	"action" : "$Nһ����շ�����һ�С����¸߿��ա���˫ȭ��ѹ��$n",
	"lvl" : 40,
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="cuff" || usage=="parry"; }

int valid_learn(object me)
{
//int lvl =me->query_skill("taisu-moon",1);
//if (lvl <150)
		//return notify_fail("���̫���ľ��ȼ���150���������������̫���ľ���\n");
if (me->query("str")<25)
return notify_fail("��̫������ʽ�����������Դ���25��\n");
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("��̫������ʽ������֡�\n");
	if ((int)me->query("max_neili") < 1000)
		return notify_fail("�������̫�����޷�����̫������ʽ��\n");
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
	int i, level, j;
	level   = (int) me->query_skill("taisu-moon",1);
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([  
				"action":	action[j]["action"],
				"lvl":		action[j]["lvl"],
				"damage_type":	action[j]["damage_type"],
				"force":	level/2,
				"dodge":	level/2,
				"parry":	level/2,
			]);
		}
	}
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 50)
		return notify_fail("�������̫���ˡ�\n");
	if ((int)me->query("neili") < 100)
		return notify_fail("�������������̫������ʽ��\n");
//	me->receive_damage("jingli", 50);
me->receive_damage("qi",50);
	me->add("neili", -50);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"taisu-moon/" + action;
}

int diffcult_level() { return 200; }
