
inherit ROOM;

void create()
{
	set("short", "南街六号");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"west" : "/data/home/l/luxiem/hell/lanxizhen",
		"south" : "/data/home/n/nmsl/hell/god",
		"north" : __DIR__"nanjie5",
		"east" : __DIR__"wulinsi22",
		//"west" : __DIR__"wulinsan19",
	]));
	set("objects", ([
	]));
	setup();
}
