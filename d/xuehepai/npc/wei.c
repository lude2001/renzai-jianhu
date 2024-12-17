// made by lks

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
#include "wei.h"
void heal_ob();
void recover_ob();

void create()
{
        set_name("卫悲回",({"wei beihui","wei"}));
        set("nickname",HIR"血踪万里"NOR);
	set("gender","男性");
	set("int",30);	
	set("con",30);
	set("str",130);
	set("dex",130);
	set("bac",40);
	set("age",40);
	set("attitude","peaceful");
        set("combat_exp",18000000);
        set("shen",1000);
	set("long",
"英俊潇洒,颇有大将风度。但也恃才傲\n物，终于在与萧秋水一役中，死于龙门急流中。\n"
	);
        set("neili",50000);
        set("jingli",30000);
        set("max_neili",50000);
        set("max_jingli",30000);
        set_skill("literate",600);
        set_skill("cuff",600);
	set_skill("parry",600);
	set_skill("dodge",600);
        set_skill("wanhua-bu",600);
        set_skill("yudi-bian",600);
        set_skill("whip",600);
        set_skill("jieniu-dao",600);
        set_skill("blade",600);
       set_skill("yiqiguan-riyue",600);
        set_skill("throwing",600);
        set_skill("youren-jian",600);
        set_skill("sword",600);
        set_skill("tianhe-jian",600);
	set_skill("force",600);
        set_skill("hx-jing",600);
	set_skill("taoism",600);
        set_skill("feixue-quan",600);
        map_skill("force","hx-jing");
        map_skill("cuff","feixue-quan");
        map_skill("sword","tianhe-jian");
        map_skill("blade","jieniu-dao");
        map_skill("throwing","youren-jian");
        map_skill("whip","yudi-bian");
        prepare_skill("cuff","feixue-quan");
	
       create_family("合欢宗",12,"掌门");
	setup();
	carry_object("/clone/misc/cloth")->wear();
        set("chat_chance", 2);
	set("chat_msg", ({
		(: heal_ob :),
	}));
	set("chat_chance_combat", 30);
	set("chat_msg_combat", ({
                (: exert_function, "xuanwo" :),
                (: recover_ob :),
	}) );
}

	
void heal_ob()
{
	command("yun heal");
	command("yun heal");
	command("yun heal");
	command("yun recover");
	return;
}

void recover_ob()
{
	command("yun recover");
	return;
}

