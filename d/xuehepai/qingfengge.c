//qingfengge。c  by baby

#include <room.h>

inherit ROOM;

void create()
{	
        set("short", "清风阁");
	set("long", @LONG
这是一间温馨的卧室。这里是合欢宗男弟子居住的地方，房间宽敞明
亮，墙壁粉刷的雪白，窗边摆放着一张宽大舒适的软床，床头有一张被擦
拭的一尘不染的红木方桌，门口垂手站立着一名侍从，随时准备听候主人
的吩咐。
LONG);	
	set("valid_startroom",1);
	set("no_steal", "1");
	set("no_fight", "1");
	set("sleep_room",1);
        set("exits", ([ "east" : __DIR__"zoulang4",
        ]));
	setup();
	replace_program(ROOM);
}
