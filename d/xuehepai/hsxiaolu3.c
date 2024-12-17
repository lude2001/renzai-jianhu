#include <room.h>
inherit ROOM;

void create()
{
        set("short", "碎石小路");
        set("long", @LONG
这里是后山小路。只容一人通过，两边杂草丛生，不时传出悉悉索索
的拨草声，偶尔还有一两只小动物自面前掠过，小路弯弯曲曲的向前伸去
，通向更加阴暗的后山。
LONG);
        set("exits", ([
		"north" : __DIR__"hsxiaolu2",
		"south" : __FILE__,
//		"east" : __FILE__,
//		"west" : __FILE__,
//		"northwest" : __FILE__,
//		"northeast" : __FILE__,
		"southeast" : __FILE__,
		"southwest" : __DIR__"hsxiaolu1",
        ]));
        set("outdoors", "龙门");
        setup();
        replace_program(ROOM);
}

