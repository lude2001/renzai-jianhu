inherit ROOM;
#include <ansi.h>
int do_yun(string arg);
void create()
{
        set("short","急流");
        set("long",@LONG
你已经掉进了这个危险的龙门急流，强大的水流冲击着你的身体。
由于形成了旋涡，一不小心就会被旋涡撕成碎片。可是这大自然的力量
又好象提示你去克服它，利用它。
LONG );
        set("exits",([
              "enter" : __DIR__"mishi",
        ]));
        set("outdoors","龙门");
        set("class","合欢宗");
        set("action_list", ([
		"领悟" : "lingwu 欢喜转轮经",
                "跳入潭底" : "tiao out"
		]));
//        set("no_clean_up"， 0);
        setup();
}

void init()
{
        add_action("do_yun","lingwu");
        add_action("do_jump","tiao");
        if ((interactive(this_player())) && !(this_player()->is_fighting()))
        {
                if (this_player()->query_skill("hx-jing",1))
                    {
                       this_player()->delete_temp("xueheche");
                        this_player()->delete_temp("chong");
                        return;
                      }
                if (!(this_player()->query_temp("chong")))
                {
                        message_vision("$N拼命去运功抵抗旋涡的压力，可是大自然的力量太强大了。。。\n",this_player());
                        this_player()->die();
                        message("channel:rumor",HIY"【惨死】"HIB"传闻"+this_player()->query("name")+"掉进龙门急流中，被急流冲得死无全尸！\n"NOR,users());
                        return;
                }
                else if (this_player()->query("max_neili")<1000)
                {
                        message_vision("虽然血河车帮你抵消了大部分的压力，但是你的内力太差了。。。。\n",this_player());
                        message("channel:rumor",HIY"【惨死】"HIB"传闻"+this_player()->query("name")+"掉进龙门急流中，被急流冲得死无全尸！\n"NOR,users());
                        this_player()->die();
                        return;
                }
                message_vision("$N拼命去运功抵抗旋涡的压力，只见水流直向你扑来。。。。\n",this_player());
                this_player()->move(__DIR__"mishi");
                this_player()->delete_temp("xueheche");
                this_player()->delete_temp("chong");
                this_player()->unconcious();
                return;
          }
}

int do_yun(string arg)
{
        object me;
        int skills;

        me=this_player();
        skills=me->query_skill("hx-jing",1);
        
         if (!arg  || arg!="欢喜转轮经")
                return notify_fail("你要领悟什么武功？\n");
                
        if ((skills*skills*skills/10)>me->query("combat_exp"))
             return notify_fail("你的经验不够，不能继续领悟。\n");

         if (skills>260)
              return notify_fail("你的欢喜转轮经深不可测了。\n");

         if (me->query("qi")<150 || me->query("jingli")<80)
                return notify_fail("你的气色太差了，还领悟个啥？\n");
        message_vision(HIY"$N将欢喜转轮经运满全身，放松肌体，任由急流冲刷。\n"NOR,me);
        message_vision(HIY"$N将急流的旋涡劲纳入体内，身随意转，随着旋涡流一起旋转。\n"NOR,me);
        tell_object(me,"你对欢喜转轮经有了更进一步的领悟。\n");
        me->improve_skill("hx-jing",random(5*me->query("int")));
        me->add("qi",-150);
        me->add("jingli",-80);
        return 1;
}

int do_jump(string arg)
{
           object me;
           me=this_player();

           if (!arg && arg!="out")
            return notify_fail("你要往哪跳？\n");

           if (me->query_skill("hx-jing",1)<100)
            return notify_fail("你的欢喜转轮经修为还不够。\n");

           message_vision("$N纵身一跃，随着旋涡而去！\n",me);
           me->move(__DIR__"tanbian");
           message_vision("只见$N突然从深潭底冒了出来！\n",me);
           return 1;
}

