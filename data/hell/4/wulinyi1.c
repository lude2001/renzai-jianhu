// by luoyun

inherit ROOM;

void create()
{
	set("short", "����һ��");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"south" : "/data/home/z/z863606146/hell/xy",
		"north" : "/data/home/q/qweasd123/hell/xiaoyu",
		"west" : __DIR__"beijie3",
		"east" : __DIR__"wulinyi2",
	]));
	//set("price_build", 1000);
	setup();
}
