// by luoyun

inherit ROOM;

void create()
{
	set("short", "武林二街");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"north" : "/data/home/w/wuqing110/hell/mz",
		"west" : __DIR__"beijie4",
		"east" : __DIR__"wuliner2",
	]));

	set("price_build", 1000);
	setup();
}
