// by luoyun

inherit ROOM;

void create()
{
	set("short", "����һ��");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"north" : "/data/home/s/sirjinmuyan/hell/sirjin",
		"south" : "/data/home/z/z1246678161/hell/taohuawu",
		"east" : __DIR__"wulinyi11",
		"west" : __DIR__"wulinyi13",
	]));
	//set("price_build", 1000);
	setup();
}
