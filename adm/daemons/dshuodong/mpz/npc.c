inherit NPC;

void create()
{
	set_name("����", ({"ceshi"}));
	set("long", "��������ͦ���ġ�\n");
	set("combat_exp", 10000);
	
	set("max_qi", 3000);
	set("qi", 3000);
	set("max_jing", 2500);
	set("jing", 2500);
	
	set("str", 20);
	set("con", 20);
	set("int", 20);
	set("dex", 20);

	set_skill("unarmed", 100);
	set_skill("dodge", 100);
	set_skill("parry", 100);
	set_skill("blade", 100);
	set_skill("force", 100);
	
	set_temp("apply/attack", 100);
	set_temp("apply/defense", 100);
	set_temp("apply/damage", 100);
	set_temp("apply/armor", 100);
	setup();
}

void init()
{
	add_action("do_check", ({"kill", "fight", "touxi", "fuhuo"}));
}

int do_check(string arg)
{
	object who = this_player();
	if (who->query("family/family_name") == this_object()->query("family/family_name") && this_object()->query("id") == arg)
	{
		write("����ͬ�ţ����뱳��ʦ�ţ�\n");
		return 1;
	}
	return 0;
}

void die()
{
	object who = this_object()->query_last_damage_from();
	object gift;
	
	who->add("combat_exp", 500);
	who->add("potential", 500);
	gift = new("/d/fuben_jiaofei/obj/butian_suipian");
	//gift->set_amount(1);
	gift->move(who);
	tell_object(who, "���ɱ��" + this_object()->name() + "����ò���ʯ��Ƭ�ͻ��500����Ǳ�ܡ�\n");
	::die();
}