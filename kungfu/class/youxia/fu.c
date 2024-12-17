#include <ansi.h>
inherit NPC;
#include "youxia.h"
void create()
{
        set_name("傅寒雪", ( { "fu hanxue", "fu" }) );
        set("title", HIB"通神天刀"NOR);
        set("gender", "男性" );
        set("age", 60);
        set("long","照影明月宫当代宫主，历代宫主中唯一将“九幽通神法”练至“意接天地，神我九合”的境界。
        年少时周游江湖，对萧无极一见倾心，其身上照影青袍便是傅寒雪亲手所织。然而萧无极情定秦化蝶，心灰意冷之下归隐明月宫中钻研武道，再不履江湖。
        傅寒雪身怀“九幽通神法”与“天意问玄刀”，可谓天底下武功最高、美貌最绝、权势最盛之女子。以神驭刀，天意为招，神我相合，问玄斩道。\n");

        set("int", 300);
        set("str", 250);
        set("con", 300);
        set("dex", 250);
        set("per",35);
        set("no_get",1);
        set("youxia_skill","jiuyoufa");

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