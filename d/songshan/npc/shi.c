// shi.c
inherit NPC;

#include <ansi.h>

void create()
{
	set_name("ʷ�Ǵ�", ({ "shi dengda", "dengda", "shi" }) );
	set("nickname", "ǧ����");
	set("gender", "����");
	set("class", "swordsman");
	set("age", 25);
	set("attitude", "peaceful");
	set("str", 26);
	set("con", 30);
	set("dex", 30);
	set("int", 28);

	set("neili", 1000);
	set("max_neili", 1000);
	set("jiali", 30);
	set("max_qi",1000);
	set("max_jing",800);
	set("combat_exp", 60000);
	set("shen_type", -1);

	set_skill("unarmed", 60);
	set_skill("sword", 60);
	set_skill("force", 60);
	set_skill("parry", 60);
	set_skill("dodge", 60);
	set_skill("songshan-sword", 60);
	set_skill("lingxu-bu", 60);
	set_skill("songshan-xinfa", 80);

	map_skill("force", "songshan-xinfa");
	map_skill("sword", "songshan-sword");
	map_skill("parry", "songshan-sword");
	map_skill("dodge", "lingxu-bu");

	create_family("��ɽ��", 14, "����");
	setup();

	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/cloth/cloth")->wear();
}

