// Room: /city/beidajie2.c

inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", @LONG
�����ǵ������档
LONG );
	set("outdoors", "city");
	set("exits", ([
		"south" : __DIR__"enter",
	]));
	set("out_room","/d/city/wumiao");
	set("newboss",1);
	setup();
}
