//【蜀山派】mhxy-yushu 2001/2
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short","小厨房");
	set("long", @LONG

  这里是蜀山剑派的一个小厨房,看起来这里打扫很干净，
你可以放心的吃。星星的手艺看起来很不错啊。你可以要些(yao)
吃的。
LONG);
        
       set("no_fight",1);
       set("exits", ([
          "south" : __DIR__"midao1",
	]));

        set("objects", ([         
        __DIR__"npc/xingxing" : 1,
        "/clone/food/jiudai" :1,
        ]));
       set("clean_up", 1);
       set("resource", ([        
       "water" : 1,
       ]));
      setup();
}
int valid_leave()
{
       if((present("gongbao jiding", this_player())))
            return notify_fail("吃完包子再走吗！\n");
            if((present("hulu", this_player())))
            return notify_fail("你不能把酒袋带走！\n");
             return ::valid_leave();
}


