// long.c

#include <ansi.h>
inherit NPC;

int ask_zhou();
int ask_back();

void create()
{
	set_name("河怪", ({"he guai", "guai"}));
	set("title", HIR "七夕河怪" NOR);
	set("gender", "男性");
	set("age", 60);
	set("long",
		"这是一个河怪。\n");

	set_temp("apply/attack", 600);
	set_temp("apply/armor", 1500);
	set_temp("apply/damage", 800);
	set_temp("apply/unarmed_damage", 800);
	set_temp("apply/dodge", 600);
	set_temp("apply/parry", 600);

	set("qi", 9000);
	set("max_qi", 9000);
	set("jing", 200000);
	set("max_jing", 200000);
	set("neili", 150000);
	set("max_neili", 150000);
	set("jiali", 250);
	set("combat_exp", 5000000);
	set("score", 20000000);

	set("level", 1);

	set_skill("force", 200);
	set_skill("taixuan-gong", 200);
	set_skill("dodge", 200);
	set_skill("taixuan-gong", 200);
	set_skill("unarmed", 200);
	set_skill("taixuan-gong", 200);
	set_skill("parry", 200);

	map_skill("force", "taixuan-gong");
	map_skill("dodge", "taixuan-gong");
	map_skill("unarmed", "taixuan-gong");
	map_skill("parry", "taixuan-gong");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
							   (
								   : exert_function, "powerup"
								   :),
							   (
								   : perform_action, "unarmed.taixuan"
								   :),
						   }));

	setup();

	carry_object("/clone/misc/cloth")->wear();
}

void die()
{
	object who = this_object()->query_last_damage_from();
	string str;
	object gift;
	int random;

	object *team;

	if (objectp(who) && pointerp(team = who->query_team()) && sizeof(team) == 2)
	{
		object env;

		env = environment(this_object());

		foreach (object ob in team)
		{
			if (environment(ob) == env)
			{
				str = "你获得了";
				ob->add("combat_exp", 1500);
				ob->add("potential", 1500);
				ob->add("qixi_dian",1);
				str += "1500经验和潜能,以及一点七夕点。\n";
				tell_object(ob, str);

			}
		}


	}

	if (query("level") < 100)
	{
		object npc;

		npc = new("/d/fuben/qixi/npc/guai");
		npc->add_g(query("level") + 1);
		npc->move(environment(this_object()));
	}

	::die();
}

int add_g(int level)
{
	string *skills;

	set("max_qi",query("max_qi") + level * 1000);
	set("eff_qi",query("max_qi"));
	set("qi",query("max_qi"));

	skills = keys(query_skills());

	foreach (string skill in skills)
	{
		set_skill(skill,query_skill(skill,1) + level * 10);
	}

	set("level",level);

}

