//Cracked by Roath
//����ɽ���ɡ�dhxy-evil 2000.7.5
//modified by hanchat@txwx2005
#include <ansi.h>
inherit NPC;

string *names = ({
 HIB "������" NOR,
  HIR"������"NOR,
  HIY"ɨ����"NOR,
  HIG"��ͷ��"NOR,
});

void create()
{
  string str;
  set_name(names[random(sizeof(names))], ({"yao guai", "yao", "guai"}));
  set("race", "Ұ��");
  set("age", 100+random(201));
  set("combat_exp", 50000000+random(50000001));
  set("limbs", ({ "ͷ��", "����", "ǰצ", "β��", "��Ƥ", "��צ"}) );
  set("verbs", ({ "bite", "claw"}) );
  set("attitude", "aggressive");
  set("per", 10);
  set_skill("parry", 200);
  set_skill("unarmed", 200);
  set_skill("dodge", 200);
  set_skill("blade", 200);
  set_skill("wuhu-duanmendao", 200);	
  map_skill("parry","wuhu-duanmendao");
  
  set("max_jing",200000);
  set("max_qi",15000);
  set("neili",2000000);
  set("max_neili",15000);
  set("jiali",500);
   add_temp("apply/damage", random(1000));
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
addexp=random(10000);
if(ob->query("combat_exp")>1200000000)
::die();
        ob->add("combat_exp", addexp);
ob->add("potential", addexp/2);
        tell_object(ob,HIW"��Ӯ����"+chinese_number(addexp)+"����"+chinese_number(addexp/3)+"Ǳ�ܡ�\n"NOR);

       ::die();
}
*/