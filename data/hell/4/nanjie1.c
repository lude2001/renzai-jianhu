// by luoyun

inherit ROOM;

void create()
{
	set("short", "�Ͻ�һ��");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"west" : "/data/home/q/q702413605/hell/duan",
		"east" : "/data/home/w/wwweee1/hell/mantou",
		"north" : __DIR__"guangchang",
		"south" : __DIR__"nanjie2",
	]));
	set("objects", ([
	]));
	setup();
}
