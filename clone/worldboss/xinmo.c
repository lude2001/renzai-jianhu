// cui.c ��Ա��

inherit NPC;

void create()
{
	set_name("��ħ", ({ "xin mo", "mo" }));
	set("gender", "����");
	set("age", 55);

	set("max_qi",500);
	set_skill("unarmed", 50);
	set_skill("dodge", 50);
	set_skill("parry", 50);
	set_temp("apply/attack", 40);
	set_temp("apply/defense", 40);
	set_temp("apply/damage", 10);

	set("combat_exp", 25000);
	set("shen_type", -1);
	setup();
	add_money("silver", 5);
	carry_object("/clone/misc/cloth")->wear();
}
	
void die()
{
        object nvh;
         object ob =  this_object()->query_last_damage_from();
            object *players,wp;
         int w,x,i;         
        ob->start_busy(1); 
        if (!sizeof(players = ob->query_team()))
        {
        wp = new("/clone/vip/jinsha");
        wp->set_amount(20);
        wp->move(ob);        
        tell_object(ob,HIR"���������ħ��Ӯ��20����ɰ.\n"NOR); 
        }
        else
        {        
       for(i = 0; i<sizeof(players); i++)
         {
        wp = new("/clone/vip/jinsha");
         wp->set_amount(10);
        wp->move(players[i]);       
       tell_object(players[i],HIR"�������������ϻ�������ħ��Ӯ��10����ɰ.\n"NOR); 
       }
       }
  //          message("channel:chat",HBYEL"��������������"HIR"��"+ob->query("name")+"�񹦸�������ɱ��"+name()+"���¼��𾪽��������߹���"+w+"�����հ����\n"NOR,users());
       ::die();
}
