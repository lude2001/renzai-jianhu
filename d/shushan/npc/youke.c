//shushan2 by yushu 2000.12
inherit NPC;
void create()
{
	set_name("�ο�", ({ "youke", "traveller"}));
	if(random(10)<7)
	    set("gender", "����" );
	else
	    set("gender", "Ů��" );
	set("age", 15+random(50));
	set("long",
		"����һλ����ɽ���������οͣ��糾���ӡ�\n");
	set("chat_chance", 40);
       set("combat_exp", 600+random(400));
	set("attitude", "friendly");
	set_skill("dodge", 10);
	set_skill("unarmed", 10);
	setup();
       carry_object("/clone/cloth/cloth")->wear();
	add_money("silver", 3+random(20));
}