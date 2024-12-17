// Room: /city/qianzhuang.c
inherit ROOM;
void create()
{
	set("short", "Ǯׯ");
	set("long", @LONG
����һ�����ֺŵ�Ǯׯ�����м��������ʷ����ȫ�����ض��зֵꡣ����
�е���Ʊ�����ǳ��ã�ͨ��ȫ����
    �ڶ����ǽ�Ϲ��˿�����(paizi)��
LONG );
	set("no_fight", 1);
	set("exits", ([



		"east" : __DIR__"beidajie1",
	]));
	set("item_desc", ([
		"�����ӡ�" : "��Ǯׯ�ṩ���·���\n"
		ZJOBACTS2+ZJMENUF(3,3,8,30)"��Ǯ:cun"ZJSEP"ȡǮ:qu"ZJSEP"����:check"ZJSEP"��ׯ���:cunkuan\n",
	]) );
	
	set("action_list", ([
		"Ǳ������":"potential_bank",
		"��ƽ�":"sale buy",
		"���ƽ�":"sale sell",
		]));
	
	set("objects", ([
		__DIR__"npc/qian" : 1
	]));
	setup();
}

void init()
{
	add_action("do_potential_bank", "potential_bank");
	add_action("do_sale", "sale");
}

int do_potential_bank(string arg)
{
	object who = this_player();
	string type;
	int num;
	
	if (!arg)
	{
		write(ZJOBLONG + "��Ҫʹ��ʲô����\n" + ZJOBACTS2+ZJMENUF(3,3,8,30) + "��Ǳ��:potential_bank cun"ZJSEP"ȡǱ��:potential_bank qu"ZJSEP"��ѯ:potential_bank check\n");
		return 1;
	}
	
	if (arg == "cun")
	{
		write(INPUTTXT("��Ŀǰ��" + ((int)who->query("potential") - (int)who->query("learned_points")) + "Ǳ�ܣ���Ҫ�������Ǳ�ܣ�", "potential_bank cun $txt#") + "\n");
		return 1;
	}
	
	if (arg == "qu")
	{
		write(INPUTTXT("��Ŀǰ����" + who->query("potential_bank/amount") + "Ǳ�ܣ���Ҫȡ������Ǳ�ܣ�", "potential_bank qu $txt#") + "\n");
		return 1;
	}
	
	if (arg == "check")
	{
		write(ZJOBLONG + "��Ŀǰ����Ǳ�����е�Ǳ��Ϊ" + who->query("potential_bank/amount") + "��\n");
		return 1;
	}
	
	if (sscanf(arg, "%s %d", type, num) == 2)
	{
		if (type == "cun" && num > 0)
		{
			if (((int)who->query("potential") - (int)who->query("learned_points")) < num)
				return notify_fail(ZJOBLONG + "���Ǳ��û��ô���ˡ�\n");
			if (!MONEY_D->player_pay(who, 1000))
				return notify_fail(ZJOBLONG + "�����Ӳ��㡣\n");
			who->add("potential_bank/amount", num);
			who->add("potential", -num);
			write(ZJOBLONG + "�������" + num + "Ǳ�ܣ�����10��������\n");
			return 1;
		}
		else if (type == "qu" && num > 0)
		{
			if (who->query("potential_bank/amount") < num)
				return notify_fail(ZJOBLONG + "�����Ǳ�����е�Ǳ��û��ô���ˡ�\n");
			if (!MONEY_D->player_pay(who, 1000))
				return notify_fail(ZJOBLONG + "�����Ӳ��㡣\n");
			who->add("potential_bank/amount", -num);
			who->add("potential", num);
			write(ZJOBLONG + "��ȡ����" + num + "Ǳ�ܣ�����10��������\n");
			return 1;
		}
		else
		{
			write("���������0������\n");
			return 0;
		}
	}
	else
	{
		write("�����ʽ�������������롣\n");
		return 0;
	}
}

int do_sale(string arg)
{
object me = this_player();
string type,ob_id;
int amount;
//if (getuid(me)!="baiyi666")
//return 1;

 if (sscanf(arg,"%s %d",type,amount)==2||sscanf(arg,"%s %s",type,ob_id)==2)
 {
 
  
  if (type == "query")
  {
  tell_object(me,SALE_D->query_gold(me,ob_id)+"\n");
  return 1;
  }
  
  if (type == "withdraw")
  {
  tell_object(me,SALE_D->withdraw_gold(me,ob_id)+"\n");
  return 1;
  }
  
  if (type == "buy")
  {
  tell_object(me,SALE_D->buy_gold(me,ob_id)+"\n");
  return 1;
  }
  
 if (type == "sell")
 {
 tell_object(me,SALE_D->sell_gold(me,amount)+"\n");
 return 1;
 }
 
 write("������ȷִ�в���\n");
 return 1;
 
 }
 if (arg == "buy")
  tell_object(me,SALE_D->buy_gold(me)+"\n");
 if (arg == "sell")
 tell_object(me,SALE_D->sell_gold(me)+"\n");
 return 1;
}
