// by luoyun

inherit ROOM;

void create()
{
	set("short", "武林一街");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"east" : "/data/home/c/ccc7520/hell/xueyuege",
		"west" : "/data/home/d/d412464611/hell/xiaowu",
		"south" : __DIR__"wulinyi13",
		"north" : __DIR__"wulinyi15",
	]));
	//set("price_build", 1000);
	setup();
}
