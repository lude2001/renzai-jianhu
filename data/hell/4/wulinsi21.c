
inherit ROOM;

void create()
{
	set("short", "武林四街");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"north" : "/data/home/w/w13247504154/hell/lonfu",
		"east" : __DIR__"wulinsi20",
		"west" : __DIR__"wulinsi22",
	]));
	set("price_build", 1000);
	setup();
}
