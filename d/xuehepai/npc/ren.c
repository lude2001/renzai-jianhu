// made by lks

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
#include "ren.h"
void heal_ob();
void recover_ob();
int ask_me();

void create()
{
        set_name("�ο�",({"ren kuang","ren"}));
        set("nickname",HIY"���ֹ���"NOR);
	set("gender","����");
	set("int",30);	
	set("con",30);
	set("str",130);
	set("dex",130);
	set("bac",40);
        set("yiqiguan_riyue",2);
	set("age",40);
	set("attitude","peaceful");
        set("combat_exp",6000000);
        set("kill",1000);
	set("long",
  "Ӣ������,���д󽫷�ȡ�\n"
	);
        set("neili",30000);
        set("jingli",30000);
        set("max_neili",30000);
        set("max_jingli",30000);
        set_skill("literate",320);
        set_skill("cuff",380);
        set_skill("parry",380);
        set_skill("dodge",380);
        set_skill("wanhua-bu",380);
        set_skill("yudi-bian",380);
        set_skill("whip",380);
        set_skill("jieniu-dao",380);
        set_skill("blade",380);
		set_skill("throwing",300);

        set_skill("yiqiguan-riyue",380);
        //set_skill("bow",380);
        set_skill("youren-jian",380);
        set_skill("force",380);
        set_skill("taoism",340);
        map_skill("force","yiqiguan-riyue");
        map_skill("blade","jieniu-dao");
        map_skill("dodge","wanhua-bu");
        map_skill("throwing","youren-jian");
        map_skill("whip","yudi-bian");
	
       create_family("�ϻ���",12,"����");
	setup();
       set("inquiry",([
            "Ѫ�ӳ�" : (: ask_me :),
       ]));
        carry_object("/clone/weapon/gangdao")->wield();
	carry_object("/clone/misc/cloth")->wear();
        set("chat_chance", 2);
	set("chat_msg", ({
		(: heal_ob :),
	}));
	set("chat_chance_combat", 30);
	set("chat_msg_combat", ({
                (: exert_function, "zhibiao" :),
                (: recover_ob :),
	}) );
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
           mapping fam;

           object me=this_player();

           fam=(mapping)me->query("family");

           if (!fam || fam["family_name"]!="�ϻ���")
           {
                  command("say ���뱾�ɲ��޹ϸ𣬴˻��Ӻ�˵��");
                  return 1;
           }
           
           if (!(present("xuehe che",environment(me))))
           {
                 command("say Ѫ�ӳ��Ѿ���ȡ���ˡ�");
                 return 1;
            }
            
            if (me->query("combat_exp")>8000000) {
                        command("say �ðɣ����Ѫ�ӳ����߰ɡ�");
                        me->set_temp("ask1",1);
                        return 1;
            }
            else {
                        command("say ��ľ��鲻�������Ѫ�ӳ���Ū���ˡ�");
                        return 1;
            }

}

