// by luoyun

inherit ROOM;

void create()
{
	set("short", "����һ��");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"south" : "/data/home/d/du199344/hell/dujiaxi",
		"north" : "/data/home/s/sjfx0802/hell/duanzhai",
		"west" : __DIR__"wulinyi1",
		"east" : __DIR__"wulinyi3",
	]));
	//set("price_build", 1000);
	setup();
}
