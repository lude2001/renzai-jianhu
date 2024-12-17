// tangque.c ��ȱ

#include <ansi.h>
#include "tangmen.h"

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("��ȱ", ({ "tang que", "tang", "que" }));
	set("long",
		"�������ŵڶ��������еĽܳ����\n");
	set("gender", "����");
	set("age", 40);
	set("attitude", "heroism");
	set("shen_type", 1);
	set("str", 32);
	set("int", 30);
	set("con", 30);
	set("dex", 32);

	set("max_qi", 1000);
	set("max_jing", 3000);
      set("max_jingli", 2000);
	set("neili", 3000);
	set("max_neili", 3000);
	set("jiali", 100);
	set("combat_exp", 1500000);
	set("level", 45);
	set("score", 200000);

        set_skill("force", 180);
        set_skill("throwing", 180);
        set_skill("dodge", 180);
        set_skill("parry", 180);
        set_skill("literate", 180);
        set_skill("hand", 180);
        set_skill("sword", 180);
        set_skill("boyun-suowu", 180);
        set_skill("biyun-xinfa", 180);
        set_skill("qiulin-shiye", 180);
        set_skill("wuzhan-mei", 180);
        set_skill("medical", 108);
        set_skill("poison", 180);
        set_skill("tangmen-throwing", 180);
        set_skill("tangmen-poison", 180);
        set_skill("tangmen-medical", 180);

        map_skill("force", "biyun-xinfa");
        map_skill("throwing", "tangmen-throwing");
        map_skill("dodge", "qiulin-shiye");
        map_skill("parry", "boyun-suowu");
        map_skill("sword", "wuzhan-mei");
        map_skill("hand", "boyun-suowu");
        map_skill("medical", "tangmen-medical");
        map_skill("poison", "tangmen-poison");

        prepare_skill("hand", "boyun-suowu");


        create_family("��������", 2, "��ϵ����");
	set("class", "tangmen");

        set("chat_chance_combat", 20);
        set("chat_msg_combat", ({
        	(: exert_function, "recover" :),
        	(: exert_function, "powerup" :),
        	// ( : command("wield all") : ),
        	(: perform_action, "throwing.san" :),   
        }) );

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob", 3);
	setup();
        carry_object("/clone/misc/cloth")->wear();
        set_temp("handing", carry_object("/d/tangmen/obj/jili"));
        carry_object("/d/tangmen/obj/feidao");
}

void init()
{
	::init();
	remove_call_out("greeting");
	call_out("greeting", 1, this_player());
}


void greeting(object ob)
{
	mapping fam;
        int i ;
	object me;
	object* obj;

	if (! objectp(ob))
	    return;

	me = this_object();
	if (interactive(ob)
	&& !environment(ob)->query("no_fight"))
	{
 	     if (!(fam = ob->query("family")) || fam["family_name"] != "��������")
		{
                   if (ob->query("shen")>-100)
			{
			command("say �������������ã���Ҫ����������߶�");
			obj = all_inventory(environment(me));
			for(i=0; i<sizeof(obj); i++)
			{
			if(obj[i]==this_player()) continue;
			if(obj[i]==me) continue;
			if((obj[i]->query("shen")<-100))
			{
				command("say ����޺�����Ϊ���󱲣����ҽ�����������!!");
				me->kill_ob(obj[i]);
				obj[i]->kill_ob(me);
			}
			}
			}

	   else{
			command("say һ��Ҫɱ�����⽭�����࣡");
			me->set_leader(ob);
			remove_call_out("kill_ob");
			call_out("kill_ob", 1, ob);

			}

		}
	}

}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

	if ((int)ob->query("shen") < 5000 )
	 {
		command("say ����ͽ��ע�ص��У�");
		command("say �ڵ��з��棬" + RANK_D->query_respect(ob) +
			"�Ƿ����ò�����");
		return;
	}

	if ((int)ob->query_skill("biyun-xinfa", 1) < 120) {
		command("say ������Ȼ�԰���Ϊ����������Ҫ����������");
		command("say " + RANK_D->query_respect(ob) +
			"�Ƿ�Ӧ���ڱ����ķ��϶��µ㹦��");
		return;
	}
	if (ob->query("int") < 25) {
		command("say ��������ע�ص��ӵ���ѧ��Ϊ��");
		command("say ���ɹ���Ҫ���������ã��������������������Զ�⾳�����Բ����ǲ��еġ�");
		command("say " + RANK_D->query_respect(ob) + "�����Ի�����Ǳ�����ڣ�������ذɡ�");
		return;
	}
	command("say ���������Ҿ������㣬��ס�Ժ�Ҫ�ڽ�����������ร�");
	command("recruit " + ob->query("id"));
}