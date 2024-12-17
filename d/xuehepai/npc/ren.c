// made by lks

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
#include "ren.h"
void heal_ob();
void recover_ob();
int ask_me();

void create()
{
        set_name("任狂",({"ren kuang","ren"}));
        set("nickname",HIY"武林孤子"NOR);
	set("gender","男性");
	set("int",30);	
	set("con",30);
	set("str",130);
	set("dex",130);
	set("bac",40);
        set("yiqiguan_riyue",2);
	set("age",40);
	set("attitude","peaceful");
        set("combat_exp",6000000);
        set("kill",1000);
	set("long",
  "英俊潇洒,颇有大将风度。\n"
	);
        set("neili",30000);
        set("jingli",30000);
        set("max_neili",30000);
        set("max_jingli",30000);
        set_skill("literate",320);
        set_skill("cuff",380);
        set_skill("parry",380);
        set_skill("dodge",380);
        set_skill("wanhua-bu",380);
        set_skill("yudi-bian",380);
        set_skill("whip",380);
        set_skill("jieniu-dao",380);
        set_skill("blade",380);
		set_skill("throwing",300);

        set_skill("yiqiguan-riyue",380);
        //set_skill("bow",380);
        set_skill("youren-jian",380);
        set_skill("force",380);
        set_skill("taoism",340);
        map_skill("force","yiqiguan-riyue");
        map_skill("blade","jieniu-dao");
        map_skill("dodge","wanhua-bu");
        map_skill("throwing","youren-jian");
        map_skill("whip","yudi-bian");
	
       create_family("合欢宗",12,"弟子");
	setup();
       set("inquiry",([
            "血河车" : (: ask_me :),
       ]));
        carry_object("/clone/weapon/gangdao")->wield();
	carry_object("/clone/misc/cloth")->wear();
        set("chat_chance", 2);
	set("chat_msg", ({
		(: heal_ob :),
	}));
	set("chat_chance_combat", 30);
	set("chat_msg_combat", ({
                (: exert_function, "zhibiao" :),
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

int ask_me()
{
           mapping fam;

           object me=this_player();

           fam=(mapping)me->query("family");

           if (!fam || fam["family_name"]!="合欢宗")
           {
                  command("say 你与本派并无瓜葛，此话从何说起？");
                  return 1;
           }
           
           if (!(present("xuehe che",environment(me))))
           {
                 command("say 血河车已经被取走了。");
                 return 1;
            }
            
            if (me->query("combat_exp")>8000000) {
                        command("say 好吧，你把血河车开走吧。");
                        me->set_temp("ask1",1);
                        return 1;
            }
            else {
                        command("say 你的经验不够，别把血河车给弄丢了。");
                        return 1;
            }

}

