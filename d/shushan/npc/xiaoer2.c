//【蜀山派】mhxy-yushu 2001/2
// lilong alter 2002.01.19
inherit F_DEALER;
inherit NPC;
void create()
{ 
        set("shen_type", 1);
         set_name("店小二", ({"xiao er","xiaoer","xiao","waiter","er"}));
        set("age", 22);
        set("gender", "男性");
        set("long","这位店小二正笑咪咪地忙著，还不时拿起挂在脖子上的抹布擦脸。\n");
	 set("title", "忠厚老实");
        set("attitude", "friendly");
        set_temp("apply/damage", 10);
        set("combat_exp", 100000);
          set("max_neili", 200);
	 set("neili", 200);
        set_skill("unarmed", 30);
        set_skill("dodge", 40);
        set_skill("parry", 30);
 set("vendor_goods", ({
  "/clone/food/jiudai",
 "/clone/food/jitui",
 "/d/shushan/obj/hedinghong",
 "/d/shushan/obj/fusheyan"
 }));
      
        setup();
         carry_object("/clone/cloth/cloth")->wear();
}
void init()
{
        object ob,owner;
        string nature;
        nature=NATURE_D->room_event_fun();
        owner=this_object();
        ::init();
        if (base_name(environment())!=query("startroom")) return;
        if (interactive(ob = this_player()) && !is_fighting()) {
        	if(nature!="event_dawn"
		&& nature!="event_night"
		&& nature!="event_midnight"){
                remove_call_out("greeting");
                call_out("greeting", 1, ob);}
                else owner->command("zzz "+owner->query("id"));
        }
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
void greeting(object ob)
{
        if (!ob || environment(ob) != environment())
                return;
        switch(random(2)) {
        case 0 :
             say( "店小二笑咪咪地说道：这位" + RANK_D->query_respect(ob)
				+ "，要住店吗？请进请进。\n");
          break;
        case 1 :
               say( "店小二用脖子上的毛巾抹了抹手，说道：这位" + RANK_D->query_respect(ob)
				+ "，请进请进。小店还有几间上好的房间。\n");
	   break;
        }
}

