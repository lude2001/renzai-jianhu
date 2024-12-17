// by luoyun

inherit ROOM;

void create()
{
	set("short", "武林一街");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"west" : "/data/home/y/ye157/hell/xh",
		"east" : "/data/home/y/ye175/hell/lbjxh",
		"south" : __DIR__"xijie3",
		"north" : __DIR__"wulinyi17",
	]));
	//set("price_build", 1000);
	setup();
}
