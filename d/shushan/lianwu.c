//【蜀山派】mhxy-yushu 2001/2
inherit ROOM;
#include <ansi.h>
void create()
{
        set("short","秘密练功房");
	set("long", @LONG

  这是蜀山派一个最隐蔽的练功房，这里静悄悄的，你走在场中，没有人
回头看你一眼，都在聚精汇神的练着自己的功夫。
LONG);
        set("exits", ([
           "west" : __DIR__"midao1",
	]));
         set("objects", ([ 
             __DIR__"obj/muren" : 4,
             __DIR__"npc/dizi" : 1,
             __DIR__"npc/dizi1" : 1,
       ]));
        setup();
}

