

inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"north" : "/data/home/r/raphael27/hell/mstg",
		"east" : __DIR__"wulinsan33",
		"south" : __DIR__"wulinsan31",
	]));
	set("price_build", 1000);
	setup();
}
