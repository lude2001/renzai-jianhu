

inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"west" : "/data/home/q/q929733198/hell/shitiandi",
		"north" : __DIR__"xijie5",
		"south" : __DIR__"wulinsan26",
	]));
	set("price_build", 1000);
	setup();
}
