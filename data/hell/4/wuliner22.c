

inherit ROOM;

void create()
{
	set("short", "���ֶ���");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"east" : "/data/home/d/duwang001/hell/ltwf",
		"south" : __DIR__"xijie4",
		"north" : __DIR__"wuliner23",
	]));
	set("price_build", 1000);
	setup();
}
