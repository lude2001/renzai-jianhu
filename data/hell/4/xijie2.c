// by luoyun

inherit ROOM;

void create()
{
	set("short", "���ֶ���");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"south" : "/data/home/z/zzldzzldzzl/hell/yanziwu",
		"north" : "/data/home/y/yst2110003/hell/hqj",
		"east" : __DIR__"xijie1",
		"west" : __DIR__"xijie3",
	]));
	set("objects", ([
	]));
	setup();
}
