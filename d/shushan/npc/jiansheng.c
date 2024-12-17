//jiansheng.c by yushu 2000.11
inherit NPC;
inherit F_QUESTER;
inherit F_MASTER;

#include "shushan.h"
#include <ansi.h>
void create()
{
       set_name("ÊñÉ½½£Ê¥", ({"shushan jiansheng","jiansheng", "master"}));
       set("title", "ÊñÉ½ÅÉ½£·¨Ö®Ê¥");
       set("gender", "ÄÐÐÔ");
       set("age", 120);
	set("class", "xiake");
       set("attitude", "friendly");
       set("shen_type", 1);
       set("rank_info/respect", "ÀÏÊ¦×æ");
       set("per", 26);
	set("looking", "ÓñÃæ¶à¹âÈó£¬²Ô÷×ò¢ÏÂÆ®£¬½ð¾¦·É»ðÑæ£¬³¤Ä¿¹ýÃ¼ÉÒ¡£");
	set("int", 30);
       set("max_qi", 5000000);
       set("max_gin", 1000);
       set("max_jing", 5000);
       set("neili", 5000);
       set("max_neili", 2500);
       set("jiali", 150);
/*
       set("max_mana", 2500);
       set("mana", 5000);
       set("mana_factor", 150);
*/
         set("combat_exp", 200000000);
        set("max_jingli", 10000);
        set("max_neili", 20000);
        set("jingli", 10000);
        set("neili",100000);
         set("jiali",10000);
       set_skill("literate", 1000);
       set_skill("dodge", 1000);
       set_skill("parry", 1000);
       set_skill("unarmed", 1000);
       set_skill("fumozhang",1000); 
	set_skill("sword", 1000);
     set_skill("songhe-sword", 1000);
         set_skill("shushan-force", 1000);
	set_skill("force", 1000);
        set_skill("zuixian-steps", 1000);
       map_skill("force", "shushan-force");
	map_skill("sword", "songhe-sword");
	map_skill("parry", "songhe-sword");
	map_skill("dodge", "zuixian-steps");
       map_skill("unarmed","fumozhang");
       set("chat_chance_combat", 60);
       set("chat_msg_combat", ({
		  (: cast_spell, "fu" :),
        }) );
        create_family("ÊñÉ½ÅÉ", 2, "µÜ×Ó");
        setup();
        carry_object("/clone/cloth/cloth")->wear();
}
void attempt_apprentice(object ob)
{	ob=this_player();

	if (! permit_recruit(ob))
		return;
		
       if ( !((string)ob->query("gender")=="ÄÐÐÔ")){
       command("shake");
       command("say ÎÒÖ»ÊÕÄÐÍ½£¬ÕâÎ»" +RANK_D->query_respect(ob) + "»¹ÊÇÈ¥ÕÒ¾Æ½£ÏÉ°É¡£\n");
       return;
       }
       if( (string)ob->query("family/family_name")=="ÊñÉ½ÅÉ") {
         if ((int)ob->query("combat_exp") < 10000000 ) {
  	command("say ÄãµÄexp»¹²»¹»£¬¶ÔÎÒµÄÕÐ·¨ÄÑÒÔÁìÎò¡£\n");
	return;
	}
        if( (int)ob->query_skill("force", 1) < 550 ) {
      command("say ÕâÎ»" + RANK_D->query_respect(ob) + "ÄãµÄÉíÌåÕâÃ´²î,Äã»¹ÊÇÕÒ×·ÔÆ×ÓËûÃÇÔÙÁ·×Å°É!\n");
	command("sigh");
	return;
	}
       command("smile");
       command("say ºÜºÃ£¬" + RANK_D->query_respect(ob) + "¶à¼ÓÅ¬Á¦£¬ÎªÊñÉ½Õù¹â¡£");
       command("recruit " + ob->query("id") );
	return;
	}
       command("shake");
       command("say ÄãÊÇ±¾ÅÉµÄÂð?£¬" + RANK_D->query_respect(ob) + "»¹ÊÇÁíÑ°ËûÈË°É£¡\n");
       return;
}
int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) ) {
                ob->set("class", "xiake");
                ob->set("title", "ÊñÉ½½£Ê¥Ç×´«µÚ×Ó");

}

        return 0;
}





ÿ
