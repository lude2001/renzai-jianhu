

inherit ROOM;

void create()
{
	set("short", "����һ��");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"south" : "/data/home/x/xf5z001/hell/lyqc",
		"north" : "/data/home/x/xuxueyang/hell/jingnan",
		"east" : __DIR__"guangchang",
		"west" : __DIR__"xijie2",
	]));
	set("objects", ([
	]));
	setup();
}
