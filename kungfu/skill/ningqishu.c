inherit SKILL;

string type() { return "knowledge"; }

int valid_enable(string usage) { return usage == "fufa"; }

int valid_learn(object me)
{
    if (me->query("family/family_name") != "�䵱��" && me->query("family/family_name") != "ȫ���")
        return notify_fail("�ǵ��������޷�������������\n");
    
	if ((int)me->query_skill("fufa", 1) < 100)
		return notify_fail("��ķ�����������̫ǳ����"
				   "�������µ���������\n");

	if ((int)me->query_skill("fufa", 1) < (int)me->query_skill("ningqishu", 1))
		return notify_fail("��ķ�������ˮƽ���ޣ���"
				   "�����ո���µ���������\n");

	return 1;
}


string perform_action_file(string action)
{
	return __DIR__"ningqishu/" + action;
}