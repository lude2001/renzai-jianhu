inherit NPC;
inherit F_SAVE;

string ask_shilian();
string ask_danchou();

void create()
{
    set_name("评论奖励发放", ({"shizhe"}));
    set("long", query("name") + "那么可爱！你们怎么忍心对" + query("name") + "下手。\n");
    set("gender", "女性");
    set("age",17);
    set("combat_exp", 1);
    restore();
    set("create_time", time()/86400 * 86400);
    
    set("inquiry", ([
            " 【十连】" : (: ask_shilian :),
            " 【单抽】" : (: ask_danchou :),
        ]));

    setup();
}

string query_save_file() { return DATA_DIR + "npc/shizhe"; }

string ask_shilian()
{
	object gift, who = this_player();
	string str;
	mapping shilian = __DIR__"shilian.c"->query_map();

	if (query("lingqu/shilian/" + who->query("id")))
	{
		return "你已经领取了哦。\n";
	}

	if (undefinedp(shilian[who->query("id")]))
	{
		return "你不能领取哦。\n";
	}

	if (!objectp(gift = new("/clone/baiyi/tencard")))
	{
		return "错误，请联系管理员处理。\n";
	}

	set("lingqu/shilian/" + who->query("id"), 1);
	save();
	gift->set_amount(1);
	gift->move(who);

	log_file("pinglun/shilian", ctime(time()) + who->name() + "领取了十连抽卡片。\n");
	return "你获得了一张十连抽卡片。\n";

	return "";
}

string ask_danchou()
{
	object gift, who = this_player();
	string str;
	mapping danchou = __DIR__"danchou.c"->query_map();

	if (query("lingqu/danchou/" + who->query("id")))
	{
		return "你已经领取了哦。\n";
	}

	if (undefinedp(danchou[who->query("id")]))
	{
		return "你不能领取哦。\n";
	}

	if (!objectp(gift = new("/clone/baiyi/onecard")))
	{
		return "错误，请联系管理员处理。\n";
	}

	set("lingqu/danchou/" + who->query("id"), 1);
	save();
	gift->set_amount(1);
	gift->move(who);

	log_file("pinglun/danchou", ctime(time()) + who->name() + "领取了单抽卡片。\n");
	return "你获得了一张单抽卡片。\n";

	return "";
}

void die()
{
	object ob, me, who;
	
	me = this_object();
	who = me->query_last_damage_from();
	ob = new(base_name(me));
	ob->set("create_time", query("create_time"));
	ob->move(environment(me));
	tell_object(who, ZJOBLONG + query("name") + "：你这个恶魔，你会受到诅咒的！你再杀会死的！\n");
	log_file("kill_qian", ctime(time()) + "   " + who->name() + "\n");
	
	::die();
}

void init()
{
    add_action("disable", ({ "kill", "hit", "fuhuo", "touxi", "fight", "steal"}));
}

int disable(string arg)
{
    object who = this_player();
    
    if (arg != "qian")
        return 0;
    
    tell_object(who, query("name") + "一脚踢向你，你倒在地上动弹不得。\n");
    who->start_busy(180);

    return 1;
}

int accept_ansuan(object who)
{
    tell_object(who, "你想暗算" + query("name") + "……\n" + query("name") + "：哼，还想暗算我？乖乖在原地罚站吧！\n");
    who->start_busy(300);
    return 0;
}

void fight_ob(object ob)
{
	::fight_ob(ob);
    tell_object(ob, query("name") + "一脚踢向你，你倒在地上动弹不得。\n");
    ob->start_busy(180);
    
}

int accept_fight(object who)
{
	command("say 没兴趣。");
	return 0;
}

void receive_damage(string type, int n)
{
	return;
}

void receive_wound(string type, int n)
{
	return;
}