// by luoyun

inherit ROOM;

void create()
{
	set("short", "����һ��");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"south" : "/data/home/a/a176129/hell/xiyue",
		"west" : "/data/home/w/wx2113002301/hell/yuran",
		"east" : __DIR__"wulinyi12",
		"north" : __DIR__"wulinyi14",
	]));
	//set("price_build", 1000);
	setup();
}
