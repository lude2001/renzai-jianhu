
inherit ROOM;

void create()
{
	set("short", "武林二街");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"west" : "/data/home/s/szer/hell/szer",
		"east" : "/data/home/b/baidu321/hell/liudao",
		"north" : __DIR__"wuliner6",
		"south" : __DIR__"dongjie4",
	]));
	set("price_build", 1000);
	setup();
}
