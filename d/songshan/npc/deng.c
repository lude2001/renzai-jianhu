// deng.c
inherit NPC;

#include <ansi.h>

void create()
{
	set_name("�˰���", ({ "deng banian", "banian", "deng" }) );
	set("nickname", "���");
	set("gender", "����");
	set("class", "swordsman");
	set("age", 35);
	set("attitude", "peaceful");
	set("str", 26);
	set("con", 30);
	set("dex", 30);
	set("int", 28);

	set("neili", 1000);
	set("max_neili", 1000);
	set("jiali", 30);
	set("max_qi",2000);
	set("max_jing",1200);
	set("combat_exp", 270000);
	set("shen_type", -1);

	set_skill("sword", 140);
	set_skill("force", 140);
	set_skill("parry", 140);
	set_skill("dodge", 130);
	set_skill("songshan-sword", 140);
	set_skill("lingxu-bu", 130);
	set_skill("songshan-xinfa", 140);

	map_skill("force", "songshan-xinfa");
	map_skill("sword", "songshan-sword");
	map_skill("parry", "songshan-sword");
	map_skill("dodge", "lingxu-bu");

	create_family("��ɽ��", 13, "����");
	setup();

	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/cloth/cloth")->wear();
}
