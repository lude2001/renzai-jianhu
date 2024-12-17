

inherit ROOM;

void create()
{
	set("short", "武林二街");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"north" : "/data/home/h/hhy1/hell/tian",
		"east" : __DIR__"nanjie4",
		"west" : __DIR__"wuliner16",
	]));
	set("price_build", 1000);
	setup();
}
