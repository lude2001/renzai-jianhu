inherit NPC;

void create()
{
    set_name("���ָ���", ({"gao shou"}));
    set("long", "���ָ���\n");
    
	set("gender", "����");
	set("age", 35);
	set("shen_type", 1);
	set("str", 50);
	set("int", 50);
	set("con", 50);
	set("dex", 50);
	
	set("qi", 200000);
	set("max_qi", 200000);
	set("jing", 200000);
	set("max_jing", 200000);
	set("neili", 200000);
	set("max_neili", 200000);
	set("no_get", 1);
	set("jiali", 300);

	set("combat_exp", 2750000);
	set("score", 200000);

	set_skill("cuff", 400);
	set_skill("force", 400);
	set_skill("blade", 400);
	set_skill("dodge", 400);
	set_skill("parry", 400);
	set_skill("sword", 400);
	set_skill("strike", 400);
	set_skill("huashan-xinfa", 400);
	set_skill("zixia-shengong", 400);
	set_skill("poyu-quan", 400);
	set_skill("fanliangyi-dao", 400);
	set_skill("huashan-sword", 400);
	set_skill("hunyuan-zhang", 400);
	set_skill("lonely-sword", 400);
	set_skill("feiyan-huixiang", 400);
	set_skill("martial-cognize", 400);
	set_skill("sword-cognize", 400);
	set_skill("literate", 400);

	map_skill("cuff", "poyu-quan");
	map_skill("force", "zixia-shengong");
	map_skill("dodge", "feiyan-huixiang");
	map_skill("parry", "lonely-sword");
	map_skill("sword", "lonely-sword");
	map_skill("blade", "fanliangyi-dao");
	map_skill("strike", "hunyuan-zhang");

	prepare_skill("cuff", "poyu-quan");
	prepare_skill("strike", "hunyuan-zhang");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "sword.po" :),
		(: perform_action, "cuff.leidong" :),
		(: perform_action, "cuff.poshi" :),
		(: perform_action, "cuff.feng" :),
		(: exert_function, "recover" :),
		(: exert_function, "powerup" :),
	}));

	set_temp("apply/attack", 220);
	set_temp("apply/defense", 220);
	set_temp("apply/damage", 200);
	set_temp("apply/unarmed_damage", 200);

	setup();
	carry_object("/clone/misc/cloth")->wear();
	carry_object("/clone/weapon/changjian")->wield();

	if (clonep())
	{
		set("chat_chance", 50);
		set("chat_msg", ({
			(: NPC_D->random_move(this_object()) :),
		}));
		keep_heart_beat();
	}
}


void init()
{
    object * beichou;
    
    if (sizeof(beichou = filter_array(all_inventory(environment(this_object())), (: ($1)->is_beichou() :))))
    {
        if (objectp(beichou[0]))
            kill_ob(beichou[0]);
    }
}

int is_dutu()    {return 1;}

void die()
{
    object who = this_object()->query_last_damage_from();
    int random = random(100);
    object gift;
    
    if (random < 39)
    {
        gift = new("/clone/gift/putao");
        tell_object(who, "������һ�����ѡ�\n");
        if (objectp(gift))
            gift->move(who);
    }
    else if (random > 39)
    {
        gift = new(__DIR__"cgod_eyes");
        tell_object(who, "������һ���ϵ�֮����Ƭ��\n");
        if (objectp(gift))
            gift->move(who);
    }
    else if (random == 39)
    {
        gift = new("/clone/baoshi/god_eyes");
        tell_object(who, "������һ���ϵ�֮�ۡ�\n");
        message("channel:chat", "���������桿��ϲ" + who->query("name") + "(" + who->query("id") + ")��ɱ���ָ��ֻ���ϵ�֮�ۡ�\n", users());
        log_file("dutu_beichou", ctime(time()) + who->query("name") + "(" + who->query("id") + ")��ɱ���ָ��ֻ���ϵ�֮�ۡ�\n");
        if (objectp(gift))
            gift->move(who);
    }
    
    ::die();
}