// by luoyun

inherit ROOM;

void create()
{
	set("short", "����һ��");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"north" : "/data/home/y/yu192721769/hell/tsrj",
		"south" : "/data/home/q/qq667788999/hell/bianjing",
		"east" : __DIR__"nanjie3",
		"west" : __DIR__"wulinyi12",
	]));
	//set("price_build", 1000);
	setup();
}
