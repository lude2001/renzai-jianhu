#include <ansi.h>
inherit NPC;
#include "youxia.h"

void create()
{
        set_name("萧无极", ( { "xiao wuji", "xiao" }) );
        set("title", HIB"炁宗剑极"NOR);
        set("gender", "男性" );
        set("age", 60);
        set("long","天下不世出的内炁宗师，爱妻早逝，葬于云梦泽畔，结庐而守。渔居二十载，自悟“涵虚混元气”与“截天七剑”两大奇功。
        曾与“天下第一狂人”燕狂徒结为挚友，斗酒三日、斗炁三日、斗拳掌兵器三日，尽皆胜之。
        “截天七剑”威势无双，但必须以“涵虚混元气”催动，否则将如无根之水难以久持。。\n");

        set("int", 300);
        set("str", 250);
        set("con", 300);
        set("dex", 500);
        set("per",35);
        
        set("no_get",1);
        set("youxia_skill","hanxueqi");
        
        set_temp("apply/attack", 1000);
        set_temp("apply/defense", 1000);
        set_temp("apply/damage", 1000);
        set("qi",200000);
        set("max_qi", 200000);
        set("jing", 200000);
        set("max_jing", 200000);
        set("neili", 100000);
        set("max_neili", 100000);
        set("jiali", 300);
        set("combat_exp", 30000000);
        set("score", 250000);

        set_skill("force", 3000);
        set_skill("taixuan-gong", 3000);
        set_skill("dodge", 3000);
        set_skill("tiyunzong", 3000);
        set_skill("unarmed", 3000);
        set_skill("taiji-quan", 3000);
        set_skill("parry", 3000);
        set_skill("taoism", 2000);
        set_skill("literate", 1000);

        map_skill("force", "taixuan-gong");
        map_skill("dodge", "taixuan-gong");
        map_skill("unarmed", "taixuan-gong");
        map_skill("parry", "taixuan-gong");
        
        set("inquiry", ([
                "奥妙" :  "须知修武不诚，如同逆水行舟,这便是奥妙。\n",
                "传武" : (:xue_skill:),
            ]));

        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("gold",1);
}