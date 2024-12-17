//Cracked by Roath
//【蜀山剑派】dhxy-evil 2000.7.5
//modified by hanchat@txwx2005
#include <ansi.h>
inherit NPC;

string *names = ({
 HIW "无名鬼" NOR,
  HIC"人尸"NOR,
  HIM"狐妖"NOR,
  HIG"河童"NOR,
});

void create()
{
  string str;
  set_name(names[random(sizeof(names))], ({"yao guai", "yao", "guai"}));
  set("race", "野兽");
  set("age", 100+random(201));
  set("combat_exp", 50000000+random(150000001));
  set("limbs", ({ "头部", "身体", "前爪", "尾巴", "肚皮", "后爪"}) );
  set("verbs", ({ "bite", "claw"}) );
  set("attitude", "aggressive");
  set("per", 10);
  set_skill("parry", 200);
  set_skill("unarmed", 200);
  set_skill("dodge", 200);
  set_skill("blade", 200);
  set_skill("wuhu-duanmendao", 200);	
  map_skill("parry","wuhu-duanmendao");
  
  set("max_jing",300000);
  set("max_qi",20000);
  set("neili",2000000);
  set("max_neili",15000);
  set("jiali",500);
   add_temp("apply/damage", random(2000));
  set("chat_chance_combat", 30);  
    set("chat_msg_combat", ({
           (: perform_action, "blade.duan" :),
                       }) );
  setup();
   carry_object("/clone/cloth/male-shoe")->wear();
   carry_object("/clone/cloth/male2-cloth")->wear();
   carry_object("/clone/weapon/blade")->wield();
}
/*
void die()
{

        object ob = query_temp("last_damage_from");
	 int addexp;	
addexp=random(15000);
if(ob->query("combat_exp")>1200000000)
::die();
        ob->add("combat_exp", addexp);
ob->add("potential", addexp/2);
        tell_object(ob,HIW"你赢得了"+chinese_number(addexp)+"经验"+chinese_number(addexp/3)+"潜能。\n"NOR);

       ::die();
}*/
