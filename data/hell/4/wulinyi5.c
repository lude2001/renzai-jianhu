// by luoyun

inherit ROOM;

void create()
{
	set("short", "����һ��");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"east" : "/data/home/y/y5yr123/hell/aoao",
		"west" : "/data/home/a/a999/hell/chanxingwuyu",
		"north" : __DIR__"wulinyi4",
		"south" : __DIR__"dongjie3",
	]));
	//set("price_build", 1000);
	setup();
}
