// by luoyun

inherit ROOM;

void create()
{
	set("short", "武林一街");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"south" : "/data/home/q/q1096/hell/hai",
		"north" : "/data/home/l/l345821/hell/fushengge",
		"east" : __DIR__"wulinyi9",
		"west" : __DIR__"nanjie3",
	]));
	//set("price_build", 1000);
	setup();
}
