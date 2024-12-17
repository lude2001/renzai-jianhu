// by luoyun

inherit ROOM;

void create()
{
	set("short", "武林一街");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"south" : "/data/home/k/kingyyyyy/hell/pyhf",
		"north" : "/data/home/k/kaiguawanjia/hell/biguan",
		"east" : __DIR__"wulinyi8",
		"west" : __DIR__"wulinyi10",
	]));
	//set("price_build", 1000);
	setup();
}
