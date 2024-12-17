inherit NPC;

string ask_jiaoyi();
string ask_shangcheng();
string ask_huishou();
string ask_huifu_skill();
void create()
{
	set_name("黑心老人", ({"heixin"}));
	set("long", "他全身隐藏在阴影之下，无法看清。\n");
	set("combat_exp", 100000);
	set("age", 59);
	
	set("inquiry", ([
		"【交易】" : (: ask_jiaoyi :),
		"【恢复技能】" : (: ask_huifu_skill :),
		"【商城】" : (: ask_shangcheng :),
		"【回收】" : (: ask_huishou :),
		]));
	
	setup();
}

void init()
{
	add_action("do_heixin_jiaoyi", "heixin_jiaoyi");
	add_action("do_heixin_shop", "heixin_shop");
}

string ask_shangcheng()
{
	this_player()->force_me("heixin_shop");
	return "";
}


string ask_huishou()
{
	this_player()->force_me("huishou");
	return "";
}

string ask_huifu_skill()
{
	object who = this_player();

	string *skill_list = ({
        "jiuyang-shengong",
        "shenzhaojing",
        "qishang-quan",
        "baihua-quan",
        "hanbing-mianzhang",
        "xuanming-zhang",
        "sougu",
         "zhuihun-jian",
        "yunlong-bian",
        "hanxing-bada",
        "bizhen-qingzhang",
         "huanyin-zhi",
        "ningxue-shenzhao",
        "sanfen-jianshu",
        "zijinbagua-dao",
    });

	foreach (string skill in skill_list)
	{
		if (who->query_skill(skill) && who->query_skill(skill) < 180)
		{
			who->set_skill(skill,180);
		}
	}

	return "你的公共技能已恢复。\n";
}
int do_heixin_shop(string arg)
{
	__DIR__"shop"->main(this_player(), arg);
	return 1;
}

string ask_jiaoyi()
{
	object who = this_player();
	
	if (who->query("yuanbao") < 100)
		return "你的元宝不够。\n";
	else
	{
		write(ZJOBLONG + "你确定要用100元宝和我换500金子？\n" + ZJOBACTS2 + "确定:heixin_jiaoyi y\n");
		return "";
	}
}

int do_heixin_jiaoyi(string arg)
{
	object who = this_player();
	object money;
	
	if(arg != "y")
		return 1;
	
	if(who->query("combat_exp") < 1000000)
	{
	    write("你的经验不够，无法兑换。\n");
		return 1;
	}
	
	if((who->query("heixin_time")/86400) != (time()/86400))
		who->delete("heixin_jiaoyi");
	
	if(who->query("heixin_jiaoyi"))
	{
	    write("你今天已经兑换过了，无法再次兑换。\n");
		return 1;
	}
	
	if (who->query("yuanbao") < 100)
	{
	    write("你的元宝不足。\n");
	    return 1;
	}
	
	if(who->query("heixin_jiaoyi") > 1)
		return 1;
	
	who->add("yuanbao", -100);
	money = new("/clone/money/gold");
	money->set_amount(500);
	money->move(who);
	write("你花费了100元宝兑换了500金子。\n");
	who->set("heixin_jiaoyi", 1);
	who->set("heixin_time", time());
	log_file("pay/duihuan", ctime(time()) + who->short() + "兑换了黄金。\n");
	return 1;
}