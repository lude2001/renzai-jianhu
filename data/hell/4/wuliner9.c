

inherit ROOM;

void create()
{
	set("short", "武林二街");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"west" : "/data/home/z/zxc17/hell/ggcs",
		"east" : "/data/home/y/yequ/hell/yequ",
		"north" : __DIR__"wuliner8",
		"south" : __DIR__"wuliner10",
	]));
	set("price_build", 1000);
	setup();
}
