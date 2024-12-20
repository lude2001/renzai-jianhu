// qi.c 戚长发

#include <ansi.h>
#include <command.h>

inherit NPC;
inherit F_DEALER;

int do_answer();

void create()
{
	set_name("唐兵兵", ({ "tang bingbing", "tang", "bingbing" }) );
	set("title",HIC "唐门暗器专卖店   店主" NOR);

	set("gender", "男性");
	set("age", 48);
	set("str", 100);
	set("long",
		"这是唐门专门卖兵器的小伙子，祖传的暗器专卖店的负责人。\n");
	set_skill("unarmed", 50);
	set_skill("dodge", 50);
	set_skill("higgling", 50);	
	set_temp("apply/damage", 15);

	set("combat_exp", 800000);
	set("attitude", "friendly");

	set("vendor_goods", ([
                "/d/tangmen/obj/fhshi":100,
                "/d/tangmen/obj/tiejili":100,
                "/d/tangmen/obj/feidao":100,
                "/d/tangmen/obj/qinglianzi":100,
	]));

	setup();
	set_max_encumbrance(100000000);
}

void init()
{
        add_action("do_buy", "buy");
	add_action("do_list", "list");
        add_action("do_drop", "drop");
        add_action("do_look", ({"guankan", "kan"}));
}


void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(2) ) 
        {
                case 0:
                        say( HIC"唐兵兵笑咪咪地说道：这位" + RANK_D->query_respect(ob)+ "，来买暗器啊。\n"NOR);
                        break;
                case 1:
                        say( HIG"唐兵兵搓了搓手，说道：这位" + RANK_D->query_respect(ob)+ "，想买点什么啊。\n"NOR);
                        break;
        }
}
