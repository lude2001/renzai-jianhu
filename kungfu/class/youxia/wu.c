#include <ansi.h>
inherit NPC;
#include "youxia.h"
int ask_zhou();

void create()
{
        set_name("武鼎言", ( { "wu dingyan", "wu" }) );
        set("title", HIB"九鼎武宗"NOR);
        set("gender", "男性" );
        set("age", 60);
        set("long","“武道称雄，一言九鼎”，这是江湖人对武鼎言最好的诠释。
        如果你没有朋友，请找武鼎言，他会是你最忠诚的朋友；如果你没人了解，请找武鼎言，他会是你最好的知音；如果你惹上麻烦，请找武鼎言，因为他可以为你解决一切疑难。
        武鼎言乃关陇武家当代家主，萧无极、傅寒雪、秦化仙均视他为至交好友。身负真武化劫经跟九鼎神掌两大绝学。以真武罡劲催发九鼎神掌，可谓天下第一流的空手武学，灵妙超越六脉，刚猛更胜降龙。\n");

        set("int", 300);
        set("str", 250);
        set("con", 300);
        set("dex", 250);
        set("per",35);
        set("no_get",1);
        set("youxia_skill","zhenwujing");

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