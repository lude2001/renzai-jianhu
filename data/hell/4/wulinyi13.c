// by luoyun

inherit ROOM;

void create()
{
	set("short", "武林一街");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"south" : "/data/home/a/a176129/hell/xiyue",
		"west" : "/data/home/w/wx2113002301/hell/yuran",
		"east" : __DIR__"wulinyi12",
		"north" : __DIR__"wulinyi14",
	]));
	//set("price_build", 1000);
	setup();
}
