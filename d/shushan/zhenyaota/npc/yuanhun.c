//Cracked by Roath
//【蜀山剑派】dhxy-evil 2000.7.5
#include <ansi.h>
inherit NPC;

void create()
{
        set_name("冤魂", ({ "yuan hun", "yuanhun" }));
        set("title", "蜀山前辈");
        set("race","人类");
        set("age", 99);
        set("attitude", "aggressive");
        set("str", 40);
        set("int", 25);
        set("con", 40);
        set("cor", 40);
        
        set("max_qi", 20000);
        set("max_jing", 20000);
        set("neili", 30000);
        set("max_neili", 20000);
        set("jiali", 60);
        set("combat_exp", 50000000);
         set("max_neili", 70000);
         set("max_jingli", 70000);
         set("jingli", 70000);
         set("jiali", 7000);
         set("neili", 7000);

        set_skill("force", 150);
        set_skill("dodge", 150);
        set_skill("parry", 150);
        set_skill("sword", 150);
        set_skill("taiji-shengong", 150);
        set_skill("zuixian-steps", 150);
        set_skill("yujianshu",150);
        map_skill("dodge", "zuixian-steps");
        map_skill("force", "taiji-shengong");
        map_skill("parry", "yujianshu");
        map_skill("sword", "yujianshu");
        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
        }) );
   add_temp("apply/damage", 20);
   add_temp("apply/armor", 20);

        setup();
        carry_object("/clone/cloth/cloth")->wear();
          carry_object("/clone/weapon/changjian")->wield();

}

void die()
{
        object me = this_object()->query_last_damage_from();
        object ob = new("/d/shushan/zhenyaota/obj/qxsword");
        ob->move(environment(me));

        if( environment() ) {
        message("sound", CYN"\n冤魂散了...", environment());
        message("sound", "\n一个神秘女孩出现在烟雾里...", environment());
        message("sound", "\n女孩道：“几十年了，父亲终于可以安息了，这把七星剑就送给你啦。”", environment());
        message("sound", "\n女孩说完消失在迷雾中...\n"NOR, environment());
        }
        destruct(this_object());
}
