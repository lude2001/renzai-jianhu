

inherit ROOM;

void create()
{
	set("short", "武林二街");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"north" : "/data/home/i/iris/hell/yujing",
		"south" : "/data/home/c/chao/hell/yi",
		"east" : __DIR__"wuliner13",
		"west" : __DIR__"nanjie4",
	]));
	set("price_build", 1000);
	setup();
}
