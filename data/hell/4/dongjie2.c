// by luoyun

inherit ROOM;

void create()
{
	set("short", "���ֶ���");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"south" : "/data/home/x/x123456789/hell/lou",
		"north" : "/data/home/a/a162275575/hell/guiwu",
		"west" : __DIR__"dongjie1",
		"east" : __DIR__"dongjie3",
	]));
	set("objects", ([
	]));
	setup();
}
