//qinghange。c  by baby

#include <room.h>

inherit ROOM;

void create()
{	
        set("short", "清寒阁");
	set("long", @LONG
这里是合欢宗女弟子的卧房。走进清寒阁，这儿虽然不是很华丽，但
处处都透出一种清新，淡雅，让人感到舒适，惬意，八盆郁金香把房间点
缀的超然脱俗，空气中弥漫着似浓似淡的花香，仿佛置身于仙境。
LONG);	
	set("valid_startroom",1);
	set("no_steal", "1");
	set("no_fight", "1");
	set("sleep_room",1);
        set("exits", ([
		"west" : __DIR__"zoulang3",
        ]));
	setup();
	replace_program(ROOM);
}
