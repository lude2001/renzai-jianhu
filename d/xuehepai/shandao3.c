//shandao1。c      by baby


#include <ansi.h>
int do_qiao(string arg);
inherit ROOM;

int do_qiao(string arg);

void create ()
{
        set ("short", "山道");
        set ("long", @LONG
这里是后山一条昏暗的山道。山道的两旁已是光秃秃的没有一棵植物
这里的山石竟发出深深的赤红色，不知这与处别的石头有什么不同，可能
有毒物和饿狼潜伏在附近，离开这里吧。
LONG);
        set("valid_startroom", 1);
        set("outdoors", "龙门");
        set("exits", ([
		"south" : __DIR__"shandao2",
		"northwest" : __DIR__"hsxiaolu1",
        ]));
        set("action_list", ([
		"敲石头" : "knock shi",
		]));
        set("shi",500);
        setup();
}

void init()
{
        add_action("do_qiao","knock");
}

int do_qiao(string arg)
{
        object me;
        object weapon;
        int jingli_cost;

        me = this_player();
        weapon=me->query_temp("weapon");
       jingli_cost = (-1) * (10 + random(10));

        if ( !arg || ( arg != "shi" ) )
                return notify_fail("你想干什么？\n");

        if ( !(me->query_temp("job_start")))
                return notify_fail("你没事做吗？乱敲什么呀！\n");
        
        if (!weapon || (weapon->query("id")!="hammer"))
                return notify_fail("你手上没有铁锤，难道用手？\n");

        if ( me->query_temp("find") )
                return notify_fail("你已经找到一块矿石了，没有力气再带一块！\n");
        
          if ( me->query("qi") <= ( - jingli_cost ) )
                return notify_fail("你太疲劳了，没有精力再继续敲凿了。\n");

         if (me->is_busy())
                   return notify_fail("你正忙着呢。\n");
        if ( (int)query("shi") >= 1 )
        {
                message_vision(YEL"$N扬起手中的铁锤重重的砸在道旁的山石上。\n"NOR, me);
                if ( random(15)<4 )
                {
                        message_vision(HIG"$N听到山石发出清脆的碎裂声，终于给$N敲下来了一大块！\n"NOR, me);
                        new("/kungfu/class/xuehepai/obj/shi")->move(me);
                        me->set_temp("find",1);
                }
                me->add("qi", jingli_cost);
                add("shi",-1);
                me->start_busy(2);
        }
        else
                return notify_fail("山道边的山石都被砸碎了，没有可以用的了。\n");

        return 1;
}

