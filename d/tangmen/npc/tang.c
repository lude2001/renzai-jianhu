// tang.c ����̫̫

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
string ask_me();
void create()
{
	set_name("����̫̫", ({ "tang laotai", "tang" }));
	set("nickname", HIW "��������" NOR);
	set("long", 
		"���������ŵ�������������̫̫�������ľ�Ӫ�£�\n"
		"�����ڽ��������������Ժա�\n"
		"����Լ��ʮ���࣬һͷ������������档\n");
	set("gender", "Ů��");
	set("age", 70);
	set("attitude", "friendly");
	set("shen_type", 1);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	
	set("max_qi", 15000);
	set("max_jing", 13000);
	set("neili", 80000);
	set("max_neili", 80000);
	set("jiali", 100);
	set("combat_exp", 6000000);
	set("score", 600000);

	set_skill("force", 350);
	set_skill("biyun-xinfa", 300);
	set_skill("dodge", 350);
	set_skill("qiulinshiye", 300);
	set_skill("strike", 250);
	set_skill("unarmed",280);
	set_skill("biye-wu", 300);
	set_skill("parry", 280);
	set_skill("throwing", 350);
	set_skill("zimu-zhen", 350);
	set_skill("literate", 250);
	map_skill("force", "biyun-xinfa");
	map_skill("dodge", "qiulinshiye");
	map_skill("strike", "biye-wu");
	map_skill("unarmed","biye-wu");
	map_skill("parry", "zimu-zhen");
	map_skill("throwing", "zimu-zhen");
	
	create_family("����", 6, "����");
	set("class", "tangmen");

	set("chat_chance_combat", 90);
	set("chat_msg_combat", ({
		(: perform_action, "throwing.poqizhen" :),
		(: perform_action, "throwing.dinhun" :),
                (: perform_action, "throwing.qizigangbiao" :),
                (: perform_action, "throwing.tanghua" :),
		(: perform_action, "strike.wandu" :),
		(: perform_action, "strike.meng" :),
		(: exert_function, "recover" :),
	}) );
	set("inquiry", 
		([
			"��������" : (: ask_me :)
		]));

	setup();
	add_money("zimuzhen",300);
	carry_object("/d/tangmen/obj/zimuzhen")->wield();
	carry_object("/d/tangmen/obj/shujin")->wear();
}

void attempt_apprentice(object ob)
{
	if ((int)ob->query_skill("biyun-xinfa", 1) < 200) {
		command("say ������Ȼ�԰���Ϊ����������Ҫ����������"); 
		command("say " + RANK_D->query_respect(ob) + 
			"�Ƿ�Ӧ���ڱ����ķ��϶��µ㹦��");
		return;
	}
	if (ob->query_int() < 30) {
		command("say ��������ע�ص��ӵ���ѧ��Ϊ��");
		command("say ���ɹ���Ҫ���������ã��������������������Զ�⾳�����Բ����ǲ��еġ�");
		command("say " + RANK_D->query_respect(ob) + "�����Ի�����Ǳ�����ڣ�������ذɡ�");
		return;
	}
	if ((int)ob->query_skill("biye-wu", 1) < 200)
        {
        command("say ��ı�Ҷ�������̫ǳ��"); 
        return 0;
        }
	if ((int)ob->query_skill("qiulinshiye", 1) < 200)
{
command("say ��ı����Ṧ���̫ǳ��"); 
        return 0;
}
	if ((int)ob->query_skill("pili-biao", 1) < 200)
{
command("say ��������ڻ��̫ǳ��"); 
        return 0;
}
	if ((int)ob->query_skill("liuxing-biao", 1) < 200)
{
command("say ������Ǹ����ڻ��̫ǳ��"); 
        return 0;
}
	if ((int)ob->query_skill("zhuihun-biao", 1) < 200)
{
command("say ���׷������ڻ��̫ǳ��"); 
        return 0;
}
	command("say ����������������");
	command("say �����ֶ���һ�������˲ţ����ǿ�ϲ�ɺء�");
	command("recruit " + ob->query("id"));
}
string ask_me()
{object me;
me =this_player();
	if (me->query_temp("marks/��")){
		command("say ������Ʒ��Ǹ���Ѿͷ��̽��Ϣ�𣿿��Ҳ�������");
		command("hit " + me->query("id"));
		return "������̫�ŷǵý�ѵ��һ�²��ɡ�\n";}
       if (me->query_temp("marks/��")){
	command("angry " + this_player()->query("id"));
	command("say �ѵ�����������ˮһ����������������\n");
	command("heng " + this_player()->query("id"));
	command("say �Ʒ��Ǹ���Ѿͷ��\n");
	this_player()->set_temp("marks/��",1);
	me->delete_temp("marks/��");
	return"����ˮ�ѱ��ҹ������ˣ��������ټ��������С���ˣ�\n";
							}
else{ 	
	return "�����ӣ���˵ɶ�ӣ���̫��������Ŷ��\n";
    }


}