#include <room.h>
inherit ROOM;

void create()
{
	set("short", "������");
	set("long", "�����ǻ�ɽ�۽��ı��侺������");
	set("exits", ([
		"out" : __DIR__"enter",
	]));
	set("objects",([
	]));
	setup();
}

int valid_leave(object me, string dir)
{
	me->force_me("quit");
	return 0;
}

void init()
{
    add_action("disable", ({"use", "eat"}));
}

int disable()
{
    write("ר�ı�������\n");
    return 1;
}