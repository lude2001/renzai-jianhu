//ningshenforce.c
//����ɽ���ɡ�by yushu 2001.2



inherit FORCE;

int valid_enable(string usage)
{ 
	return usage == "force"; 
}

int query_neili_improve(object me)
{
	int lvl;

	lvl = (int)me->query_skill("shushan-force", 1);
	return lvl * lvl * 15 * 25 / 100 / 200;
}

int valid_force(string force)
{
	return 1;
}

int valid_learn(object me) 
{ 
	int lvl = (int)me->query_skill("shushan-force", 1);

	if (me->query("gender") == "����" && (int)me->query_skill("shushan-force", 1) > 49)
		return notify_fail("���޸����ԣ������������������������ɽ�ķ���\n");

	if ((int)me->query_skill("force", 1) < 100)
		return notify_fail("��Ļ����ڹ���򻹲�����������ѧϰ��ɽ�ķ���\n");

	if (me->query("int") < 30)
		return notify_fail("�������ɽ�ķ����ڼ��������⡣\n");

	return ::valid_learn(me);
}


int practice_skill(object me)
{
        return notify_fail("��ɽ�ķ�ֻ����ѧ�ģ����Ǵ�����(exert)�����������ȡ�\n");
}
string exert_function_file(string func)
{
        return __DIR__"shushan-force/" + func;
}

