// Room: /d/huashan/jzroad7.c

#include <room.h>
inherit ROOM;

void create()
{
	set("short", "�ͱ�");
	set("long", @LONG
�������ͱڱߵ�С·�ϡ�һ�������ܵĴ��֣����ȴ�Ǽ���Ķ�
�ڡ�ɽ������������Ҫ���������ȥ��
LONG );
	set("exits", ([

	    "eastdown" : __DIR__"jzroad6",
	    "southup"  : __DIR__"shangu",
	    "north"  : __DIR__"shandian",
	]));
	set("outdoors", "xx");
	set("no_clean_up", 0);

	setup();
}
