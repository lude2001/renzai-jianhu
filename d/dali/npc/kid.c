// kid.c

inherit NPC;

void create()
{
	set_name("����С��",({ "kid" }) );
	set("gender", "����" );
	set("age", 5);
	set("long", "һ����С�İ��Ķ�ͯ��\n");
	set("combat_exp", 50);
	set("shen_type", 1);
	set("str", 11);
	set("dex", 11);
	set("con", 11);
	set("int", 11);
	set("attitude", "friendly");
	setup();
	carry_object("/clone/cloth/cloth")->wear();
}

