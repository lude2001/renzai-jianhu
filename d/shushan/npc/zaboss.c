//【蜀山派】mhxy-yushu 2001/2
inherit NPC;
inherit F_DEALER;
void create()
{
//        reload("shushan_zaboss");   
        set_name("王老板", ({"wang laoban", "laoban"}));
        set("age", 42);
        set("gender", "男性");
        set("long","杂货铺的老板，笑眯眯的看着你。\n");
	 set("title", "杂货铺老板");
  set("attitude", "friendly");
        set("combat_exp", 10000);
        set("shen_type", 1);
	 set("max_neili", 200);
	 set("neili", 200);
	 set("jiali", 5);
        set_skill("unarmed", 30);
        set_skill("dodge", 40);
        set_skill("parry", 30);
        set("vendor_goods", ([
/*
              "shoes": "/d/shushan/obj/shoe",
             "pifeng": "/d/shushan/obj/longwenpifeng",
		  "bag": "/d/obj/misc/bag",
              "cutan": "/d/obj/food/cutan",
		 "seal": "/obj/paper_seal",
*/
        ]));
        setup();
//         carry_object("/d/obj/cloth/choupao")->wear();
}
void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
		call_out("greeting",1,ob);
        }
        add_action("do_vendor_list", "list");
}
void greeting(object ob)
{
        if( !ob || !visible(ob) || environment(ob) != environment() ) return;
        switch( random(1) ) {
                case 0:
                        say( name()+"说道：这位" +
RANK_D->query_respect(ob)
                                + "，要买些什么东西？\n");
                        break;
        }
}