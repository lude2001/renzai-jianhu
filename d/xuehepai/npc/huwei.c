

inherit NPC;
int ask_me();
#include <ansi.h>
void create()
{
        set_name("护卫", ({ "hu wei", "wei"}) );
        set("gender", "男性" );
        set("age", 22);
//      set("title", "合欢宗");
        set("long",
                "这位人物正笑咪咪地看着你。\n");
        set("combat_exp", 200000);
        set("attitude", "friendly");
        set("yiqiguan-riyue",1);
        
        set("max_neili",20000);
        set("neili",20000);
        set("max_qi",20000);
        set("eff_qi",20000);
        set("qi",20000);
        set("max_jingli",20000);
        set("eff_jingli",20000);
        set("jingli",20000);
        
        set_skill("force",300);
        set_skill("dodge",300);
        set_skill("parry",300);
        set_skill("blade",300);
        set_skill("cuff",300);
        set_skill("yiqiguan-riyue",300);
         set_skill("huaxue-dafa",300);
        set_skill("wanhua-bu",300);
        set_skill("jieniu-dao",300);
		set_skill("taoism",70);
        set_skill("literate",300);
        set_skill("feixue-quan",300);
        
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
        set("inquiry",([
                "询问" : (: ask_me :),
        ]));

}

void init()
{       
        object ob;

        ::init();
          if( interactive(ob = this_player()) && !is_fighting() && this_player()->query_temp("xhjob_start") ) {
                   command("sweat");
                   write("快来，我都忙不过来了。快来守(shouwei)住这里，不能让江湖人士通过。\n");
              }
}


int ask_me()
{
                object me;
                mapping family;

                me=this_player();
                family=(mapping)me->query("family");

                if ( !family || family["family_name"]!="合欢宗")      return 0;
                if ( me->query_temp("xhjob_start") || me->query_temp("shouwei") )  {
                command("poor "+me->query("id"));
                command("say 好吧！"+me->query("name")+"你走吧。");
                me->add("combat_exp",-(me->query("combat_exp")/1000));
                me->add("potential",-(me->query("potential")/1000));
                me->delete_temp("shouwei");
                me->delete_temp("xhjob_start");
                if (environment(me)->query("renshu"))  environment(me)->add("renshu",-1);
                return 1;
                }
                return 0;
}


