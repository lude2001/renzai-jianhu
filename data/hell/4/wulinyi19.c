// by luoyun

inherit ROOM;

void create()
{
	set("short", "����һ��");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"south" : "/data/home/x/x2437279718/hell/coydalis",
		"north" : "/data/home/z/z245411/hell/biaoju",
		"west" : __DIR__"wulinyi18",
		"east" : __DIR__"wulinyi20",
	]));
	//set("price_build", 1000);
	setup();
}
