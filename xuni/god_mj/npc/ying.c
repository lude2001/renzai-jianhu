inherit NPC;
varargs void create(int level)
{
	set_name("不屈英魂", ({ "buqu hun", "hun" }) );
	set("title", HIY "传奇" NOR);
	set("gender", "男性");
	set("age", 32);
	set("long", "似幻非幻，以无法目视其人。\n");
	set("attitude", "peaceful");
	set("str", 32);
	set("int", 39);
	set("con", 37);
	set("dex", 32);

	set("max_qi", 10000 * level);
	set("max_jing", 10000 * level);
	set("neili", 10000 * level);
	set("max_neili", 10000 * level);
	set("jiali", 300);

	set("combat_exp", 500000 * level);

	set_skill("unarmed", 690 + 10 * level);
	set_skill("finger", 690 + 10 * level);
	set_skill("claw", 690 + 10 * level);
	set_skill("strike", 690 + 10 * level);
	set_skill("hand", 690 + 10 * level);
	set_skill("cuff", 690 + 10 * level);
	set_skill("parry", 690 + 10 * level);
	set_skill("dodge", 690 + 10 * level);
	set_skill("force", 690 + 10 * level);
	set_skill("jiuyin-shengong", 690 + 10 * level);
	set_skill("martial-cognize", 690 + 10 * level);
	set_skill("literate", 690 + 10 * level);

	map_skill("parry", "jiuyin-shengong");
	map_skill("force", "jiuyin-shengong");
	map_skill("dodge", "jiuyin-shengong");
	map_skill("unarmed", "jiuyin-shengong");
	map_skill("finger", "jiuyin-shengong");
	map_skill("strike", "jiuyin-shengong");
	map_skill("hand", "jiuyin-shengong");
	map_skill("cuff", "jiuyin-shengong");
	map_skill("claw", "jiuyin-shengong");

	prepare_skill("claw", "jiuyin-shengong");
	prepare_skill("cuff", "jiuyin-shengong");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: exert_function, "powerup" :),
		(: exert_function, "shield" :),
		(: exert_function, "recover" :),
		(: perform_action, "cuff.quan" :),
		(: perform_action, "strike.zhang" :),
		(: perform_action, "claw.zhua" :),
		(: perform_action, "finger.zhi" :),
	}));


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

	setup();
	carry_object("/clone/cloth/cloth")->wear();
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
        int wound;

        if (random(5) == 1)ob->start_busy(8 + random(16));
        wound=20000+random(20000)-me->query_temp("apply/armor");
        if (wound < 1)wound = 1;
        me->receive_wound("qi", wound, ob);
        return HIY "$N" HIY "怒喝一声，奋力反抗，竟逼得$n" HIY "手忙脚乱。\n" NOR;
}

void heart_beat()
{
        if (query("neili") < 100 && random(50) == 1)
                set("neili", query("max_neili"));

        return ::heart_beat();
}
