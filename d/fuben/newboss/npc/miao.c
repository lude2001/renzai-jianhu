
#include <ansi.h>;

inherit NPC;
#include "dj.h"

string ask_me();

void create()
{
	set_name("���˷�", ({ "miao renfeng", "miao" }));
	set("gender", "����");
	set("nickname", YEL "�����" NOR);
	set("age", 37);
	set("long", @LONG
������ȥ��ɫ͸�ƣ��ƺ�����һ�㵭���Ľ�ֽ����ĸߴ���࣬ȷ
��ȫȻ����ƪ�������˳��档
LONG );
	set("attitude", "peaceful");

	set("boss","miao");

	set("str", 32);
	set("int", 31);
	set("con", 33);
	set("dex", 31);
    set_temp("apply/armor", 800);
    
	set("qi", 30000000);
	set("max_qi", 30000000);
	set("jing", 10000000);
	set("max_jing", 10000000);
	set("neili", 10000000);
	set("max_neili", 10000000);
	set("jiali", 120);
	set("combat_exp", 100000000);

	set_skill("force", 220);
	set_skill("hunyuan-yiqi", 220);
	set_skill("sword", 230);
	set_skill("miaojia-jian", 230);
	set_skill("dodge", 210);
	set_skill("feiyan-zoubi", 210);
	set_skill("strike", 225);
	set_skill("tianchang-zhang", 225);
	set_skill("parry", 230);

	map_skill("force", "hunyuan-yiqi");
	map_skill("sword", "miaojia-jian");
	map_skill("dodge", "feiyan-zoubi");
	map_skill("parry", "miaojia-jian");
	map_skill("strike", "tianchang-zhang");

	prepare_skill("strike", "tianchang-zhang");

	set("inquiry", ([
		"��һ��": (: ask_me :),
		"��������޵���" : "�⻰˵˵���ѣ����ܵ��棿",
	]));
	set_heart_beat(1);
	setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/cloth/cloth")->wear();
}

string ask_me()
{
	object ob, me;

	me = this_player();
	if (me->query("family/family_name") != "�������")
		return "��������һ�����ӣ���ϧ����ϧ��\n";

	return "���겻�����˼��˶����������������ź�������";
}
