// Room: /city/wumiao.c
// YZC 1995/12/04 

#include <room.h>

inherit ROOM;

int is_chat_room() { return 1; }

void create()
{
	set("short", "武庙");
	set("long", @LONG
这里是岳王庙的正殿，内有岳飞像，像上方悬挂岳飞手书“还我河山”的
横匾。殿两侧壁上嵌着“尽忠报国”四个大字。武人到此，都放下武器，毕恭
毕敬地上香礼拜。旁边似乎有一道侧门。
LONG );
	set("no_fight", "1");
	set("no_steal", "1");
	set("no_sleep_room", "1");
	set("close_room",1);
	set("valid_startroom","1");
	set("objects", ([
		__DIR__"obj/box" : 1,
	]));

	set("exits", ([



		"east" : __DIR__"beidajie2",
		"up"   : __DIR__"wumiao2",
		"northwest": "/d/wizard/guest_room",
	]));
	create_door("northwest", "竹门", "southeast", DOOR_CLOSED);
	setup();
}

int valid_leave(object me, string dir)
{
	if (dir == "northwest" && ! userp(me) && ! me->is_chatter())
		return 0;
	return ::valid_leave(me, dir);
}

