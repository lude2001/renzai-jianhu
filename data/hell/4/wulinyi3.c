// by luoyun

inherit ROOM;

void create()
{
	set("short", "����һ��");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"east" : "/data/home/a/a25838870/hell/hongmoguag",
		"north" : "/data/home/z/z18799763492/hell/liudaogong",
		"west" : __DIR__"wulinyi2",
		"south" : __DIR__"wulinyi4",
	]));
	//set("price_build", 1000);
	setup();
}
