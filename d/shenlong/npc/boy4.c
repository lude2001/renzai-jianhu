// boy4.c

#include <ansi.h>

inherit NPC;

void create()
{
	set_name("�������", ({"young boy", "boy", "young"}));
	set("title",HIY "������" HIG "����ʹ" NOR "���µ���");
	set("long",
		"����һ�������̵��ӣ�һϮ���£�����͸��һ��а����\n"
	);

	set("gender", "����");
	set("attitude", "peaceful");

	set("age", 10+random(10));
	set("shen_type", -1);
	set("str", 25+random(10));
	set("dex", 25+random(10));
	set("max_qi", 200);
	set("max_jing", 150);
	set("neili", 200);
	set("max_neili", 200);
	set("jiaji", 5+random(5));
	set("combat_exp", 20000+random(10000));

	set_skill("force", 40);
	set_skill("dodge", 40);
	set_skill("unarmed", 40);
	set_skill("parry", 40);
	set_skill("sword", 60);
	set_skill("shedao-qigong", 30);
	map_skill("sword","shedao-qigong");
	set("chat_chance", 3);
	set("chat_msg", ({
"������Ӻ�Ȼ�����е���������ѵ��ʱ�����ģ������˵У����²��ɣ�\n",
"������Ӻ�Ȼ�����е�����־���Ŀɳɳǣ����������ޱ��ף�\n",
"������Ӻ�Ȼ�����е����������������������������ǰ˷���\n",
"������Ӻ�Ȼ�����е����˷����˳�Ӣ����������ͬ���¹⣡\n",
"������������е������������ɸ����������룡\n",
	}) );

	setup();
	carry_object("/d/shenlong/obj/xionghuang")->wield();
	carry_object("/d/city/obj/duanjian")->wield();
	carry_object("/clone/misc/cloth")->wear();
}

#include "sldizi.h"