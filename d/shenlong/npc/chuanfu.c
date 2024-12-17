// chuanfu.c �ϴ���

#include <ansi.h>

inherit NPC;
int  chu_hai();
void goto_dao(object ob);

void create()
{
	set_name("�ϴ���", ({ "lao chuanfu","chuanfu","lao" }));
	set("gender", "����");
	set("age", 56);
	set("long", @LONG
����һ���ϴ��򡣱�����˪������͸��һ˿�ƻ�����������������˵
��ǰ����ȥ����������������ӵ��һ�Ҵ󴬿��Գ�����
LONG );

	set("combat_exp", 100000);
	set("shen_type", 1);

	set("max_qi", 5000);
	set("max_jing", 2000);
	set("neili", 1000);

	set_skill("force", 200);
	set_skill("unarmed", 400);
	set_skill("dodge", 200);
	set_skill("parry", 200);
	set("inquiry", ([
		"���ߵ�" : "���ߵ�����һ�����ˣ�ǧ����ȥ��\n",
		"������" : "����������һ�����ˣ�ǧ����ȥ��\n",
		"����" :   (: chu_hai :),
	]));

	setup();
	carry_object("/clone/misc/cloth")->wear();
}

int chu_hai()
{
  	object ob, myenv;
  	ob = this_player();
  	if (ob->query("party/party_name") == "������")
  	{
		message_vision("�ϴ���һ���֣������������ᴬ��\n", ob);
		message_vision("���ᴬ���$N���˴���һ������ê�����Ϳ����ˣ���"
		       	       "�ϴ���ȴû�ϴ�......\n", ob);
		myenv = environment (ob);
		ob->move ("/d/shenlong/dahai");
		tell_object(ob, BLU "���ں��Ϻ����˺ܾúܾ�......."NOR"\n");
		 call_out("goto_shenlong", random(3), ob)
;
       		return 1;
  	} else  
  		message_vision("�ϴ����������´�����$Nһ�£�ʲô����������"
			       "��Ҫ���ˣ���\n�ϴ���������һ�£�����...��"
			       "������һ�����ӣ��������Կ��ǡ�\n", ob);
  	ob->set_temp("����", 1);
  	return 1;
}

int accept_object(object who, object ob)
{
    	object myenv;
    	if (! (int)who->query_temp("����"))
    	{
		message_vision("�ϴ���Ц�Ŷ�$N˵���޹�����»����"
			       "�����Լ����Űɣ�\n", who);
		return 0;
    	}
    	if (ob->query("money_id") && ob->value() >= 10000)
	{
		message_vision("�ϴ����$N˵���ã���Ȼ��λ" +
			       RANK_D->query_respect(who) +
			       "��˿������ң�\n����Ҳƴ�������ƴ�����"
			       "������ӱ��ˣ�\n" , who);
		who->delete_temp("����" );
		message_vision("�ϴ���һ���֣������������ᴬ��\n���ᴬ"
			       "���$N���˴���һ������ê�����Ϳ����ˣ���"
			       "�ϴ���ȴû�ϴ�......\n", who);
		myenv = environment (who);
		who->move("/d/shenlong/dahai");
		tell_room(myenv, "�ϴ��򿴴����ˣ��ٺ�Ц��������\n");
		tell_object(who, BLU "���ں��Ϻ����˺ܾúܾ�......."NOR"\n");
		call_out("goto_shenlong", 10, who);
		destruct(ob);
		return -1;
	} else  
		message_vision("�ϴ�����ü��$N˵��������Ҳ̫���˰ɣ�\n", who);
	return 0;
}

void goto_shenlong(object ob)
{
	if (! objectp(ob) || find_object("/d/shenlong/dahai") != environment(ob))
		return;

   	tell_object(ob, "������ͣ����һ��С���ߡ������´�����\n");
   	ob->move("/d/shenlong/haitan");
}

void unconcious()
{
	::die();
}

varargs void die(object killer)
{
	mapping my;

	message_vision(HIR "$N" HIR "��ɫ��Ȼһ�䣬�����к�����"
		       "��������ɸ��������������룡��\n"
		       HIR "ֻ��$N" HIR "�����˵�ʱ������񣬼�����ء�"NOR"\n",
		       this_object());

	my = query_entire_dbase();
	my["eff_qi"]   = my["max_qi"];
	my["qi"]       = my["max_qi"];
	my["eff_jing"] = my["max_jing"];
	my["jing"]     = my["max_jing"];

	if (query_temp("count") < 3)
	{
		add_temp("count", 1);
		add_temp("apply/unarmed_damage", 300);
		add_temp("apply/attack", 300);
		add_temp("apply/defense", 300);
		set_skill("force", query_skill("force", 1) + 200);
	}
}