// by luoyun

inherit ROOM;

void create()
{
	set("short", "武林一街");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"south" : "/data/home/d/du199344/hell/dujiaxi",
		"north" : "/data/home/s/sjfx0802/hell/duanzhai",
		"west" : __DIR__"wulinyi1",
		"east" : __DIR__"wulinyi3",
	]));
	//set("price_build", 1000);
	setup();
}
