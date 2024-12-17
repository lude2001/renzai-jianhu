//hsxiaolu。c             龙门后山--碎石小路

#include <room.h>
inherit ROOM;

void create()
{
	set("short", "碎石小路");
	set("long", @LONG
这里是后山小路。道路越来越窄，山石林立，状若犬齿，碎石扎的脚
刺痛刺痛的，不时从远处传来声声怪啸，让人头皮发麻，小路弯弯曲曲的
向前伸去，通向更加阴暗的后山。
LONG);
	set("exits", ([
		"south" : __DIR__"hsxiaolu3",
		"west" : __DIR__"hsxiaolu4",
		"southeast" : __FILE__,
		"northeast" : __FILE__,
//		"southwest" : __FILE__,
//		"northwest" : __FILE__,
//		"east" : __FILE__,
//		"north" : __FILE__,
	]));
         set("outdoors","龙门");
	setup();
	replace_program(ROOM);
}
