// zhong.c
inherit NPC;

#include <ansi.h>

void create()
{
	set_name("����", ({ "zhong zhen", "zhen", "zhong" }) );
	set("nickname", "������");
	set("gender", "����");
	set("class", "swordsman");
	set("age", 45);
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
	set("combat_exp", 150000);
	set("shen_type", -1);

	set_skill("unarmed", 80);
	set_skill("sword", 140);
	set_skill("force", 120);
	set_skill("parry", 100);
	set_skill("dodge", 100);
	set_skill("songshan-xinfa", 120);
	set_skill("songshan-sword", 140);
	set_skill("lingxu-bu", 100);

	map_skill("force", "songshan-xinfa");
	map_skill("sword", "songshan-sword");
	map_skill("parry", "songshan-sword");
	map_skill("dodge", "lingxu-bu");

	create_family("��ɽ��", 13, "����");
	setup();

	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/cloth/cloth")->wear();
}

