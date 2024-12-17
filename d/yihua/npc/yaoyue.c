// /NPC gongzhu.c

#include <ansi.h>

//inherit BH_NPC;
inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("邀月", ({ "yao yue", "yao", "yue" }));
	set("long",
	    "她就是「移花宫」的开山祖师.\n"+
	    "她用薄薄的面纱蒙着脸,可是透过那块面纱你仍然依稀可见\n"+
	    "她面色煞白,以不是人间所人看见的,你不由得多看了一眼.\n");
	set("title", "移花宫大宫主");
	set("gender", "女性");
	set("age", 36);
	set("nickname", HIR "杀尽天下负心汉" NOR);
      set("shen_type",-500);
	set("attitude", "peaceful");

    set("str", 1550);
	set("int", 350);
	set("con", 400);
	set("dex", 250);

	set("qi", 50000);
	set("max_qi", 50000);
	set("jing", 14000);
    set("max_jing", 5000);
      set("neili", 9000000);
    set("max_neili", 20000);
      set("jiali", 20000);

      set("combat_exp", 600000000);
	set("score", 2000000);
	set_skill("force", 750);
	set_skill("unarmed", 750);
	set_skill("dodge", 700);
	set_skill("parry", 750);
	set_skill("sword",850);
        set_skill("literate",1000);

	set_skill("jueqing-zhang",700);
	set_skill("mingyu-shengong",700);
	set_skill("yifeng-jian",700);
        set_skill("yihua-jiemu",700);

	map_skill("force", "mingyu-shengong");
	map_skill("unarmed", "jueqing-zhang");
		map_skill("dodge", "yihua-jiemu");
	map_skill("parry", "yihua-jiemu");
        map_skill("sword","yifeng-jian");

	create_family("移花宫",1, "邀月宫主");
set("chat_chance_combat", 50);
	set("chat_msg_combat", ({
		(: perform_action, "sword.yifeng" :),
			}) );
	setup();
	carry_object("/d/city/obj/changjian")->wield();
    carry_object("/d/yihua/obj/jinlvyi")->wear();
       
}

void attempt_apprentice(object ob)
{
   
   if ((string)ob->query("gender")!="女性")
           {
 		command("chat* heihei");
                command("chat 我这一生最恨的就是男人,你去死吧!");
                kill_ob(this_player());
                command("perform yifeng");
		return;
	   }
   if ((int)ob->query_skill("dodge", 1) < 100) 
           {
		command("say " + RANK_D->query_respect(ob) + "你的身法不够!");
		return;
	   }
   if ((int)ob->query_skill("mingyu-shengong", 1) < 330) 
           {
		command("say " + RANK_D->query_respect(ob) + "是否还应该多练练冥雨神功？");
		return;
	   }
   if ((int)ob->query_skill("yifeng-jian", 1) < 130) 
           {
		command("say " + RANK_D->query_respect(ob) + "是否还应该多练练移风剑法？");
		return;
	   }
   if (ob->query_per() < 19) 
      	   {
		command("say 凭你这模样还想拜我为师.");
		return;
	   }
   if (ob->query_con() < 40) 
      	   {
		command("say 本门功法极为难练,你的根骨似乎不够.");
		return;
	   }
   command("recruit " + ob->query("id"));
   if((string)ob->query("class") != "chuanren")
     ob->set("class", "chuanren");
   return;
}

void init()
{
	object ob;

	::init();

	ob = this_player();

	if (interactive(ob) && (!ob->query("gender") || ob->query("gender")!="女性"))
	{
			command("heihei");
			command("say 我平生最讨厌男人！你竟然来送死，好吧，我就成全了你！\n");
			remove_call_out("kill_ob");
                        call_out("kill_ob", 1, ob); 
                        command("perform yifeng");
	}
	else if(ob->query("gender")=="女性")
	{
	command("smile");
	command("say 好在你不是男人不然你会死得很惨。");
	}
}
void die()
{
       command("sigh");
        if(killer->query("lonely/duguqiubai1") ){
         killer->delete("lonely/duguqiubai1");
         killer->set("lonely/duguqiubai2",1);
       message_vision("\n$N娇喘一口气，说道：没有想到你小小年纪就能领悟武学的精髓。\n", this_object());
      destruct(this_object());
          }
  else
      message_vision("$N说完，化作一缕清风而去。\n", this_object());
   return ::die();
//      destruct(this_object());
  }

