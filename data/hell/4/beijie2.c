// by luoyun

inherit ROOM;

void create()
{
	set("short", "���ֶ���");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"east" : "/data/home/d/duxing123/hell/duxing",
		"west" : "/data/home/l/lyj19988/hell/swty",
		"south" : __DIR__"beijie1",
		"north" : __DIR__"beijie3",
	]));
	set("objects", ([
	]));
	setup();
}
