

inherit NPC;
inherit F_MASTER;
#include <ansi.h>
#include "newbie.h"
void create()
{
        set_name("管事", ({ "guan shi","guan", "shi"}) );
        set("gender", "男性" );
        set("age", 22);
//      set("title", "合欢宗");
        set("long",
                "这位人物正笑咪咪地看着你。\n");
        set("combat_exp", 2000000);
        set("attitude", "peaceful");
        set("yiqiguan-riyue",1);
        
        set("max_neili",2000);
        set("neili",2000);
        set("max_qi",2000);
        set("eff_qi",2000);
        set("qi",2000);
        set("max_jingli",2000);
        set("eff_jingli",2000);
        set("jingli",2000);
        
        set_skill("force",100);
        set_skill("dodge",100);
        set_skill("parry",100);
        set_skill("blade",100);
        set_skill("cuff",100);
        set_skill("yiqiguan-riyue",100);
         set_skill("huaxue-dafa",100);
        set_skill("wanhua-bu",100);
        set_skill("jieniu-dao",100);
   set_skill("taoism",70);
        set_skill("literate",100);
        set_skill("feixue-quan",100);
        
        map_skill("force","yiqiguan-riyue");
        map_skill("dodge","wanhua-bu");
        map_skill("cuff","feixue-quan");
        map_skill("parry","jieniu-dao");
        map_skill("blade","jieniu-dao");
        
        prepare_skill("cuff","feixue-quan");
        
        create_family("合欢宗",14,"弟子");
        setup();

        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/gangdao")->wield();
        add_money("silver",20);
        set("chat_chance",1);
        set("chat_msg",({
                (: exert_function, "heal" :),
        }));
        set("chat_chance_combat",30);
        set("chat_msg_combat",({
                (: exert_function, "recover" :),
        }));
}

void init()
{       
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() && (this_player()->query("family/family_name")!="合欢宗")) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        say( "管事笑咪咪地说道：这位" + RANK_D->query_respect(ob)
                                + "，是来拜师的吧？拜我吧！\n");
}

