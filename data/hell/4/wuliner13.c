

inherit ROOM;

void create()
{
	set("short", "���ֶ���");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"north" : "/data/home/a/a1292299769/hell/difu",
		"east" : __DIR__"wuliner12",
		"west" : __DIR__"wuliner14",
	]));
	set("price_build", 1000);
	setup();
}
