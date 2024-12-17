inherit NPC;
#include <localtime.h>

string ask_zhengrong();
string ask_bianxing();
void create()
{
	set_name("������ҽ", ({"shenyi"}));
	set("long", "������һ������Ķ����㣡");
	set("combat_exp", 10000);
	
	set("inquiry", ([
		"�����ݡ�" : (: ask_zhengrong :),
		"�����ԡ�" : (: ask_bianxing :),
		]));
	setup();
}

void init()
{
	add_action("do_zhengrong", "zhengrong");
	add_action("do_bianxing", "bianxing");
}

//��װzj����
string popup(string str)
{
string msg;
 msg = ZJOBLONG+str;
 msg = replace_string(msg,"\n",ZJBR);
 return msg+"\n";
}
//��������zj����
string popup_key(string str)
{
 str = ZJOBACTS2+ZJMENUF(2,2,9,30)+str;
return str+"\n";
}
//�������ַ�����ֱ�ӵ���
string popup_input(string str,string order)
{
 return INPUTTXT(str,order+"$txt#")+"\n";
}

string ask_zhengrong()
{
	this_player()->force_me("zhengrong");
	return "";
}

string ask_bianxing()
{
	this_player()->force_me("bianxing");
	return "";
}

int do_bianxing(string arg)
{
	object me = this_player();

	if (!arg)
	{
		string msg;
		msg = popup("�������������Ա�") + popup_key(sprintf("����:%s%sŮ��:%s%s","bianxing ����",ZJSEP,"bianxing Ů��",ZJSEP));
		write(msg);
		return 1;
	}

	if (me->query("shenyi/bianxing"))
	{
		write("���ڿ���Ц�ɣ����Ѿ����������ˣ�����������˵��������Ѿ��������ˣ�������Щ����ҩ�ɣ������ǿ϶������ˣ�\n");
		return 1;
	}

	if (arg != "����" || arg != "Ů��")
	{
		write("����ѡ���������Ա�ȽϺá�\n");
	}

	me->set("gender",arg);
	me->set("shenyi/bianxing",1);

	write("����Ա�ɹ��ı���ҽ�ı����" + arg + "��\n");

	return 1;
}

int do_zhengrong(string arg)
{
	object who = this_player();
	int last_time, num;
	
	
	last_time = who->query("shenyi_zhengrong");
	if ((localtime(last_time)[LT_MON] == localtime(time())[LT_MON]) && (localtime(last_time)[LT_MDAY] == localtime(time())[LT_MDAY]))
	{
		write(ZJOBLONG + "һ��ֻ������һ�Ρ�\n");
		return 1;
	}
	
	if (!arg)
	{
		write(INPUTTXT("һ��һ�Σ�����1��50�����¾��鲻�շѡ�"ZJBR"���뽫��ò�޸�Ϊ���٣�(10-30)", "zhengrong $txt#") + "\n");
		return 1;
	}
	
	if (!sscanf(arg, "%d", num) || num < 10 || num > 30)
	{
		write(ZJOBLONG + "������һ������10��С��30������\n");
		return 1;
	}
	
	if (!MONEY_D->player_pay(who, 10000) && who->query("combat_exp") > 500000)
		return notify_fail(ZJOBLONG + "���Ǯ������\n");
	
	who->set("per", num);
	who->set("shenyi_zhengrong", time());
	write("���ݳɹ��������ò�޸�Ϊ" + num + "��\n");
	return 1;
}