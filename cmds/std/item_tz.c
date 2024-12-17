inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;

	string expend,weaponId;

	mapping tzList = ([
		"��":({ 
			"sword",   //��������
			"blade",   //��������
			"staff",   //�����ɷ�
			"hammer",  //��������
			"club",	   //��������
			"whip",	   //�����޷�
		 }),
		"ˮ":({ 
			"force"
		}),
		"ľ":({ 
			"unarmed", //����ȭ��
			"cuff",	   //����ȭ��
			"strike",  //�����Ʒ�
			"finger",  //����ָ��
			"hand",	   //�����ַ�
			"claw",	   //����צ��
		}),
		"��":({
			"dodge",
		}),
		"��":({
			"parry",
		})
	]);

	
	if (objectp(present(arg,me)))
	{
		string msg;

		if (!objectp(ob = present(arg, me)))
		return notify_fail("������û���������߰���\n");

		if (ob->is_weapon() || ob->is_unarmed_weapon())
		return notify_fail("��ֻ�ܶԷ��߽��м�����\n");

		msg = ZJOBLONG"����Զ�" + ob->name() + "���м���,Ԫ����������180Ԫ����ͨ����������240ͨ����\n";
		msg += ZJOBACTS2"Ԫ������:item_tz yuanbao " + ob->query("id") + ZJSEP;
		msg += "ͨ������:item_tz yuan_bao " + ob->query("id") + "\n";
		write(msg);
		return 1;
		
	}

	if (!arg || sscanf(arg,"%s %s",expend,weaponId) != 2)
		return notify_fail("�������Ͳ��ԡ�\n");

	if (!objectp(ob = present(weaponId, me)))
		return notify_fail("������û���������߰���\n");

	if (ob->is_weapon() || ob->is_unarmed_weapon())
		return notify_fail("��ֻ�ܶԷ��߽��м�����\n");

	
	if (expend != "yuanbao" && expend != "yuan_bao")
	return notify_fail("��Ĳ������Ͳ��ԡ�\n");
	
	if (expend == "yuanbao")
	{
		if (me->query(expend) < 180)
		return notify_fail("���Ԫ����������180,�޷���ɼ�����\n");

		me->add(expend,-180);

	}

	if (expend == "yuan_bao")
	{
		if (me->query(expend) < 240)
		return notify_fail("���ͨ����������240,�޷���ɼ�����\n");

		me->add(expend,-240);
	}



	write(sprintf("�㿪ʼ����ȫ�������Լ���Ѫ����ʼ����%s����ͼʹ��������һ��������\n",ob->name()));

	if (random(60) == 1 || me->query("item_tz/uplv") >= 60)
	{
		string type,skill,*types;

		types = keys(tzList);

		type = types[random(sizeof(types))];
		skill = tzList[type][random(sizeof(tzList[type]))];

		ob->set("magic/tz_type/skill",skill);
		ob->set("magic/tz_type/attribute",type);
		ob->delete("item_tz/uplv");
		ob->save();

		write(sprintf("���%s���������ɹ��Ļ����%s����-%s��\n",ob->name(),type,to_chinese(skill)));
		return 1;
	}
	else
	{
		me->add("item_tz/uplv",1);
		write(sprintf("���ź���%s����ʧ�ܣ�ǰ�������ˣ����ٽ�����!\n",ob->name()));
		write(sprintf("��ǰ�Ѿ�������%d�Ρ�\n",me->query("item_tz/uplv")));
	}

	return 1;
}