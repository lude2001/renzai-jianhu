// by luoyun

inherit ROOM;

void create()
{
	set("short", "武林一街");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"north" : "/data/home/s/sirjinmuyan/hell/sirjin",
		"south" : "/data/home/z/z1246678161/hell/taohuawu",
		"east" : __DIR__"wulinyi11",
		"west" : __DIR__"wulinyi13",
	]));
	//set("price_build", 1000);
	setup();
}
