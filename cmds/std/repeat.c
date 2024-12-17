// cut.c

#include <ansi.h>

inherit F_CLEAN_UP;
mapping repeat_quest_level = (["liu mang":1,
							"xiao hunhun":1,
							  "guan bing":1,
							   "yang guo":3,
								"long nv":2,
								  "tuoba":1,
							"ma chaoxing":1,
								 "du she":1,
							  "huanan hu":1,
								 "dao ke":1,
]);

mapping repeat_quest_name = (["liu mang":"������å",
						   "xiao hunhun":"�ͽ�С���",
							 "guan bing":"�����ٱ�",
							  "yang guo":"��ɱ���",
							   "long nv":"��ɱС��Ů",
								 "tuoba":"��ɱ�ذ�",
						   "ma chaoxing":"��ɱ����",
								"du she":"������",
							 "huanan hu":"�����ϻ�",
								"dao ke":"��������",
]);

mapping repeat_quest_number = (["liu mang":50,
							 "xiao hunhun":50,
							   "guan bing":30,
								"yang guo":1,
								 "long nv":1,
								   "tuoba":1,
							 "ma chaoxing":1,
								  "du she":50,
							   "huanan hu":50,
								  "dao ke":30,
]);

mapping english_number = (["һ":"one",
						   "��":"two",
						   "��":"three",
						   "��":"four",
]);
int distribution_quest(object me);
int finish_quest(object me);

//��װzj����
string popup(string str)
{
	string msg;
	msg = ZJOBLONG + str;
	msg = replace_string(msg, "\n", ZJBR);
	return msg + "\n";
}
//��������zj����
string popup_key(string str)
{
	str = ZJOBACTS2 + ZJMENUF(2, 2, 9, 30) + str;
	return str + "\n";
}
//�������ַ�����ֱ�ӵ���
string popup_input(string str, string order)
{
	return INPUTTXT(str, order + "$txt#") + "\n";
}

int main(object me, string arg)
{
	object ob;
	string *repeat_information;
	string str, msg;

	repeat_information = keys(repeat_quest_name);

	if (!arg)
	{

		if (me->query("repeat") && time() >= (me->query("repeat/time") + 3600))
		{

			me->delete ("repeat");

			return notify_fail(popup("����ʱ�䵽�������Զ����ϣ������³�ȡ����"));
		}
		//ÿ����Сʱ�Զ���������
		if (time() >= me->query("quest_give/time") + 14400 || !me->query("quest_give"))
		{
			write(popup("ʱ���ѵ����Զ�����������"));
			distribution_quest(me);
		}

		if (me->query("quest_give") && !me->query("quest_give/number"))
			return notify_fail(popup(sprintf("��ǰ������ȫ����ɣ��������%s����ˢ����ȡ�µ�����", CHINESE_D->chinese_time(me->query("quest_give/time") + 14400 - time()))));

		repeat_information = me->query("quest_give/number");

		str = "��Ŀǰ���������ȡ������ѭ������\n";
		str += "��Щ������" + CHINESE_D->chinese_time(me->query("quest_give/time") + 14400 - time()) + "��ˢ��\n";
		str += HIC "��" HIY "һһһһһһһһһһһһһһһһһһһһ" HIC "��" NOR "\n";
		// ����(�������/����)[��ȡ״��]
		foreach (msg in repeat_information)
			//	    if (!me->query("quest_give/finish/"+msg))
			str += sprintf("��%d����%s(%d/%d)[%s]\n", repeat_quest_level[msg], repeat_quest_name[msg], me->query("repeat/npc_" + msg), repeat_quest_number[msg], me->query("repeat/quest_" + msg) ? HIY "����ȡ" NOR : HIR "δ��ȡ" NOR);

		if (me->query("repeat"))
			str += sprintf("������ȡ%s����Ŀǰ���������������%s������ץ��ʱ�䡣\n", repeat_quest_name[me->query("repeat/name")], CHINESE_D->chinese_time(me->query("repeat/time") + 3600 - time()));
		str += "�����ִ�����²�����\n";
		str += HIC "��" HIY "һһһһһһһһһһһһһһһһһһһһ" HIC "��" NOR;
		str = popup(str);
		msg = "";
		if (me->query("repeat"))
			msg += "ʹ�ü��ٿ�:repeat accelerate" ZJSEP;
		msg += "��ȡ�������:repeat receive" ZJSEP;
		msg += "�ύ�������:repeat finish";
		str += popup_key(msg);
		write(str);
	}
	repeat_information = me->query("quest_give/number");

	//�ڶ��μ���ָֹ����ȡ
	if (me->query("quest_give") && !me->query("quest_give/number"))
		return notify_fail(popup(sprintf("��ǰ������ȫ����ɣ��������%s����ˢ����ȡ�µ�����", CHINESE_D->chinese_time(me->query("quest_give/time") + 14400 - time()))));

	if (arg == "receive")
	{
		string receive;
		if (me->query("repeat"))
			return notify_fail(popup("���Ѿ���ȡ�������ˣ��Ȱ�������˰�"));

		receive = repeat_information[random(sizeof(repeat_information))];

		me->set("repeat/quest_" + receive, 1);
		me->set("repeat/name", receive);
		me->set("repeat/time", time());
		write(popup(sprintf("��ϲ�������ȡ����%s����������Ҫ����һСʱ����ɣ������Զ���������ץ��ʱ��ɣ�", repeat_quest_name[receive])));
	}

	if (arg == "finish")
	{
		string receive = me->query("repeat/name");
		if (!me->query("repeat"))
			return notify_fail(popup("�㻹������ȡһ������ɣ���Ȼ���ύ��������"));

		if (me->query("repeat/npc_" + receive) < repeat_quest_number[receive])
			return notify_fail(popup("�㻹û�������������أ���ô������ΰ���"));

		return finish_quest(me);
	}

	if (arg == "accelerate")
	{
		object obj;
		string obj_name;
		if (!me->query("repeat"))
			return notify_fail(popup("�㻹������ȡһ������ɣ���Ȼ����ٿ�������"));
		obj_name = english_number[chinese_number(repeat_quest_level[me->query("repeat/name")])] + " card";
		//	write(obj_name+"\n");
		if (!objectp(obj = present(obj_name, me)))
			return notify_fail(popup("�㻹û�����ּ��ٿ�����ô������ΰ���"));
		obj->add_amount(-1);
		return finish_quest(me);
	}
	return 1;
}

int distribution_quest(object me)
{
	int i = 0;
	string *quest_give = ({});
	while (i < 4)
	{
		string quest_id, *quest_name = keys(repeat_quest_name);
		quest_id = quest_name[random(sizeof(quest_name))];
		if (sizeof(quest_give) && member_array(quest_id, quest_give) != -1)
			continue;
		quest_give += ({quest_id});
		i++;
	}
	me->delete ("quest_give");
	//�����ԭ����Ϣ��
	me->set("quest_give/number", quest_give);
	me->set("quest_give/time", time());
	return 1;
}

int finish_quest(object me)
{

	string receive = me->query("repeat/name");
	int quest_exp, quest_pot;
	string *quest_give = ({});

	quest_exp = 2000 * pow(repeat_quest_level[receive], 2);
	quest_pot = 1500 * pow(repeat_quest_level[receive], 2);

	me->add("combat_exp", quest_exp);
	me->add("potential", quest_pot);
	me->delete ("repeat");
	//ȥ��ԭ�ȶ��������

	//�������������Ϣ
	quest_give = me->query("quest_give/number");
	quest_give -= ({receive});
	if (sizeof(quest_give))
		me->set("quest_give/number", quest_give);
	else
		me->delete ("quest_give/number");

	tell_object(me, popup(sprintf("��ϲ�������%s�����񣬻�����½���\n���飺%d\n��Ǳ�ܣ�%d\n,���������Ŷ��", repeat_quest_name[receive], quest_exp, quest_pot)));
	return 1;
}
// int help(object me)
// {
// 	write( @HELP
// �����ͨ����ָ����ȡһ���������

// HELP );
// 	return 1;
// }
