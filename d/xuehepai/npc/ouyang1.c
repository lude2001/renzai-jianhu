#include <ansi.h>

inherit NPC;
inherit F_MASTER;
#include "ouyang.h"
void heal_ob();
void recover_ob();

void create()
{
        set_name("欧阳驼",({"ouyang tuo","ouyang"}));
        set("nickname",HIR"血影神掌"NOR);
        set("gender","男性");
        set("int",30);  
        set("con",30);
        set("str",130);
        set("dex",130);
        set("bac",40);
        set("age",40);
        set("attitude","peaceful");
        set("combat_exp",12000000);
        set("shen",1000);
        set("long",
"其人秉性刚烈，脸狠心慈，是个极端快意恩仇的人，无\n论好坏，他都不畏惧，更不屈服，他的才气可谓惊\n才羡艳，算得上“震古烁今，并世无双”八个字！\n"
        );
        set("neili",50000);
        set("jingli",30000);
        set("max_neili",50000);
        set("max_jingli",30000);
        set_skill("literate",400);
        set_skill("cuff",500);
        //set_skill("bow",500);
        set_skill("parry",500);
        set_skill("dodge",500);
        set_skill("wanhua-bu",500);
        set_skill("yudi-bian",500);
        set_skill("whip",500);
		set_skill("throwing",500);
        set_skill("jieniu-dao",500);
        set_skill("blade",500);
       set_skill("yiqiguan-riyue",500);
        set_skill("throwing",500);
        set_skill("youren-jian",500);
        set_skill("sword",500);
        set_skill("tianhe-jian",500);
        set_skill("force",500);
        set_skill("taoism",500);
        set_skill("feixue-quan",500);
          map_skill("force","yiqiguan-riyue");
        map_skill("cuff","feixue-quan");
        map_skill("sword","tianhe-jian");
        map_skill("blade","jieniu-dao");
        map_skill("parry","youren-jian");
        map_skill("throwing","youren-jian");
        map_skill("whip","yudi-bian");
        prepare_skill("cuff","feixue-quan");
        
       create_family("合欢宗",11,"掌门");
        setup();
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

