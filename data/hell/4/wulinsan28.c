

inherit ROOM;

void create()
{
	set("short", "武林三街");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"west" : "/data/home/z/z0411/hell/motianxuandi",
		"north" : __DIR__"wulinsan29",
		"south" : __DIR__"xijie5",
	]));
	set("price_build", 1000);
	setup();
}

