
inherit ROOM;

void create()
{
	set("short", "武林四街");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"north" : "/data/home/o/osbort0613/hell/xrdsg",
		"south" : "/data/home/x/xian150/hell/first",
		"east" : __DIR__"wulinsi21",
		"west" : __DIR__"nanjie6",
	]));
	set("price_build", 1000);
	setup();
}
