// by luoyun

inherit ROOM;

void create()
{
	set("short", "武林一街");
	set("long", "这是一条宽阔的青石街道。");
	set("outdoors", "hell");
	set("exits", ([
		"east" : "/data/home/z/z2530505089/hell/daoguan",
		"west" : "/data/home/q/qw6812249/hell/shangqing",
		"north" : __DIR__"wulinyi6",
		"south" : __DIR__"wulinyi8",
	]));
	//set("price_build", 1000);
	setup();
}
