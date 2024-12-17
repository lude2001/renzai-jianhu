#include <ansi.h>
inherit NPC;
#include "youxia.h"
void create()
{
        set_name("秦化仙", ( { "qin huaxian", "qin" }) );
        set("title", HIB"神鬼莫测"NOR);
        set("gender", "男性" );
        set("age", 60);
        set("long","京都秦氏当代家主的长兄，本是家主继承人，因醉心武道放弃家主之位，远游江湖。
        平生最是疼爱小妹秦化蝶，秦化蝶重病时踏遍江湖为其寻得“医邪”天不孤的踪迹。怎奈晚归一日，秦化蝶终是重病不治而去。对傅寒雪有着难言的情愫，可惜傅寒雪心伤之后再无意情爱之事，终是不得眷侣。
        秦化仙身怀玄天無相诀与殛神枪法，更是天底下一等一的聪明人，其天资之高，可谓冠绝古今。\n");

        set("int", 300);
        set("str", 250);
        set("con", 300);
        set("dex", 250);
        set("per",35);
        set("no_get",1);
        set("youxia_skill","xuantianjue");

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