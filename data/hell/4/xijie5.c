// by luoyun

inherit ROOM;

void create()
{
	set("short", "�������");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"west" : "/data/home/c/cao956793717/hell/changshengju",
		"east" : __DIR__"xijie4",
		"north" : __DIR__"wulinsan28",
		"south" : __DIR__"wulinsan27",
	]));
	set("objects", ([
	]));
	setup();
}
