// Room: /city/beidajie2.c

#define YIJING_D "/adm/daemons/yijingd"

inherit ROOM;
int start_set(string arg);
string set_color(string arg);
int yijing_number(object me);
int same_yijing_number(object me, string type);
int yijing_expend(object me, string yijingName, int self);
int judge_requirement(object me, string type, string yijingName);
int set_yijing_desc(object me, string yijingName, string attackDesc, string dodgeDesc, string msg);
int set_yijing_skill_expend(object me, string yijingName, string type, int expend, string skillType);
int guizhen();
int inform_all(object me);

mapping yj_f_name = (["unarmed":"����", //����ȭ��
						 "cuff":"ȭ��", //����ȭ��
					   "strike":"����", //�����Ʒ�
					   "finger":"ָ��", //����ָ��
						 "hand":"�־�", //�����ַ�
						 "claw":"צ��", //����צ��
						"sword":"����", //��������
						"blade":"����", //��������
						"staff":"�Ⱦ�", //�����ȷ�
					   "hammer":"����", //��������
						 "club":"����", //��������
						 "whip":"����", //�����޷�
					 "throwing":"����"	//��������
]);

int inform_all(object me)
{
	string msg;
	int number;
	string *colorList = ({ HIR,HIG,HIY, HIB,HIM,HIC, HIW});

	this_object()->add("yj_lw/number", 1);
	number = this_object()->query("yj_lw/number");

	msg =  colorList[random(sizeof(colorList))] + "���⾳֮�ۡ�--- ";

	if (me->query("family/family_name"))
	{
		switch (number)
		{
		case 1:
			msg += "�����������ƶ���.......";
			break;
		case 2:
			msg += CHINESE_D->chinese_date(time(), 1);
			break;
		case 3:
			msg += me->query("family/family_name") + "�������������ڣ�����չ��ҵĵ�����Ȼ�˹�����������á�";
			break;
		case 4:
			msg += me->query("family/master_name") + "���������������������ڵ��ӣ������˳����ã������ų�̧ͷң���⾳֮�۴���";
			break;
		case 5:
			msg += "�ڴ�ͬʱ�����������޲�������֮�����׹�������������������";
			break;
		case 6:
			msg += "����֮��߷崦��һ����Ӱ�ڲ������������ѧ��ϸϸ��֮����Ȼ�����¼������������" + me->query("name") + "����ù����䳤Х��������֮:��" + me->query("name") + "��������" + me->query("age") + "֮�䣬���⾳֮������" + me->query_temp("yj_set/name") + yj_f_name[me->query_temp("yj_set/type")] + ",�ڴ�ɽ��ʯ�������⾳������������������ͬ������֮��";
			break;
		case 7:
			msg += me->query("family/family_name") + "���ڣ���ң�ɸ���������ܸߺ�:��" + me->query("name") + "ʦ�ֵ�������⣬�������£�";
			break;
		case 8:
			msg += me->query("family/master_name") + "��:��ͽ......" + me->query("name") + "������" + CHINESE_D->chinese_date(me->query("family/enter_time"), 1) + "֮ʱ����" + me->query("family/family_name") + "���£��벻����������֮�꾹�ܼ������������⣬����ο�ԡ�";
			break;
		case 9:
			msg += "������ܣ����£�����������⣬��Ȼ�������⣬��ͬ����󺣣���Ҳ������ˣ�";
			break;
		case 10:
			msg += "��Ħ����" + me->query("name") + ",������������λС��֮�����׹߶�������һ���������Ǵ�о�̾��������Ϊ�������";
			break;
		case 11:
			msg += "������:��ʮ�겻����������ˣ�����������˫..........";
			break;
		default:
			this_object()->delete("yj_lw");
			if (!this_object()->query("yj_lw/number"))
			{
		
			message("channel:chat", sprintf(HIY"���⾳֮�ۡ�%s��%d��֮�䣬��%s���⾳֮��������%s%s��
			���������������������У���һλ����֮�����������һ;�����⣬����֮����������������
			�ݷ�Ҳ�ھ�̾�ⲻ��˼���һ��"NOR"��",me->query("name"),me->query("age"),CHINESE_D->chinese_date(time(),1),me->query_temp("yj_set/name"),yj_f_name[me->query_temp("yj_set/type")]),users());
			remove_call_out("inform_all");
			}
			return 1;
		}
	}

	message("story", msg + NOR "\n", users());
	call_out("inform_all",5,me);
	return 1;
}

void create()
{
	set("short", "�⾳֮��");
	set("long", "�������⾳֮�ۣ��Թ����������������֮���޵���Ŷ��ڴ˴����������Լ��Ĵ�˵��");
	set("outdoors", "city");
	set("item_desc", (["��ʯ����":"����һ��ʯ�����̺�������⾳�İ��ء�\n" ZJOBACTS2 "�鿴:setyj"ZJSEP"����:gz\n",
	]));
	// set("exits", (["south":__DIR__ "enter",
	// ]));
	// set("out_room", "/d/city/wumiao");
	setup();
}


void init()
{
	add_action("start_set", "setyj");
	add_action("start_wu", "startwu");
	add_action("guizhen", "gz");
}

// �趨�⾳���� �������� �������� �⾳�������� �⾳����
int start_set(string arg)
{
	object me = this_player();

	mixed setType, setMsg;
	if (!arg)
	{
		string msg;
		msg = ZJOBLONG "���趨���⾳��Ϣ\n";
		msg += "�⾳����:" + (me->query_temp("yj_set/name") ? me->query_temp("yj_set/name") : "��") + "\n";
		msg += "�⾳��������:" + (me->query_temp("yj_set/msg") ? me->query_temp("yj_set/msg") : "��") + "\n";
		msg += "�⾳��������:" + (me->query_temp("yj_set/attack_desc") ? me->query_temp("yj_set/attack_desc") : "��") + "\n";
		msg += "�⾳��������:" + (me->query_temp("yj_set/dodge_desc") ? me->query_temp("yj_set/dodge_desc") : "��") + "\n";
		msg += "�⾳���ĵȼ�:" + (me->query_temp("yj_set/expend") ? me->query_temp("yj_set/expend") : "��") + "\n";
		msg += "��������:" + (me->query_temp("yj_set/skill") ? me->query_temp("yj_set/skill") : "��") + "\n";
		msg += "�⾳����:" + (me->query_temp("yj_set/type") ? yj_f_name[me->query_temp("yj_set/type")] : "��") + "\n";

		msg = replace_string(msg, "\n", ZJBR);
		msg += "\n" ZJOBACTS2;
		msg += "�趨����:setyj set name" ZJSEP;
		msg += "�趨��������:setyj set attack_desc" ZJSEP;
		msg += "�趨��������:setyj set dodge_desc" ZJSEP;
		msg += "�趨��������:setyj set msg" ZJSEP;
		msg += "�趨����:setyj set expend" ZJSEP;
		msg += "�趨��������:setyj set skill" ZJSEP;
		msg += "�趨�⾳����:setyj set type" ZJSEP;
		msg += "��ʼ�����⾳:startwu\n";
		tell_object(me, msg);
		return 1;
	}

	if (sscanf(arg, "%s %s", setType, setMsg) == 2)
	{
		string msg;
		string *s1 = ({
			"unarmed", //����ȭ��
			"cuff",	   //����ȭ��
			"strike",  //�����Ʒ�
			"finger",  //����ָ��
			"hand",	   //�����ַ�
			"claw",	   //����צ��
			"sword",   //��������
			"blade",   //��������
			"staff",   //�����ɷ�
			"hammer",  //��������
			"club",	   //��������
			"whip",	   //�����޷�
		});

		setMsg = replace_string(setMsg, " ", "");
		setMsg = replace_string(setMsg, "\"", "`");
		setMsg = replace_string(setMsg, "\\n", ZJBR);
		setMsg = replace_string(setMsg, "\n", ZJBR);
		setMsg = replace_string(setMsg, "$n", "");

		if (setType == "set")
		{
			if (setMsg == "name")
			{
				msg = "���趨����⾳���ƣ������趨����Ϊ���죬����Ϊ�������վ��ǲ��콣�⡣";
				msg = INPUTTXT(msg, "setyj name $txt#") + "\n";
				tell_object(me, msg);
				return 1;
			}

			if (setMsg == "attack_desc")
			{
				msg = "���趨��Ĺ�������,����ʹ����ɫ�ַ������� $HIR$Ϊ��ɫ��$target_name$����з������֣�$my_name$�����Լ������֣�����Ǳ������͵��⾳,$weapon_name$�����Լ����������֡�,Ӣ��б��+n������";
				msg = INPUTTXT(msg, "setyj attack_desc $txt#") + "\n";
				tell_object(me, msg);
				return 1;
			}

			if (setMsg == "dodge_desc")
			{
				msg = "���趨��Ķ�������,����ʹ����ɫ�ַ������� $HIR$Ϊ��ɫ��$target_name$����з������֣�$my_name$�����Լ������֡�,Ӣ��б��+n������";
				msg = INPUTTXT(msg, "setyj dodge_desc $txt#") + "\n";
				tell_object(me, msg);
				return 1;
			}

			if (setMsg == "msg")
			{
				msg = "���趨����⾳��������,����ʹ����ɫ�ַ������� $HIR$Ϊ��ɫ������������趨������Դ��������е���Ϣ��Ӣ��б��+n������";
				msg = INPUTTXT(msg, "setyj msg $txt#") + "\n";
				tell_object(me, msg);
				return 1;
			}

			if (setMsg == "expend")
			{
				msg = "���趨������ĵȼ���6 - 18����Ӧ600-1800���������ģ�6-18���cd���⾳�����Զ������ģ�������cd�����Ÿ����Ĵ��۲�ͬ��������ɵ�Ч����ͬ����Ϊ�������ͣ����У�6 -18���������˺�����Ч�ȼ� *��6 - 18�� / 4�� ����ָ�����Ч�ȼ� * ��6 - 18�� / 8����Ѫ���ٻָ����ֵһ��ľ��񣬼� / 4���� ";
				msg = INPUTTXT(msg, "setyj expend $txt#") + "\n";
				tell_object(me, msg);
				return 1;
			}

			if (setMsg == "type")
			{

				msg = ZJOBLONG "���趨����⾳���͡�\n" ZJOBACTS2;

				foreach (string skill_id in s1)
				{
					msg += replace_string(to_chinese(skill_id), "����", "") + ":setyj type " + skill_id + ZJSEP;
				}

				msg += "����:setyj\n";

				tell_object(me, msg);
				return 1;
			}

			if (setMsg == "skill")
			{

				msg = ZJOBLONG "���趨��ļ������͡���ע�⣬�⾳���о������ˣ�����pvp�Ƚ�ǿ�ƣ�������ȽϾ��⣬ʹ���⾳����������pve�����⾳����ǿ����һ���ǳ��޴�����Ϊ������������ѡ���⾳���ܡ�\n" ZJOBACTS2;

				msg += "����:setyj skill ����" ZJSEP;
				msg += "�����˺�:setyj skill �����˺�" ZJSEP;
				msg += "���лָ�:setyj skill ���лָ�" ZJSEP;

				msg += "����:setyj\n";

				tell_object(me, msg);
				return 1;
			}

			return 1;
		}

		if (setType == "name")
		{
			if ((strlen(setMsg) < 2) || (strlen(setMsg) > 4))
			{
				tell_object(me, "�Բ�������⾳���Ʋ���̫����̫�̡�\n");
				return 1;
			}

			if (!is_chinese(setMsg))
			{
				tell_object(me, "�Բ��������á����ġ�ȡ�⾳���ơ�\n");
				return 1;
			}

			if (!me->query_temp("yj_set/type"))
			{
				tell_object(me, "����Ҫ��ѡ���⾳���Ͳ����趨�⾳���ơ�\n");
				return 1;
			}

			if (YIJING_D->check_yj_name_is_repetition(setMsg, me->query_temp("yj_set/type")))
			{
				tell_object(me, "�Բ����⾳֮���Ѿ�������⾳�����ˣ���ͬ���ͣ���ͬ���Ʋ����ظ������ǲ�ͬ���ͣ���ͬ���ƿ����趨 ��������콣��Ͳ��쵶����ǲ�ͬ��������ͬ���ƣ������趨�����㲻��ʹ�úͱ���һ�����⾳���ơ�\n");
				return 1;
			}

			me->set_temp("yj_set/name", setMsg);
			tell_object(me, sprintf("���趨%sΪ����⾳���ơ�\n", setMsg));

			return 1;
		}

		if (setType == "attack_desc")
		{
			if ((strlen(setMsg) < 2) || (strlen(setMsg) > 400))
			{
				tell_object(me, "�Բ�������⾳��������̫����̫�̣�1-200�֣���\n");
				return 1;
			}

			setMsg = set_color(setMsg);

			me->set_temp("yj_set/attack_desc", setMsg);
			tell_object(me, sprintf("���趨��%sΪ����⾳����������\n", setMsg));
			return 1;
		}

		if (setType == "dodge_desc")
		{
			if ((strlen(setMsg) < 2) || (strlen(setMsg) > 400))
			{
				tell_object(me, "�Բ�������⾳��������̫����̫�̣�1-200�֣���\n");
				return 1;
			}

			setMsg = set_color(setMsg);

			me->set_temp("yj_set/dodge_desc", setMsg);
			tell_object(me, sprintf("���趨��%sΪ����⾳����������\n", setMsg));
			return 1;
		}

		if (setType == "msg")
		{
			if ((strlen(setMsg) < 2) || (strlen(setMsg) > 600))
			{
				tell_object(me, "�Բ�������⾳��������̫����̫�̣�1-300�֣���\n");
				return 1;
			}

			setMsg = set_color(setMsg);

			me->set_temp("yj_set/msg", setMsg);
			tell_object(me, sprintf("���趨��%sΪ����⾳����������\n", setMsg));
			return 1;
		}

		if (setType == "type")
		{

			if (member_array(setMsg, s1) == -1)
			{
				tell_object(me, "û���������͵����տ������������⾳��\n");
				return 1;
			}

			me->set_temp("yj_set/type", setMsg);
			tell_object(me, sprintf("�������%sΪ��չ�����и����͵���ѧ�������⾳��", to_chinese(setMsg)));
			return 1;
		}

		if (setType == "skill")
		{
			string *skillTypeList = ({"����", "�����˺�", "���лָ�"});

			if (member_array(setMsg, skillTypeList) == -1)
			{
				tell_object(me, "û���������͵��⾳���ܿ������������⾳��\n");
				return 1;
			}

			me->set_temp("yj_set/skill", setMsg);
			tell_object(me, sprintf("�������%sΪ���⾳�ļ������͡�", to_chinese(setMsg)));
			return 1;
		}

		if (setType == "expend")
		{

			setMsg = to_int(setMsg);

			if (setMsg < 6 || setMsg > 18)
			{
				tell_object(me, "�⾳���ĵȼ��ķ�ΧΪ6-18���벻Ҫ�������ĵȼ��ķ�Χ��\n");
				return 1;
			}

			me->set_temp("yj_set/expend", setMsg);

			tell_object(me, sprintf("���趨���⾳���ĵȼ�Ϊ%d��\n", setMsg));
			return 1;
		}
	}
	else
	{
		tell_object(me, "��ʽ����ȷ���޷�ʹ�����ָ�ʽ��\n");
		return 1;
	}

	return 1;
}

int start_wu()
{
	object me = this_player();

	if (this_object()->query("yj_lw"))
		return notify_fail("�����֮������ɽ�����������⾳���㻹���ٵȵȰɣ�\n");

	if (!me->query_temp("yj_set/name") || !me->query_temp("yj_set/attack_desc") || !me->query_temp("yj_set/msg") || !me->query_temp("yj_set/dodge_desc") || !me->query_temp("yj_set/type") || !me->query_temp("yj_set/expend") || !me->query_temp("yj_set/skill"))
		return notify_fail("����⾳��Ϣ���������������ƣ���������,���������������������⾳���ͣ��⾳����,�������͡�\n");

	if (!judge_requirement(me, me->query_temp("yj_set/type"), me->query_temp("yj_set/name")))
		return 1;

	if (!yijing_expend(me, me->query_temp("yj_set/name"), 1))
		return 1;

	set_yijing_desc(me, me->query_temp("yj_set/name"), me->query_temp("yj_set/attack_desc"), me->query_temp("yj_set/dodge_desc"), me->query_temp("yj_set/msg"));
	set_yijing_skill_expend(me, me->query_temp("yj_set/name"), me->query_temp("yj_set/type"), me->query_temp("yj_set/expend"), me->query_temp("yj_set/skill"));

	me->set("yijing/" + me->query_temp("yj_set/name") + "/time", time());
	me->set("yijing/" + me->query_temp("yj_set/name") + "/family", me->query("family"));
	me->set("yijing/" + me->query_temp("yj_set/name") + "/age", me->query("age"));

	//ÿ��������Ҫ��¼һ�¼ӳɵĵȼ�
	me->add("yijing/skill_add/" + me->query_temp("yj_set/type"), 100);
	YIJING_D->set_data(me);
	inform_all(me);

	log_file("guizhen", ctime(time()) + sprintf("%s������%s%s,һ����%d���⾳��",me->query("name"),me->query_temp("yj_set/name"),yj_f_name[me->query_temp("yj_set/type")],yijing_number(me)));
	return 1;
}

string set_color(string arg)
{
	arg = replace_string(arg, "$BLK$", BLK);
	arg = replace_string(arg, "$RED$", RED);
	arg = replace_string(arg, "$GRN$", GRN);
	arg = replace_string(arg, "$YEL$", YEL);
	arg = replace_string(arg, "$BLU$", BLU);
	arg = replace_string(arg, "$MAG$", MAG);
	arg = replace_string(arg, "$CYN$", CYN);
	arg = replace_string(arg, "$WHT$", WHT);
	arg = replace_string(arg, "$HIR$", HIR);
	arg = replace_string(arg, "$HIG$", HIG);
	arg = replace_string(arg, "$HIY$", HIY);
	arg = replace_string(arg, "$HIB$", HIB);
	arg = replace_string(arg, "$HIM$", HIM);
	arg = replace_string(arg, "$HIC$", HIC);
	arg = replace_string(arg, "$HIW$", HIW);
	arg = replace_string(arg, "$NOR$", NOR);

	return arg;
}

//���ڼ��������⾳������
int yijing_number(object me)
{
	if (!me->query("yijing_list"))
		return 0;

	return sizeof(keys(me->query("yijing_list")));
}

//���ڼ�����ͬ���͵��⾳������
int same_yijing_number(object me, string type)
{
	string *yijingList;
	int number = 0;

	if (!me->query("yijing_list"))
		return 0;

	yijingList = keys(me->query("yijing_list"));

	foreach (string yijingName in yijingList)
	{
		if (me->query("yijing/" + yijingName + "/type"))
		{
			number++;
		}
	}

	return number;
}

// ���ڼ����⾳������
// ����Ĳ�����self���������������������������˵ģ�1������������
// 2�����������ˣ���Ȼ�ģ��������˵��⾳�����Ǽ���ģ���Ȼ���еļ��㹫ʽӦ���ڷ������ڲ����д���һ����������һ�����顣
// ����ֵΪ1�ɹ�������Ϊ0�����ʧ�ܣ����ô˷�����ʱ����Ҫ�жϷ���ֵ��
int yijing_expend(object me, string yijingName, int self)
{
	int expendPotential, expendNeili;
	int level, possessPotential;

	level = yijing_number(me);
	expendNeili = 3000 * (level + 1) * (level + 1);

	expendPotential = 4000000 * (level + 1) * (level + 1);
	possessPotential = me->query("potential") - me->query("learned_points");

	//�������˵��⾳���ļ���
	if (self == 2)
	{
		expendNeili /= 2;
		expendPotential /= 2;
	}

	if (me->query("max_neili") < expendNeili)
	{
		tell_object(me, "��������������" + expendNeili + ",�����Ȳ������������\n");
		return 0;
	}

	if (possessPotential < expendPotential)
	{
		tell_object(me, "���Ǳ�ܲ���" + expendPotential + ",���Ȳ���Ǳ�ܡ�\n");
		return 0;
	}

	me->add("potential", -expendPotential);
	me->add("max_neili", -expendNeili);

	if (self == 2)
		me->set("yijing/" + yijingName + "/self", 1); //����������⾳���Լ������

	return 1;
}

// ����ֵΪ1�������󣬷���ֵΪ0����������
int judge_requirement(object me, string type, string yijingName)
{
	int basicForce, baisicDodge, basicParry, basicType;
	int specialForce, specialDodge, specialParry, specialType;
	int level, needLevel;

	basicForce = me->query_skill("force", 1);
	baisicDodge = me->query_skill("dodge", 1);
	basicParry = me->query_skill("parry", 1);
	basicType = me->query_skill(type, 1);

	specialForce = me->query_skill(me->query_skill_mapped("force"), 1);
	specialDodge = me->query_skill(me->query_skill_mapped("dodge"), 1);
	specialParry = me->query_skill(me->query_skill_mapped("parry"), 1);
	specialType = me->query_skill(me->query_skill_mapped(type), 1);

	level = yijing_number(me);

	needLevel = 650 + level * level * 100;

	if (!specialForce || !specialDodge || !specialParry || !specialType)
	{
		tell_object(me, "���Ƚ�����Ҫ���⼼�ܼ����ٽ��������⾳��\n");
		return 0;
	}

	if (me->query("myspecial/b" + type + "level") + 1 < same_yijing_number(me, type))
	{
		tell_object(me, "����츳�ȼ��������������������֮����⾳��\n");
		return 0;
	}

	if (me->query_skill("martial-cognize") < 500)
	{
		tell_object(me, "�����ѧ�����ȼ����������������⾳��\n");
		return 0;
	}

	if (basicForce < needLevel)
	{
		tell_object(me, sprintf("%s��Ϊ(����%d)����,����ǿ�������⾳��\n", to_chinese("force"), needLevel));
		return 0;
	}

	if (baisicDodge < needLevel)
	{
		tell_object(me, sprintf("%s��Ϊ(����%d)����,����ǿ�������⾳��\n", to_chinese("dodge"), needLevel));
		return 0;
	}

	if (basicParry < needLevel)
	{
		tell_object(me, sprintf("%s��Ϊ(����%d)����,����ǿ�������⾳��\n", to_chinese("parry"), needLevel));
		return 0;
	}

	if (basicType < needLevel)
	{
		tell_object(me, sprintf("%s��Ϊ(����%d)����,����ǿ�������⾳��\n", to_chinese(type), needLevel));
		return 0;
	}

	if (specialForce < needLevel)
	{
		tell_object(me, sprintf("%s��Ϊ(����%d)����,����ǿ�������⾳��\n", to_chinese(me->query_skill_mapped("force")), needLevel));
		return 0;
	}

	if (specialDodge < needLevel)
	{
		tell_object(me, sprintf("%s��Ϊ(����%d)����,����ǿ�������⾳��\n", to_chinese(me->query_skill_mapped("dodge")), needLevel));
		return 0;
	}

	if (specialParry < needLevel)
	{
		tell_object(me, sprintf("%s��Ϊ(����%d)����,����ǿ�������⾳��\n", to_chinese(me->query_skill_mapped("parry")), needLevel));
		return 0;
	}

	if (specialType < needLevel)
	{
		tell_object(me, sprintf("%s��Ϊ(����%d)����,����ǿ�������⾳��\n", to_chinese(me->query_skill_mapped(type)), needLevel));
		return 0;
	}

	return 1;
}

// �����趨һ���⾳�Ĺ��������Լ�����������
int set_yijing_desc(object me, string yijingName, string attackDesc, string dodgeDesc, string msg)
{
	me->set("yijing_list/" + yijingName, 1); //�����⾳�б���
	me->set("yijing/" + yijingName + "/attack_desc", attackDesc);
	me->set("yijing/" + yijingName + "/dodge_desc", dodgeDesc);
	me->set("yijing/" + yijingName + "/msg", msg);
	return 1;
}

// type ������ѡ����⾳���ͣ�expendΪ 6- 18. ��Ӧcd:(6 -18) /2 �룬�������� 150 * ��6 - 18��
int set_yijing_skill_expend(object me, string yijingName, string type, int expend, string skillType)
{
	me->set("yijing/" + yijingName + "/type", type);
	me->set("yijing/" + yijingName + "/expend", expend);
	me->set("yijing/" + yijingName + "/skill", skillType);
	return 1;
}

int guizhen()
{
	object me = this_player();

	int guizhenNumber;

	guizhenNumber = me->query("guizhen/number");

	if (guizhenNumber >= yijing_number(me))
	{
		tell_object(me, sprintf("һ���⾳��Ӧһ�ι��棬��Ŀǰ��%d���⾳��������%d�ι��档\n", yijing_number(me), guizhenNumber));
		return 0;
	}

	me->add("guizhen/number", 1);
	me->set("guizhen/" + me->query("guizhen/number") + "/time", time()); //��¼ÿһ�ι����ʱ�����
	me->add("yijing/other_add/qi", 10000 * me->query("guizhen/number")); //ÿ�ζ����������1w * �����������Ѫ��
	me->add("tianfu_point",10);

	CHAR_D->setup_char(me);
	if (me->query("family/master_name"))
	message("channel:chat", HIG"��"+ me->query("family/family_name") + "��:"+ me->query("family/master_name") + "����ͽ" +  me->query("name") + "����������ѹ��棬�Ҽ������뺣�������\n",users());
	message("channel:chat", HIG"���⾳֮�ۡ�:" + me->query("name") + "����˵�" + me->query("guizhen/number") + "���⾳���档\n",users());
	tell_object(me,sprintf("������˵�%d�ι���,����10000��Ѫ���������10��ɷ����츳��,�����������Ϣ����������ѡ��һ�����ɰ�ʦ��\n",me->query("guizhen/number")));
	me->delete("family");
	log_file("guizhen", ctime(time()) + sprintf("---%s(%s)�����˵�%d�ι��档\n", me->query("name"), me->query("id"), me->query("guizhen/number")));
	return 1;
}