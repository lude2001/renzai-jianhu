inherit NPC;

string *dan_list = ({
	"/clone/gift/unknowdan",
	"/clone/gift/xiandan",
	"/clone/gift/xisuidan",
	"/clone/gift/shenliwan",
	});
void create()
{
	set_name("草人", ({"cao ren"}));
	set("long", "草人。\n");
	set("combat_exp", 100000);
	set("shen",-10000);
	
	set("max_qi", 1000);
	set("qi", 1000);
	set("max_neili", 1000);
	set("neili", 1000);
	set("max_jing", 1000);
	set("jing", 1000);
	         
	set_skill("sword",100);
    set_skill("blade", 100);
    set_skill("whip", 100);
    set_skill("club", 100);
    set_skill("staff", 100);
    set_skill("throwing", 100);

    set_skill("force", 100);
    set_skill("parry", 100);
    set_skill("dodge", 100);

    set_skill("unarmed",100);
    set_skill("cuff", 100);
    set_skill("strike", 100);
    set_skill("finger", 100);
    set_skill("claw", 100);
    set_skill("hand", 100);

	setup();
}

void die()
{
	object who = this_object()->query_last_damage_from();
	string str;
	object gift;
	int random;
	
	str = "你获得了";
	random = random(10);
	if(random < 3)
		gift = new("/u/cx/luck/putao");
	else if(random == 5)
		gift = new("/clone/baiyi/onecard");
	else if(random == 4)
	{
		gift = new(dan_list[random(sizeof(dan_list))]);
	}
	if (objectp(gift)&&objectp(who))
	{
		str += gift->query("name") + "、";
		gift->move(who);
	}
	who->add("combat_exp", 250);
	who->add("potential", 250);
	str += "250经验和潜能。\n";
	tell_object(who, str);
	::die();
}