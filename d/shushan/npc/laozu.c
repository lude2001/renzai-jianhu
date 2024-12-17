//¡¾ÊñÉ½ÅÉ¡¿mhxy-yushu 2001/2
inherit NPC;
inherit F_MASTER;
int ask_back();
#include <ansi.h>
#define BHUOZHU       "/d/shushan/zhenyaota/obj/huozhu"
void create()
{
       set_name(HIW "¾²ĞéÀÏ×æ" NOR, ({"master jingxu","jingxu", "master"}));
       set("title",HIC"ÊñÉ½ÅÉ¿ªÉ½×æÊ¦"NOR);
       set("gender", "ÄĞĞÔ");
       set("age", 220);
	set("class", "xiake");
       set("attitude", "peaceful");
       set("shen_type", 1);
       set("rank_info/respect", "ÀÏÊ¦×æ");
       set("per", 26);
	set("long", "ËûÓñÃæ¶à¹âÈó£¬²Ô÷×ò¢ÏÂÆ®£¬½ğ¾¦·É»ğÑæ£¬³¤Ä¿¹ıÃ¼ÉÒ¡£\n");
	set("int", 30);
       set("max_qi", 500000);
       set("max_jing", 50000);
       set("neili", 500000);
       set("max_neili", 25000);
   set("neili", 20000000);
       set("jiali", 1500);
/*
       set("max_mana", 2500);
       set("mana", 5000);
       set("mana_factor", 150);
*/
       set("combat_exp", 300000000);
       set_skill("literate", 2000);
       set_skill("dodge", 2000);
       set_skill("parry", 2000);
       set_skill("unarmed", 2000);
        set_skill("fumozhang", 2000); 
        set_skill("songhe-sword", 2000);
       set_skill("yujianshu", 2000);
       set_skill("shushan-force", 2000);
	set_skill("sword", 2000);
	set_skill("force", 2000);
     set_skill("zuixian-steps", 2000);
       map_skill("force", "shushan-force");
	map_skill("sword", "yujianshu");
	map_skill("parry", "yujianshu");
	map_skill("dodge", "zuixian-steps");
       map_skill("unarmed","fumozhang");
       set("chat_chance_combat", 10);
       set("chat_msg_combat", ({
	  (: perform_action, "sword." :),
                (: perform_action, "sword." :),
        }) );
        set("inquiry", ([
                 "»ØÈ¥" : (: ask_back :),
                 "back" : (: ask_back :),
	  "Íò½£¾ö" : "Èç¹ûÄãÄÜ°ïÎÒÕÒµ½»ğÁéÖéÎÒ¾Í½ÌÄã£¡\n",
         ]) );
        create_family("ÊñÉ½ÅÉ", 1, "µÜ×Ó");
        setup();

       carry_object("/clone/cloth/cloth")->wear();
carry_object("/d/shushan/obj/qixing")->wield();
}

void attempt_apprentice(object ob)
{	ob=this_player();
       if( (string)ob->query("family/family_name")=="ÊñÉ½ÅÉ") {
        if ((int)ob->query("combat_exp") < 300000000 ) {
  	command("say ÄãµÄexp»¹²»¹»£¬¶ÔÎÒµÄÕĞ·¨ÄÑÒÔÁìÎò¡£\n");
	return;
	}
 if( (int)ob->query_skill("zuixian-steps", 1) < 1000 ) {
command("say ÕâÎ»" + RANK_D->query_respect(ob) + "ÄãµÄ×íÏÉÍûÔÂ²½»¹²»µ½»ğºò,Äã»¹ÊÇÕÒ½£Ê¥ËûÃÇÁ·×Å°É!\n")
;
	command("sigh");
	return;
	}
       if( (int)ob->query_skill("force", 1) < 1000 ) {
	command("say ÕâÎ»" + RANK_D->query_respect(ob) + "ÄãµÄ»ù±¾ÄÚ¹¦»¹²»µ½»ğºò,Äã»¹ÊÇÕÒ½£Ê¥ËûÃÇÁ·×Å°É!\n");
	command("sigh");
	return;
	}
       if( (int)ob->query_skill("sword", 1) < 1000 ) {
	command("say ÕâÎ»" + RANK_D->query_respect(ob) + "ÄãµÄ»ù±¾½£·¨»¹²»µ½»ğºò,Äã»¹ÊÇÕÒ½£Ê¥ËûÃÇÁ·×Å°É!\n");
	command("sigh");
	return;
	}
       command("smile");
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
                ob->set("title", "ÊñÉ½¾²ĞéÀÏ×æ´«ÈË");

}

        return 0;
}
int ask_back()
{

    object ob=this_player();
    if(ob->query("family/family_name") != "ÊñÉ½ÅÉ")
    {
    command("say ÄãÓÖ²»ÊÇÊñÉ½ÅÉµÄ£¬ÄãÎÊÕâ¸ö¸ÉÂğ£¡");
    return 1;
    }
    if(ob->query("shushan/tuoqiao_cast"))
    { 
    command("say Äã²»ÊÇÖªµÀÁËÂğ? ");
    return 1;
    }
    if(ob->query("family/master_name") == "¾²ĞéÀÏ×æ" )
    {
    command("say ÄãÏë³öÈ¥°¡£¡ºÃ°É!ÎÒ½ÌÄãÒ»ÕĞ¡¸½ğ²õÍÑ¿Ç¡¹!");
    command("say ÓÃ(cast tuoqiao)¾ÍÄÜ³öÈ¥!");
    command("say ÏÂ´Î½øÀ´Ê±¾Í²»ÒªÄÇÃ´Âé·³ÁË,È¥²Ø¾­¸ó(push Êé¼Ü)¾Í¿ÉÒÔÁË¡£");
    ob->set("shushan/tuoqiao_cast",1);
    return 1;
    }
}


int accept_object(object me, object obj)
{
object tuzhu;
if(base_name(obj)!=BHUOZHU)
{
                command("say ÎÒÒªµÄÊÇ»ğÁéÖé!ÆäËûµÄÎÒÃ»ĞËÈ¤¡£\n");
                return 0;
}
	me->set("shushan/wanjian_perform", 10);
	command("say ¿´ÔÚÄãÄÇÃ´ÓĞĞÄµÄ·İÉÏ£¬ÎÒ¾Í½ÌÄã¡¸Íò½£¾ö¡¹¡£\n");
destruct(obj);
return 1;

}
ÿ
