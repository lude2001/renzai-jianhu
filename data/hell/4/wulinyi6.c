// by luoyun

inherit ROOM;

void create()
{
	set("short", "武林一街");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"west" : "/data/home/z/zhang0zi0yi0/hell/zhenhun",
		"east" : "/data/home/q/q1639284573/hell/chinese",
		"north" : __DIR__"dongjie3",
		"south" : __DIR__"wulinyi7",
	]));
	//set("price_build", 1000);
	setup();
}
