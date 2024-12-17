//houshan。c             龙门后山

#include <room.h>
inherit ROOM;

void create()
{
	set("short", "后山");
	set("long", @LONG
这里是合欢宗后山。这里阴森恐怖，四周断崖屹立，连日光也被遮住
，地上阴影斑驳，暗中好象有无数凶狠的目光注视着你，可能随时会扑上
来杀死你，赶快离开这里吧!
LONG);
	set("valid_startroom",1);
	set("exits", ([
		"southdown" : __DIR__"hsxiaolu4",
		"west" : __DIR__"zrping",
	]));
	set("outdoors","龙门");
	setup();
	replace_program(ROOM);
}