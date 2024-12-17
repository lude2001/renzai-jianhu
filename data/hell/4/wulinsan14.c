

inherit ROOM;

void create()
{
	set("short", "武林三街");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"south" : "/data/home/p/poke/hell/qingshan",
		"north" : __DIR__"wulinsan13",
		"west" : __DIR__"wulinsan15",
	]));
	set("price_build", 1000);
	setup();
}
