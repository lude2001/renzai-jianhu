// Room: /city/qianzhuang.c
inherit ROOM;
void create()
{
	set("short", "钱庄");
	set("long", @LONG
这是一家老字号的钱庄，已有几百年的历史，在全国各地都有分店。它发
行的银票信誉非常好，通行全国。
    在对面的墙上挂了块牌子(paizi)。
LONG );
	set("no_fight", 1);
	set("exits", ([



		"east" : __DIR__"beidajie1",
	]));
	set("item_desc", ([
		"【牌子】" : "本钱庄提供以下服务：\n"
		ZJOBACTS2+ZJMENUF(3,3,8,30)"存钱:cun"ZJSEP"取钱:qu"ZJSEP"查账:check"ZJSEP"本庄存款:cunkuan\n",
	]) );
	
	set("action_list", ([
		"潜能银行":"potential_bank",
		"买黄金":"sale buy",
		"卖黄金":"sale sell",
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
		write(ZJOBLONG + "你要使用什么服务？\n" + ZJOBACTS2+ZJMENUF(3,3,8,30) + "存潜能:potential_bank cun"ZJSEP"取潜能:potential_bank qu"ZJSEP"查询:potential_bank check\n");
		return 1;
	}
	
	if (arg == "cun")
	{
		write(INPUTTXT("你目前有" + ((int)who->query("potential") - (int)who->query("learned_points")) + "潜能，你要存入多少潜能？", "potential_bank cun $txt#") + "\n");
		return 1;
	}
	
	if (arg == "qu")
	{
		write(INPUTTXT("你目前存有" + who->query("potential_bank/amount") + "潜能，你要取出多少潜能？", "potential_bank qu $txt#") + "\n");
		return 1;
	}
	
	if (arg == "check")
	{
		write(ZJOBLONG + "你目前存在潜能银行的潜能为" + who->query("potential_bank/amount") + "。\n");
		return 1;
	}
	
	if (sscanf(arg, "%s %d", type, num) == 2)
	{
		if (type == "cun" && num > 0)
		{
			if (((int)who->query("potential") - (int)who->query("learned_points")) < num)
				return notify_fail(ZJOBLONG + "你的潜能没那么多了。\n");
			if (!MONEY_D->player_pay(who, 1000))
				return notify_fail(ZJOBLONG + "你银子不足。\n");
			who->add("potential_bank/amount", num);
			who->add("potential", -num);
			write(ZJOBLONG + "你存入了" + num + "潜能，花费10两白银。\n");
			return 1;
		}
		else if (type == "qu" && num > 0)
		{
			if (who->query("potential_bank/amount") < num)
				return notify_fail(ZJOBLONG + "你存在潜能银行的潜能没那么多了。\n");
			if (!MONEY_D->player_pay(who, 1000))
				return notify_fail(ZJOBLONG + "你银子不足。\n");
			who->add("potential_bank/amount", -num);
			who->add("potential", num);
			write(ZJOBLONG + "你取出了" + num + "潜能，花费10两白银。\n");
			return 1;
		}
		else
		{
			write("请输入大于0的数。\n");
			return 0;
		}
	}
	else
	{
		write("输入格式错误，请重新输入。\n");
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
 
 write("请你正确执行操作\n");
 return 1;
 
 }
 if (arg == "buy")
  tell_object(me,SALE_D->buy_gold(me)+"\n");
 if (arg == "sell")
 tell_object(me,SALE_D->sell_gold(me)+"\n");
 return 1;
}
