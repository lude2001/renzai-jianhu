

inherit ROOM;

void create()
{
	set("short", "���ֶ���");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"west" : "/data/home/z/zxc17/hell/ggcs",
		"east" : "/data/home/y/yequ/hell/yequ",
		"north" : __DIR__"wuliner8",
		"south" : __DIR__"wuliner10",
	]));
	set("price_build", 1000);
	setup();
}
