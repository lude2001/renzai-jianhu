//¡¾ÊñÉ½ÅÉ¡¿mhxy-yushu 2001/2
inherit NPC;
inherit F_MASTER;

#include "shushan.h"
#include <ansi.h>
string ask_me();
int ask_jiu();
void create()
{
       set_name("¾Æ½£ÏÉ", ({"jiu jianxian", "jianxian", "xian"}));
       set("title", HIC"×íµÀÊ¿"NOR);   
       set("long", "Ò»ÈËÈËËÍÍâºÅ¡°¾Æ½£ÏÉ¡±£¬ĞĞ×Ù²»¶¨£¬»òÓÎÀúÓÚÃûÉ½´ó´¨Ö®ÅÏ£¬»òÒşÄäÓÚ½ÖÍ·ÄÖÊĞÖ®ÖĞ¡£\n");
       set("gender", "ÄĞĞÔ");
       set("age", 68);
       set("attitude", "peaceful");
       set("class", "xiake");
       set("str", 80);
       set("int", 80);
       set("per", 80);
       set("con", 80);
       set("combat_exp", 100000000);
       set("max_qi", 3700000);
       set("max_jing", 1700000);
       set("neili", 4000000);
       set("max_neili", 2000000);
       set("jiali", 1200);
/*
       set("max_mana", 2000);
       set("mana", 4000);
       set("mana_factor", 120);
*/
        set("max_jingli", 200000);
       set("max_neili", 200000);
     set("jingli", 200000);
        set("neili",3000000);
        set_skill("shushan-force", 1000);
      set_skill("yujianshu", 1000);
      set_skill("fumozhang", 1000); 
      set_skill("zuixian-steps", 1000);
       set_skill("sword", 1000);
       set_skill("unarmed", 1000);
       set_skill("dodge", 1000);
       set_skill("literate", 1000);
       set_skill("force", 1000);
       set_skill("parry", 1000);
       map_skill("dodge", "zuixian-steps");
	map_skill("parry", "yujianshu");
	map_skill("sword", "yujianshu");
       map_skill("force", "shushan-force");
       map_skill("unarmed","fumozhang");
       set("chat_chance_combat", 60);
       set("chat_msg_combat", ({
		  (: cast_spell, "fu" :),
                (: perform_action, "sword", "fumo" :),
        }) );
       set("inquiry", ([
                 "¾ÆÉñ" : (: ask_jiu :),
	  "ÏÉÊõ" : (: ask_me :),

       ]) );
       create_family("ÊñÉ½ÅÉ", 2, "µÜ×Ó");
set("book_count", 1);
       setup();
      carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}

void attempt_apprentice(object ob)
{	ob=this_player();

	if (! permit_recruit(ob))
		return;
		
	if( (string)ob->query("family/family_name")=="ÊñÉ½ÅÉ") {
         if ((int)ob->query("combat_exp") < 10000000 ) {
  	command("say ÄãµÄexp»¹²»¹»£¬" + RANK_D->query_respect(ob) + "»¹Ğè¶à¼ÓÅ¬Á¦²ÅĞĞ¡£\n");
	return;
	}
       if( (int)ob->query_skill("force", 1) < 750 ) {
        command("say ÕâÎ»" + RANK_D->query_respect(ob) + "Äã¿´ÄãµÄºïÑù»¹À´ÕÒÎÒ°İÊ¦? Äã»¹ÊÇÕÒ×·ÔÆ×ÓËûÃÇÁ·×Å°É!\n");
	command("sigh");
	return;
	}
       command("haha");
       command("say ºÜºÃ£¬" + RANK_D->query_respect(ob) + "¶à¼ÓÅ¬Á¦£¬ËûÈÕ±Ø¶¨ÓĞ³É¡£");
       command("recruit " + ob->query("id") );
	return;
	}
       command("shake");
       command("say ÄãÊÇ±¾ÅÉµÄÂğ?£¬" + RANK_D->query_respect(ob) + "»¹ÊÇÁíÑ°ËûÈË°É£¡\n");
       return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) ) {
                ob->set("class", "xiake");
                ob->set("title", "ÊñÉ½¾Æ½£ÏÉµÜ×Ó");

               } 
}

int ask_jiu()
{

    object ob=this_player();
    if(ob->query("family/family_name") != "ÊñÉ½ÅÉ")
    {
    command("say ÄãÓÖ²»ÊÇÊñÉ½ÅÉµÄ£¬Ë­¹ÜÄã£¡");
    return 1;
    }
    if(ob->query("shushan/jiushen_cast"))
    { 
    command("say Äã²»ÊÇÎÊ¹ıÁËÂğ? ");
    return 1;
    }
    if(ob->query("family/master_name") == "¾Æ½£ÏÉ" )
    {
    command("say ÕâÒ»ÕĞ¾ÆÉñ£¬ÊÇÎªÊ¦Î¨Ò»ÄÜ¸øÄãµÄ£¬¾ø²»±ÈÈÎºÎ·¨Êõ²î£¡ËüÓ¦¸Ã¿ÉÒÔ°ïÄã±£ÃüµÄ£¡");
    ob->set("shushan/jiushen_cast",1);
    return 1;
    }
}


string ask_me()
{
        mapping fam; 
        object ob;
        if (!(fam = this_player()->query("family")) 
        || fam["family_name"] != "ÊñÉ½ÅÉ")
                return RANK_D->query_respect(this_player()) + 
                "ÓÖ²»ÊÇÊñÉ½ÅÉµÄ£¬Ë­¹ÜÄã£¡";
        if (query("book_count") < 1)
                return "ÄãÀ´ÍíÁË";
        add("book_count", -1);
        ob = new("/d/shushan/obj/xfbook");
        ob->move(this_player());
        return "ºÃ°É£¬ÕâÄãÄÃ»ØÈ¥ºÃºÃ×êÑĞ¡£";
}

ÿ
