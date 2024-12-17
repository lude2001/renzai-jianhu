//ling yunzi-yushu 2001.2
inherit NPC;
inherit F_MASTER;

#include "shushan.h"
void create()
{
       set_name("ÁèÔÆ×Ó", ({"ling yunzi", "yunzi", "zi"}));
       set("title", "ÊñÉ½ÅÉµÚÈı´úµÜ×Ó");   
       set("gender", "ÄĞĞÔ");
       set("age", 32);
       set("attitude", "peaceful");
       set("class", "xiake");
       set("str", 30);
       set("int", 30);
       set("per", 30);
       set("con", 30);
       set("combat_exp", 500000);
       set("max_qi", 1000);
       set("max_jing", 1000);
       set("neili", 3600);
       set("max_neili", 1800);
       set("jiali", 90);
/*
       set("max_mana", 1800);
       set("mana", 3600);
       set("mana_factor", 90);
*/
        set("max_jingli", 500);
        set("max_neili", 500);
        set("neili", 500);
        set("jingli", 500);
        set("jiali", 500);
	set_skill("shushan-force", 150);
	set_skill("songhe-sword", 150);
       set_skill("dodge", 140);
       set_skill("literate", 100);
       set_skill("sword", 150);
       set_skill("force", 140);
       set_skill("parry", 150);
       set_skill("zuixian-steps", 140);
       map_skill("dodge", "zuixian-steps");
	map_skill("parry", "songhe-sword");
	map_skill("sword", "songhe-sword");
       map_skill("force", "shushan-force");
       create_family("ÊñÉ½ÅÉ", 3, "µÜ×Ó");
       setup();
     carry_object("/clone/cloth/cloth")->wear();
         carry_object("/clone/weapon/changjian")->wield();
//       carry_object("d/obj/weapon/sword/qinghong")->wield();
}

void attempt_apprentice(object ob)
{
	
	if (! permit_recruit(ob))
		return;
		
	if( (string)ob->query("family/family_name")=="ÊñÉ½ÅÉ" )
	{
		if( (int)ob->query("family/generation") < 3  )
		{
			if ( (string)ob->query("gender") == "ÄĞĞÔ" ) command("say Ê¦Êå¼ûĞ¦ÁË¡£\n");
			else command("say Ê¦¹Ã¼ûĞ¦ÁË¡£\n");
		}
		else if( (int)ob->query("family/generation") ==3  )
		{
			if ( (string)ob->query("gender") == "ÄĞĞÔ" ) command("say Ê¦ĞÖÌ«¿ÍÆøÁË¡£\n");
			else command("say Ê¦ÃÃÌ«¿ÍÆøÁË¡£\n");
		}
		else 
		{
			command("consider");
			command("say ÊÇÄã×Ô¼ºÒª°İµÄ£¬¿É±ğ¹ÖÎÒ°¡!¡£\n");
			command("recruit " + ob->query("id") );
		}
	}
            else
	{
		command("say ºÃ£¬ÎÒÊñÉ½ÅÉÒ»ÃÅÈË²Å±²³ö£¬Äã¿ÉµÃ¸øÊ¦¸¸ÕùÆø¡£\n");
		command("recruit " + ob->query("id") );
	}

	return;
}
int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) ) {
                ob->set("class", "xiake");
                ob->set("title", "ÊñÉ½ÅÉµÚËÄ´úµÜ×Ó");
                            }

        return 0;
}

ÿ
