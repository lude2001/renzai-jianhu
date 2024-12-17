// by luoyun

inherit ROOM;

void create()
{
	set("short", "武林一街");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"south" : "/data/home/a/anran/hell/zmqj",
		"north" : "/data/home/e/e115234625/hell/dijiang",
		"west" : __DIR__"wulinyi19",
		"east" : __DIR__"beijie3",
	]));
	//set("price_build", 1000);
	setup();
}
