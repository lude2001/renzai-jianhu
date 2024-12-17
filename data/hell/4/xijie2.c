// by luoyun

inherit ROOM;

void create()
{
	set("short", "西街二号");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"south" : "/data/home/z/zzldzzldzzl/hell/yanziwu",
		"north" : "/data/home/y/yst2110003/hell/hqj",
		"east" : __DIR__"xijie1",
		"west" : __DIR__"xijie3",
	]));
	set("objects", ([
	]));
	setup();
}
