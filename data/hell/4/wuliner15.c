

inherit ROOM;

void create()
{
	set("short", "���ֶ���");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"north" : "/data/home/h/hhy1/hell/tian",
		"east" : __DIR__"nanjie4",
		"west" : __DIR__"wuliner16",
	]));
	set("price_build", 1000);
	setup();
}
