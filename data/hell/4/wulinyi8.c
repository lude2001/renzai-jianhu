// by luoyun

inherit ROOM;

void create()
{
	set("short", "武林一街");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"south" : "/data/home/q/q18813438745/hell/bldcyy",
		"east" : "/data/home/q/qj7964512/hell/btzx",
		"north" : __DIR__"wulinyi7",
		"west" : __DIR__"wulinyi9",
	]));
	//set("price_build", 1000);
	setup();
}
