// by luoyun

inherit ROOM;

void create()
{
	set("short", "�Ͻֶ���");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"west" : "/data/home/z/zyh5202/hell/lfj",
		"east" : "/data/home/w/wwweee2/hell/maomao",
		"north" : __DIR__"nanjie1",
		"south" : __DIR__"nanjie3",
	]));
	set("objects", ([
	]));
	setup();
}
