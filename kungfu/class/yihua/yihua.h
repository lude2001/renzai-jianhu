// yihua.h

int permit_recruit(object ob)
{
	object me;

	me = this_object();
	if( ob->query("detach/�ƻ���") ||
	    ob->query("betrayer/�ƻ���") )
	{
		command("say �㵱���Ȼ�뿪���ƻ����������ֺαػ�����");
		return 0;
	}

	if( ob->query("family/family_name") &&
	    ob->query("family/family_name") != "�ƻ���" )
	{
		command("say ��������ʦָ�㣬Ϊ�������ƻ�����"
			"Ī����Ҫ��ʦ���ɣ�");
		return 0;
	}

	return 1;
}
