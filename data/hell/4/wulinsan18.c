

inherit ROOM;

void create()
{
	set("short", "武林三街");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"south" : "/data/home/a/aa225/hell/yun",
		"north" : "/data/home/x/xiong123/hell/shanzhuang",
		"east" : __DIR__"wulinsan17",
		"west" : __DIR__"nanjie5",
	]));
	set("price_build", 1000);
	setup();
}
