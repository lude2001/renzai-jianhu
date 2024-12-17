// spy.c
// by ReyGod  in  12/16/1996  in BUPT

#include <ansi.h>

inherit F_CLEAN_UP;
int remote_bonus(object me);

int main(object me, string arg)
{

    
    if (me->query("combat_exp") < 1500000)
    return notify_fail("����С��150�򣬲��ܿ���ɨ����\n");
    
    if (me->query("cxpay/gongxian") < 30)
    return notify_fail("����С��30�޷�ɨ����\n");
    
	if (!arg)
    {
		write(ZJOBLONG"�����ѡ������ɨ��\n"ZJOBACTS2"Ԫ��ɨ��:shimensd yuanbao"ZJSEP"ͨ��ɨ��:shimensd yuan_bao\n");
		return 1;
	}
	else if (arg == "yuanbao" || arg == "yuan_bao")
	{

		if (arg == "yuanbao")
		{
			if (me->query("yuanbao") < 50)
				return notify_fail("Ԫ���������㡣\n");

			me->add("yuanbao",-50);
		}
		else
		{
			if (me->query("yuan_bao") < 50)
			return notify_fail("ͨ���������㡣\n");

			me->add("yuan_bao",-50);
		}

		if ((time() / 86400) > (me->query("shimensd/time") / 86400) && me->query("shimensd/number") >= 1000)
		{
			me->delete("shimensd/number");
		}

		if ((time() / 86400) >= (me->query("shimensd/time") / 86400) && me->query("shimensd/number") >= 1000)
		{
			write("������ʦ��ɨ�������Ѿ��ù��ˡ�\n");
			return 1;
		}
    
        
		me->set("shimensd/time",time());
		me->add("shimensd/number",50);
	}
	else
	{
	    return 1;
	}

	for (int i = 0;i<50;i++)
	{
		remote_bonus(me);
	}

	write("�����Ѿ����ɨ������Ϊ:" + me->query("shimensd/number") + "�Ρ�\n");
	return 1;
}


// Զ�̽���
int remote_bonus(object me)
{
	//mapping q;	      // WHO������
	string msg = "";	     // ����˵����Ϣ
	//object dob;	     // ���ε��˵���
	int bonus;	      // ����(��������1������)
	//int t;		  // ��������ʱ��ı���
	int exp;		// ��õľ���
	int pot;		// ��õ�Ǳ��
	int mar;		// ��õ�ʵս���
	int weiwang;	    // ��õ�����
	int score;	      // ��õĽ�������
	int lvl;		// ����ĵȼ�
	//int quest_level;	// QUEST�ĵȼ�
	int quest_count;	// ����QUEST����Ŀ
	//int timeover;	   // ��־����ʱ�ˣ�
	int added;	      // �������ʱ�������ֵĵ��˻��������
	mixed special = 0;      // �Ƿ������⽱��


	// bonus Ϊ 1 ��ʾ����������Ϊ 2 ��ʾ�۳�һ�롣
	bonus = 1;

	lvl = NPC_D->check_level(me);
	exp = 8 + random(5) + lvl;
	pot = 4 + random(3) + lvl;
	weiwang = 1 + random(3) + lvl / 2;
	score = 1 + random(3) + lvl / 2;
	quest_count = me->query("quest_count") + 1;

	// ����������ɵĴ�����������
	if (quest_count >= 500)
	{
		// ��������˳���500�ε�����
		exp += 80 + random(quest_count / 20 + 1);
		pot += 45 + random(quest_count / 25 + 1);
		mar = 45 + random(20);
		weiwang += 8 + random(20);
		score += 4 + random(15);
	} else
	if (quest_count >= 200)
	{
		// ��������˳���200�ε�����
		exp += 70 + random(quest_count / 20 + 1);
		pot += 40 + random(quest_count / 25 + 1);
		mar = 20 + random(10);
		weiwang += 5 + random(15);
		score += 3 + random(10);
	} else
	if (quest_count >= 100)
	{
		// ��������˳���100�ε�����
		exp += 50 + random(quest_count / 20 + 1);
		pot += 30 + random(quest_count / 25 + 1);
		weiwang += 3 + random(10);
		score += 2 + random(10);
	} else
	if (quest_count >= 10)
	{
		// ��������˳���10�ε�����
		exp += 45 + random(quest_count / 20 + 1);
		pot += 25 + random(quest_count / 25 + 1);
		weiwang += 1 + random(5);
		score += 1 + random(5);
	}
	if (quest_count >= 1000)
	{
		msg += "�벻����������ǧ��������һʧ�֣���������" + me->query("family/family_name") + "��������ӡ�";
		special = "/clone/vip/dan_jiuzhuan1";
		quest_count = 0;
            me->add("quest_circle", 1);
	} else
	if ((quest_count % 50) == 0)
	{
		msg += "���ǲ�������Ȼ����" + chinese_number(quest_count) + "�ζ�û��ʧ�֡�";
	}


	me->set("quest_count", quest_count);

	msg += "\n";
	tell_object(me, msg);
	me->delete("quest");
	if (! bonus) return 1;

	exp /= bonus;
	pot /= bonus;
	mar /= bonus;
	weiwang /= bonus;
	score /= bonus;

	tell_object(me,HIR"���ǵ�" + quest_count + "��ʦ��"NOR"��\n");	// 0.01% to get a special object
	if ((quest_count>0 && (quest_count % 30) == 0)|| special)
	{
		QUEST_D->special_bonus(QUEST_D, me, special);
		tell_object(me,HIR"ʦ����Ʒ����������"NOR"��\n");
	}
	else
	if (random(10000) == 1||me->query("skill_bonus_set"))
	{
		QUEST_D->skill_bonus(QUEST_D, me);
		tell_object(me,HIR"ʦ�ż��ܽ���������"NOR"��\n");
    }
	QUEST_D->bonus(me, ([ "exp" : exp, "pot" : pot, "mar" : mar,
		      "weiwang" : weiwang, "score" : score ]), 1);
	return 1;
}