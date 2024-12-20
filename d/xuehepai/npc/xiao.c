// made by lks

#include <ansi.h>
#include "xiaojob.h"

inherit NPC;
inherit F_MASTER;
int ask_me();
int ask_job();
#include "xiao.h"
#include "cloth.h"
void heal_ob();
void recover_ob();

void create()
{
        set_name("萧萧天",({"xiao xiaotian","xiao"}));
        set("nickname",HIR"幽冥血奴"NOR);
	set("gender","男性");
	set("int",30);	
	set("con",30);
	set("str",30);
	set("dex",30);
	set("bac",40);
	set("age",40);
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
        set_skill("literate",100);
        set_skill("cuff",150);
        set_skill("parry",250);
        set_skill("dodge",250);
        set_skill("wanhua-bu",250);
        set_skill("tianhe-jian",250);
        set_skill("sword",250);
        set_skill("force",250);
        set_skill("taoism",200);
        set_skill("feixue-quan",250);
        set_skill("throwing",250);
        set_skill("huaxue-shenzhen",250);
        set_skill("huaxue-dafa",250);
        map_skill("force","huaxue-dafa");
        map_skill("dodge","wanhua-bu");
        map_skill("cuff","feixue-quan");
        map_skill("sword","tianhe-jian");
        map_skill("throwing","huaxue-shenzhen");
        prepare_skill("cuff","feixue-quan");
	
       create_family("合欢宗",13,"弟子");
	setup();
	carry_object("/clone/misc/cloth")->wear();
	carry_object("/clone/weapon/gangdao")->wield();
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
              "血翼" : (: ask_me :),
              "任务" : (: ask_job :),
       ]));
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
           object ob;
           mapping fam;

           object me=this_player();

           fam=(mapping)me->query("family");

           if (!fam || fam["family_name"]!="合欢宗")
           {
                  command("say 你与本派并无瓜葛，此话从何说起？");
                  return 1;
           }
           else if (fam["master_id"]!="xiao xiaotian")
           {
                  command("say 你不是我的弟子。");
                  return 1;
           }
           if (me->query("combat_exp")<2000000)
           {
                  command("say 你的实战经验太低了。");
                  return 1;
           }
             if (me->query("max_neili")<300)
           {
                  command("say 你的内力修为太低了。");
                  return 1;
           }
	if (query("yi"))
	{
		command("say 血翼已经被拿走了。");
		return 1;
	}
	command("say 好吧，我把血翼交给你。");
	set("yi",1);
	ob=new("/d/xuehepai/obj/xueyi");
	ob->move(me);
	return 1;
}

int ask_job()
{
        object me;
        object ob;
        mapping myfam;
        me=this_player();

        myfam=me->query("family");
        
        if ( !myfam || myfam["family_name"] != "合欢宗" )
        {
                command("say "+RANK_D->query_respect(me)+"不是我合欢宗的弟子，我们又怎敢劳烦您呢？");
                return 1;
        }
        
        if (me->query_temp("job_start"))
        {
                command("say 你已经有工作了，还不快去！");
                return 1;
        }
        
          if (me->query("combat_exp")>40000000)
        {
                command("say "+RANK_D->query_respect(me)+"你是时候练武功了，这些小事就不用麻烦你了。");
                return 1;
        }
        
        tell_object(me,"好吧,听说后山山道上的石头材质不错！\n");
        tell_object(me,"你去搬一块回来，我要做一些东西！\n");
         if (!(ob=present("hammer",me)))
         {
         ob=new("/d/xuehepai/obj/hammer");
         ob->move(me);
           }
        me->set_temp("job_start",1);
        return 1;
}


