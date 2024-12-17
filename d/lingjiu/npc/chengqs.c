// /NPC fumy.c

#include <ansi.h>

inherit NPC;

void create()
{
	set_name("����˪", ({ "cheng qingshuang", "cheng"}));
	set("long",
	    "���ǡ����չ�������Ų��о��첿�ĸ�����.\n");
	set("title", "���첿������");
	set("gender", "Ů��");
	set("age", 20);
	set("shen_type",1);
	set("attitude", "peaceful");

	set("str", 25);
	set("int", 25);
	set("con", 30);
	set("dex", 30);

	set("qi", 800);
	set("max_qi", 800);
	set("jing", 400);
	set("max_jing", 400);
	set("neili", 1500);
	set("max_neili", 1500);
	set("jiali", 20);

	set("combat_exp", 100000);
	set("score", 10000);
	set_skill("force", 100);
	set_skill("unarmed", 90);
	set_skill("dodge", 90);
	set_skill("parry", 90);
	set_skill("hand", 90);
	set_skill("strike", 90);

	set_skill("zhemei-shou", 90);
	set_skill("liuyang-zhang", 90);
	set_skill("yueying-wubu", 90);
	set_skill("lingjiu-xinfa", 100);

	map_skill("force", "lingjiu-xinfa");
	map_skill("strike","liuyang-zhang");
	map_skill("dodge", "yueying-wubu");
	map_skill("unarmed", "liuyang-zhang");
	map_skill("hand", "zhemei-shou");
	map_skill("parry", "liuyang-zhang");

	prepare_skill("hand", "zhemei-shou");
	prepare_skill("strike","liuyang-zhang");

	create_family("���չ�",3,"����");
	setup();
	carry_object("/d/lingjiu/obj/qingyi")->wear();
	    carry_object("/d/lingjiu/obj/doupeng")->wear();
	add_money("silver",5);
}