inherit NPC;

int add_skill(int level);

void create()
{
        set_name("霍山", ({ "huo shan", "huo", "shan" }) );
        set("title", HIW "大宗师" NOR);
        set("gender", "男性");
        set("age", 91);
        set("long", "他身着奇装异服，相貌平平，便似一般的西域人士。\n");
        set("attitude", "peaceful");
        set("class", "fighter");
        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);

        set("max_qi", 20000);
        set("max_jing", 20000);
        set("neili", 30000);
        set("max_neili", 30000);
        set("jiali", 100);

        set("combat_exp", 50000000);

	set_skill("unarmed", 500);
	set_skill("finger", 500);
	set_skill("parry", 500);
	set_skill("dodge", 500);
	set_skill("force", 500);
	set_skill("sword", 500);
	set_skill("kuihua-mogong", 500);
	set_skill("martial-cognize", 500);
	set_skill("literate", 220);

	map_skill("parry", "kuihua-mogong");
	map_skill("force", "kuihua-mogong");
	map_skill("dodge", "kuihua-mogong");
	map_skill("unarmed", "kuihua-mogong");
	map_skill("finger", "kuihua-mogong");
	map_skill("sword", "kuihua-mogong");

	prepare_skill("finger", "kuihua-mogong");
	prepare_skill("unarmed", "kuihua-mogong");

	set("rank_info/self", "本座");

	set("chat_chance_combat", 10);
	set("chat_msg_combat", ({
		(: exert_function, "powerup" :),
		(: exert_function, "shield" :),
		(: exert_function, "recover" :),
		(: perform_action, "finger.you" :),
		(: perform_action, "finger.wu" :),
		(: perform_action, "finger.gui" :),
	}));

	setup();
	carry_object("/clone/cloth/cloth")->wear();
	carry_object("/clone/misc/spin")->wield();

        set("chat_chance", 10);
        set("chat_msg", ({
                (: NPC_D->random_move(this_object()) :),
        }));

        keep_heart_beat();
	setup();


        //set("startroom", "/d/mingjiao/xuantianshi");
        set_heart_beat(1);
        //check_clone();
}

void init()
{
    object *player;
    
    if (sizeof(player = filter_array(all_inventory(environment(this_object())), (: living($1) :))))
    {
        if (sizeof(player))
        {
            foreach (object ob in player)
            {
                if (!wizardp(ob))
                kill_ob(ob);
            }
        }
    }
}

void heart_beat()
{
        object *all;
        object me = this_object();
        
         if (!me->query_temp("weapon"))
	 carry_object("/clone/misc/spin")->wield();

        if (!this_object()->is_fighting())
        {
                if (me->query("level"))
                {
                        add_skill(me->query("level"));
                }
                ::heart_beat();

                return;
        }
        else
        {

                all = this_object()->query_enemy();
                me->set("level",sizeof(all));


                foreach (object ob in all)
                {
                        if (ob->query_skill("force") > me->query_skill("force"))
                        {
                                if (random(2) == 1)
                                me->move("/d/taishan/daizong");
                                else
                                me->move("/d/taishan/wudafu");

                                tell_object(ob,"今日心情不好，放阁下一马，吾走也！\n");
                        }
                }

                if (random(20) == 1)
                {
                        mapping my;
                        my = me->query_entire_dbase();
                        my["jing"]   = my["eff_jing"]   = my["max_jing"];
                        my["jingli"] = my["eff_jingli"] = my["max_jingli"];
                        my["qi"]     = my["eff_qi"]     = my["max_qi"]+me->query_gain_qi();
                        my["neili"]  = my["max_neili"];

                        foreach (object obs in all)
                        {
                                obs->add("eff_qi",-obs->query("eff_qi") / 2);
                                obs->add("qi",-obs->query("eff_qi") / 2);
                                obs->start_busy(random(3) + 1);

                                tell_object(obs,sprintf("只见%s全身魔气冲天，瞬发嗜血枪法第一式-鬼吸，掠夺了你的气血恢复了自身的状态。\n",me->query("name")));
                        }
                }
        }


 ::heart_beat();


}

int add_skill(int level)
{
        object me = this_object();
        mapping my;
        string skill,*skills;

        skills = keys(me->query_skills());

        me->add("max_qi",level * 10000);
        me->add("max_jing",level * 10000);
        me->add("combat_exp",level * 100000);
        me->add("max_neili",level * 10000);


        my = me->query_entire_dbase();
	my["jing"]   = my["eff_jing"]   = my["max_jing"];
	my["jingli"] = my["eff_jingli"] = my["max_jingli"];
	my["qi"]     = my["eff_qi"]     = my["max_qi"]+me->query_gain_qi();
	my["neili"]  = my["max_neili"];


        set_temp("apply/attack", 150 + level * 10);
	set_temp("apply/defense", 150+ level * 10);
	set_temp("apply/damage", 100+ level * 10);
	set_temp("apply/unarmed_damage", 100+ level * 10);
	set_temp("apply/armor", 200+ level * 30);
	set_temp("apply/sword", level * 20);
	set_temp("apply/force", level * 20);
	set_temp("apply/dodge", level * 20);
	set_temp("apply/parry", level * 20);
	set_temp("apply/unarmed", level * 20);

        foreach (skill in skills)
        {
                me->set_skill(skill,me->query_skill(skill,1) + 10 * level);
        }

       CHANNEL_D->do_channel(this_object(),"rumor","听说大宗师霍山游历江湖功力又获得进一步提升!\n");
       
        this_object()->delete("level");

}
