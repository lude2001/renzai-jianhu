// by luoyun

inherit ROOM;

void create()
{
	set("short", "武林一街");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"east" : "/data/home/t/tx151134/hell/yutang",
		"west" : "/data/home/y/yyouzhen2015/hell/jiuxiaoge",
		"north" : __DIR__"wulinyi3",
		"south" : __DIR__"wulinyi5",
	]));
	//set("price_build", 1000);
	setup();
}
