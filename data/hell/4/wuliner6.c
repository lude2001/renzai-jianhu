inherit ROOM;

void create()
{
	set("short", "���ֶ���");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"west" : "/data/home/a/a283193184/hell/sg",
		"east" : "/data/home/k/kmmm/hell/wjsd",
		"north" : __DIR__"wuliner5",
		"south" : __DIR__"wuliner7",
	]));
	set("price_build", 1000);
	setup();
}
