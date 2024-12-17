// by luoyun

inherit ROOM;

void create()
{
	set("short", "北街一号");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"west" : "/data/home/s/sdl1984/hell/qingyangju",
		"east" : "/data/home/a/ark76522/hell/third",
		"south" : __DIR__"guangchang",
		"north" : __DIR__"beijie2",
	]));
	set("objects", ([
	]));
	setup();
}
