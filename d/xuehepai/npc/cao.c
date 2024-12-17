// made by lks

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
#include "xiao.h"
#include "cloth.h"
#include "caojob.h"
void heal_ob();
int ask_me();
void recover_ob();

void create()
{
        set_name("曹大悲",({"cao dabei","cao"}));
        set("nickname",RED"血雾纷飞"NOR);
	set("gender","男性");
       set("shen_type",-1);
	set("int",30);	
	set("con",30);
	set("str",30);
	set("dex",30);
	set("bac",40);
        set("book",1);
        set("age",30);
	set("attitude","peaceful");
        set("combat_exp",5000000);
        set("shen",1000);
	set("long",
"英俊潇洒,但始终看不破一个情字，最后也殉情了。\n"
	);
        set("neili",20000);
        set("jingli",18000);
        set("max_neili",20000);
        set("max_jingli",18000);
        set_skill("yiqiguan-riyue",150);
        set_skill("literate",100);
        set_skill("cuff",350);
        set_skill("parry",350);
        set_skill("dodge",350);
        set_skill("wanhua-bu",350);
        set_skill("tianhe-jian",350);
        set_skill("sword",350);
        set_skill("force",350);
        set_skill("throwing",350);
        set_skill("huaxue-shenzhen",350);
        set_skill("taoism",300);
        set_skill("feixue-quan",350);
        set_skill("huaxue-dafa",350);
        map_skill("force","huaxue-dafa");
        map_skill("dodge","wanhua-bu");
        map_skill("cuff","feixue-quan");
        map_skill("throwing","huaxue-shenzhen");
        map_skill("sword","tianhe-jian");
        prepare_skill("cuff","feixue-quan");
	
       create_family("合欢宗",13,"弟子");
	setup();
	carry_object("/clone/misc/cloth")->wear();
        set("chat_chance", 2);
	set("chat_msg", ({
		(: heal_ob :),
	}));
	set("chat_chance_combat", 30);
	set("chat_msg_combat", ({
                (: exert_function, "xisui" :),
                (: exert_function, "xuewu" :),
                (: recover_ob :),
	}) );
       set("inquiry",([
              "job" : (: ask_job :),
       ]));
}

	
void heal_ob()
{
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
           object ob;
           mapping fam;

           object me=this_player();

           if (!me->query("family") || me->query("family/family_name")!="合欢宗")
           {
                  command("say 你与本派并无瓜葛，此话从何说起？");
                  return 1;
           }
            if (!query("book"))
            {
                 command("say 秘籍已经被拿走了。");
                 return 1;
            }
                  command("say 好吧，这几本书你拿去好好研究一下。");
                   set("book",0);
                   if (me->query("combat_exp")>100000) {
                  ob=new("/d/xuehepai/obj/miji");
                  ob->move(me);
                   }
				   //有问题
                  //ob=new("/d/book/changbian");
                  //ob->move(me);
                  return 1;
}

