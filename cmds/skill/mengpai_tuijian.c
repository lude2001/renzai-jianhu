
inherit F_CLEAN_UP;

int lv_fa(object me,string family_name);

int main(object me, string arg)
{

	string *chooseList = ({ "��ɽ��","��������","�ϻ���" });
	string *yjList;
	int tg = 0;

	// if (!me->query("family"))
	// return notify_fail("�㻹�����Ҹ������ٿ����Լ���û�б��Ƽ����ʸ�ɣ�\n");

	if (!me->query("yijing"))
	return notify_fail("����δ������ο��Ի�ȡ�Ƽ��ʸ�,�����˲�Ҫ�ø���Զ��\n");

	yjList = keys(me->query("yijing"));

	foreach (string name in yjList)
	{
		string family_name = me->query("yijing/" + name + "/" + "family/family_name");

		if (!me->query("yijing/" + name + "/family"))
			continue;

		if ((lv_fa(me,family_name) && FAMILY_D->query_family_leader(family_name) == me->query("id")) || wizardp(me))
			tg = 1;
	}

	if (!tg)
	return notify_fail("��û���ڱ���û�л���⾳�������ɵ���ϯ�������ݣ��޷�����Ƽ��ʸ�\n");


	if (me->query("family"))
	return notify_fail("���������ɣ��޷���ȡ�ʸ񣬻��ǹ���ȴ�ʦ�Ŷ�׼��������˵�ɣ�\n");
	
	// if (!lv_fa(me,me->query("family/family_name")) || !FAMILY_D->query_family_leader(me->query("family/family_name")) != me->query("family/famiy_name"))
	// return notify_fail("�㻹û�л��" + me->query("family/family_name") + "��ϯ���ӵ���ݣ�û���Ƽ��ʸ�\n");


	if (!arg)
	{
		string *list = ({ }),msg = ZJOBLONG"����ѡ����Ҫ�Ƽ�ȥ�ĸ߽�����\n";

		foreach (string choose in chooseList)
		{
			list += ({ choose + ":mengpai_tuijian " + choose });
		}

		msg += ZJOBACTS2 + implode(list,ZJSEP);
		msg += "\n";

		write(msg);
	}

	if (arg)
	{

		if (!member_array(arg,chooseList) == -1)
		return notify_fail("��������δ���š�\n");

		me->set("mengpai_tuijian/" + arg,1);

		write(sprintf("��ϲ������ϯ����ӵ���ݣ�������Ƽ���%s���ʸ�\n",arg));

	}

    return 1;
}

//1������������⾳����
int lv_fa(object me,string family_name)
{
    if (!me->query("yijing"))
    return 0;
    
    foreach (string name in keys(me->query("yijing")))
    {
        if (me->query("yijing/" + name + "/family/family_name") == family_name)
        return 1;
    }
    return 0;
}