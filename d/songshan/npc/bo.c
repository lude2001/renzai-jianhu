// bo.c
inherit NPC;

#include <ansi.h>

void create()
{
	set_name("����", ({ "bo chen", "chen", "bo" }) );
	set("nickname", "��ͷ��");
	set("gender", "����");
	set("class", "swordsman");
	set("age", 53);
	set("attitude", "peaceful");
	set("str", 26);
	set("con", 30);
	set("dex", 30);
	set("int", 28);

	set("neili", 2000);
	set("max_neili", 2000);
	set("jiali", 30);
	set("max_qi",2000);
	set("max_jing",1200);
	set("combat_exp", 90000);
	set("shen_type", -1);

	set_skill("unarmed", 80);
	set_skill("sword", 80);
	set_skill("force", 80);
	set_skill("parry", 80);
	set_skill("dodge", 80);
	set_skill("songshan-sword", 80);
	set_skill("lingxu-bu", 80);
	set_skill("songshan-xinfa", 80);

	map_skill("force", "songshan-xinfa");
	map_skill("sword", "songshan-sword");
	map_skill("parry", "songshan-sword");
	map_skill("dodge", "lingxu-bu");

	create_family("��ɽ��", 13, "����");
	setup();

	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/cloth/cloth")->wear();
}
