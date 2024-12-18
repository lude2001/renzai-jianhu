#include <room.h>
inherit ROOM;

void create()
{
        set("short", "龙门瀑布");
        set("long", @LONG
来到龙门瀑布了，震耳欲聋的水声从更高的山上咆哮而下，一条条银
练击打着岩石，溅起串串水珠，在阳光的照射下，分外吸引人。常年不绝
的瀑布使得下面形成了一个深潭，潭里的水势依然很急。想起卫悲回就是
死于这龙门急流中，心里不禁黯然。
LONG);
        set("valid_startroom",1);
        set("exits", ([
		"east" : __DIR__"pububian",
        ]));
        set("action_list", ([
		"跳瀑布" : "jump pubu",
		]));
        set("outdoors","龙门");
        setup();
}

void init()
{
        add_action("do_jump","jump");
}

int do_jump(string arg)
{
          object ob;
        object me;
          mapping fam;

          me=this_player();
          if (!arg || arg!="pubu")
              return notify_fail("你要跳到哪里去？\n");
          message_vision("只见$N力贯全身，向着瀑布呼啸而去！\n",me);
          if ((me->query_skill("dodge",1)<101) || !(ob=present("xueyi",me)))
             {
          message_vision("只见$N快要穿过瀑布时，身形顿缓，朝着底下深潭跌落下去！\n",me);
          me->move(__DIR__"jiliu");
          return 0;
        }
          me->move(__DIR__"midao1");
          message_vision("只见$N脚一点地，跳了进来！\n",me);
          return 1;
}

