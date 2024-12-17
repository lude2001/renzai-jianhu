// by luoyun

inherit ROOM;

void create()
{
	set("short", "东街一号");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"south" : "/data/home/d/d259060658/hell/qingyilou",
		"north" : "/data/home/y/yly1/hell/yunlanju",
		"west" : __DIR__"guangchang",
		"east" : __DIR__"dongjie2",
	]));
	set("objects", ([
	]));
	setup();
}
