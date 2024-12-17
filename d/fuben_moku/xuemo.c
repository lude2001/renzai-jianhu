inherit NPC;

void end_fuben(object me);
void xuemo_pfm();
#include "fuben_init_skills.h"

void create()
{
	set_name("Ѫħ", ({"xue mo", "mo"}));
	set("long", "ħ���в�����Ѫħ��");
	set("combat_exp", 100000);
	set("shen",-10000);
	
	set("max_qi", 3000000);
	set("qi", 3000000);
	set("max_neili", 20000);
	set("neili", 20000);
	set("max_jing", 10000);
	set("jing", 10000);
	
	set("chat_chance_combat", 120);
	
	set_temp("apply/attack", 150);
	set_temp("apply/defense", 150);
	set_temp("apply/damage", 100);
	set_temp("apply/unarmed_damage", 100);
	set_temp("apply/armor", 200);

	setup();
}

void init()
{
    object * player;
    
    if (sizeof(player = filter_array(all_inventory(environment(this_object())), (: userp($1) :))))
    {
        if (sizeof(player))
            kill_ob(player[0]);
    }
}


void die()
{
	object me, who, gift, ob;
	
	me = this_object();
	who = environment(this_object())->query("player");
	
	if (!userp(who))
	{
	    write(query("xuemo") + "��������ϵ����Ա����\n");
	    ::die();
	}
	
	if (me->query("xuemo") >= 100)
	{
		gift = new("/clone/money/silver");
		gift->set_amount(1000);
		gift->move(who);
		gift = new("/d/fuben_jiaofei/obj/butian_suipian");
		gift->set_amount(5);
		gift->move(who);
		who->add("yuanbao", 10);
		who->add("combat_exp", 1000);
		who->add("potential", 1000);
		tell_object(who, "��ϲ���������ħ����ս�������10Ԫ����5������Ƭ��10�����ӣ�1000Ǳ�ܺ;��顣\n");
		__DIR__"moku"->restore_status(who);
		who->move("/d/city/guangchang");
		::die();
	}
	else
	{
    	init_npc(me, (ob = new(__FILE__)));
    	ob->move(environment(this_object()));
    	
		gift = new("/clone/money/silver");
		gift->set_amount(50);
		gift->move(who);
		who->add("yuanbao", 1);
		who->add("combat_exp", 100);
		who->add("potential", 200);
    	tell_object(who, "���ɱ��Ѫħ���1Ԫ����50�����ӣ�100�����200Ǳ�ܡ�\n");
    	::die();
	}
}

void xuemo_pfm()
{
    object who = select_opponent();
    tell_object(who, "Ѫħ����һ���ֺ�������˺ҧ��\n");
    if (random(2))
    {
        tell_object(who, "�㱻Ѫħҧ���ˣ��˿ڿ�ʼ��ԡ�\n");
        who->start_busy(3);
    	who->affect_by("xuedu",
    		       ([ "level" : 200,
    			  "id"    : query("id"),
    			  "duration" : 100,]));
    }
    else
    {
        tell_object(who, "�����Ա�һ�㣬Ѫħ���˸��ա�\n");
    }
}