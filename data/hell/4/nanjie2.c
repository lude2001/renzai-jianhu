// by luoyun

inherit ROOM;

void create()
{
	set("short", "南街二号");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"west" : "/data/home/z/zyh5202/hell/lfj",
		"east" : "/data/home/w/wwweee2/hell/maomao",
		"north" : __DIR__"nanjie1",
		"south" : __DIR__"nanjie3",
	]));
	set("objects", ([
	]));
	setup();
}
