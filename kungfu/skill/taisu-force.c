// taisu-force.c ̫���ľ�
// by ����ҹ��

inherit FORCE;

int valid_enable(string usage)
{
	return usage == "force";
}

int query_neili_improve(object me)
{
	int lvl;

	lvl = (int)me->query_skill("taisu-force", 1);
	return lvl * lvl * 15 * 22 / 100 / 200;
}

int valid_force(string force)
{
	return 1;
}

int valid_learn(object me)
{
	int lvl = (int)me->query_skill("taisu-force", 1);
//	if ((int)me->query_skill("taisu-force", 1) <150)
		//return notify_fail("���̫���ľ��ȼ���150���������������̫���ľ���\n");
	if ((int)me->query_skill("force", 1) < 200)
		return notify_fail("��Ļ����ڹ���򻹲�����������ѧϰ̫���ľ���\n");

	if (me->query("int") < 25)
		return notify_fail("�����̫���ľ����ڼ�����������������⡣\n");

	if (me->query("con") < 25)
		return notify_fail("��ĸ��ǲ��ã�������ת̫���ľ���\n");

	return ::valid_learn(me);
}

int practice_skill(object me)
{
		if ((int)me->query("qi") < 70)
		return notify_fail("�������̫���ˡ�\n");
	if ((int)me->query("neili") < 70)
		return notify_fail("�������������̫���ľ���\n");

	me->receive_damage("qi", 61);
	me->add("neili", -57);
	return 1;
}

string exert_function_file(string func)
{
	return __DIR__"taisu-force/" + func;
}

int diffcult_level() { return 200; }
