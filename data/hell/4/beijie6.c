// by luoyun

inherit ROOM;

void create()
{
	set("short", "北街五号");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"west" : "/data/home/q/qq3011893671/hell/loushi",
		"north" : "/data/home/c/cs666/hell/xiaoyhg",
		"south" : __DIR__"beijie5",
		"east" : __DIR__"wulinsi1",
		//"west" : __DIR__"wulinsi56",
		//"north" : __DIR__"beijie7",
	]));
	set("objects", ([
	]));
	setup();
}
