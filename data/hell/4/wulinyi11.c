// by luoyun

inherit ROOM;

void create()
{
	set("short", "武林一街");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"north" : "/data/home/y/yu192721769/hell/tsrj",
		"south" : "/data/home/q/qq667788999/hell/bianjing",
		"east" : __DIR__"nanjie3",
		"west" : __DIR__"wulinyi12",
	]));
	//set("price_build", 1000);
	setup();
}
