// by luoyun

inherit ROOM;

void create()
{
	set("short", "武林一街");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"west" : "/data/home/w/wdc123/hell/qingjingju",
		"east" : "/data/home/l/ljf123/hell/fenge",
		"south" : __DIR__"wulinyi16",
		"north" : __DIR__"wulinyi18",
	]));
	//set("price_build", 1000);
	setup();
}
