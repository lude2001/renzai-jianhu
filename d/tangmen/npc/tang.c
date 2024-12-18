// tang.c 唐老太太

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
string ask_me();
void create()
{
	set_name("唐老太太", ({ "tang laotai", "tang" }));
	set("nickname", HIW "霹雳夫人" NOR);
	set("long", 
		"她就是唐门第六代掌门唐老太太，在她的经营下，\n"
		"唐门在江湖中声名更加显赫。\n"
		"她大约七十有余，一头银发，红光满面。\n");
	set("gender", "女性");
	set("age", 70);
	set("attitude", "friendly");
	set("shen_type", 1);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	
	set("max_qi", 15000);
	set("max_jing", 13000);
	set("neili", 80000);
	set("max_neili", 80000);
	set("jiali", 100);
	set("combat_exp", 6000000);
	set("score", 600000);

	set_skill("force", 350);
	set_skill("biyun-xinfa", 300);
	set_skill("dodge", 350);
	set_skill("qiulinshiye", 300);
	set_skill("strike", 250);
	set_skill("unarmed",280);
	set_skill("biye-wu", 300);
	set_skill("parry", 280);
	set_skill("throwing", 350);
	set_skill("zimu-zhen", 350);
	set_skill("literate", 250);
	map_skill("force", "biyun-xinfa");
	map_skill("dodge", "qiulinshiye");
	map_skill("strike", "biye-wu");
	map_skill("unarmed","biye-wu");
	map_skill("parry", "zimu-zhen");
	map_skill("throwing", "zimu-zhen");
	
	create_family("唐门", 6, "掌门");
	set("class", "tangmen");

	set("chat_chance_combat", 90);
	set("chat_msg_combat", ({
		(: perform_action, "throwing.poqizhen" :),
		(: perform_action, "throwing.dinhun" :),
                (: perform_action, "throwing.qizigangbiao" :),
                (: perform_action, "throwing.tanghua" :),
		(: perform_action, "strike.wandu" :),
		(: perform_action, "strike.meng" :),
		(: exert_function, "recover" :),
	}) );
	set("inquiry", 
		([
			"大闹唐门" : (: ask_me :)
		]));

	setup();
	add_money("zimuzhen",300);
	carry_object("/d/tangmen/obj/zimuzhen")->wield();
	carry_object("/d/tangmen/obj/shujin")->wear();
}

void attempt_apprentice(object ob)
{
	if ((int)ob->query_skill("biyun-xinfa", 1) < 200) {
		command("say 唐门虽然以暗器为主，但还是要辅以内力。"); 
		command("say " + RANK_D->query_respect(ob) + 
			"是否还应该在碧云心法上多下点功夫？");
		return;
	}
	if (ob->query_int() < 30) {
		command("say 唐门历来注重弟子的文学修为。");
		command("say 本派功夫要能熟练运用，必须能体会其中所含深远意境，悟性差了是不行的。");
		command("say " + RANK_D->query_respect(ob) + "的悟性还大有潜力可挖，还是请回吧。");
		return;
	}
	if ((int)ob->query_skill("biye-wu", 1) < 200)
        {
        command("say 你的碧叶随风舞火候太浅。"); 
        return 0;
        }
	if ((int)ob->query_skill("qiulinshiye", 1) < 200)
{
command("say 你的本门轻功火候太浅。"); 
        return 0;
}
	if ((int)ob->query_skill("pili-biao", 1) < 200)
{
command("say 你的霹雳镖火候太浅。"); 
        return 0;
}
	if ((int)ob->query_skill("liuxing-biao", 1) < 200)
{
command("say 你的流星赶月镖火候太浅。"); 
        return 0;
}
	if ((int)ob->query_skill("zhuihun-biao", 1) < 200)
{
command("say 你的追魂夺命镖火候太浅。"); 
        return 0;
}
	command("say 哈哈哈哈！！！！");
	command("say 唐门又多了一个得力人才，真是可喜可贺。");
	command("recruit " + ob->query("id"));
}
string ask_me()
{object me;
me =this_player();
	if (me->query_temp("marks/闹")){
		command("say 你想帮唐方那个死丫头打探消息吗？看我不劈了你");
		command("hit " + me->query("id"));
		return "看来老太婆非得教训你一下不可。\n";}
       if (me->query_temp("marks/萧")){
	command("angry " + this_player()->query("id"));
	command("say 难道你想像萧秋水一样来个大闹唐门吗？\n");
	command("heng " + this_player()->query("id"));
	command("say 唐方那个死丫头！\n");
	this_player()->set_temp("marks/闹",1);
	me->delete_temp("marks/萧");
	return"萧秋水已被我关起来了！她别想再见到这个混小子了！\n";
							}
else{ 	
	return "瓜娃子，你说啥子？老太婆听不懂哦！\n";
    }


}
