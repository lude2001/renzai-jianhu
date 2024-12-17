inherit NPC;

string ask_jiaoyi();
string ask_shangcheng();
string ask_huishou();
string ask_huifu_skill();
void create()
{
	set_name("��������", ({"heixin"}));
	set("long", "��ȫ����������Ӱ֮�£��޷����塣\n");
	set("combat_exp", 100000);
	set("age", 59);
	
	set("inquiry", ([
		"�����ס�" : (: ask_jiaoyi :),
		"���ָ����ܡ�" : (: ask_huifu_skill :),
		"���̳ǡ�" : (: ask_shangcheng :),
		"�����ա�" : (: ask_huishou :),
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

	return "��Ĺ��������ѻָ���\n";
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
		return "���Ԫ��������\n";
	else
	{
		write(ZJOBLONG + "��ȷ��Ҫ��100Ԫ�����һ�500���ӣ�\n" + ZJOBACTS2 + "ȷ��:heixin_jiaoyi y\n");
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
	    write("��ľ��鲻�����޷��һ���\n");
		return 1;
	}
	
	if((who->query("heixin_time")/86400) != (time()/86400))
		who->delete("heixin_jiaoyi");
	
	if(who->query("heixin_jiaoyi"))
	{
	    write("������Ѿ��һ����ˣ��޷��ٴζһ���\n");
		return 1;
	}
	
	if (who->query("yuanbao") < 100)
	{
	    write("���Ԫ�����㡣\n");
	    return 1;
	}
	
	if(who->query("heixin_jiaoyi") > 1)
		return 1;
	
	who->add("yuanbao", -100);
	money = new("/clone/money/gold");
	money->set_amount(500);
	money->move(who);
	write("�㻨����100Ԫ���һ���500���ӡ�\n");
	who->set("heixin_jiaoyi", 1);
	who->set("heixin_time", time());
	log_file("pay/duihuan", ctime(time()) + who->short() + "�һ��˻ƽ�\n");
	return 1;
}