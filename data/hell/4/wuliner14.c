

inherit ROOM;

void create()
{
	set("short", "���ֶ���");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"north" : "/data/home/i/iris/hell/yujing",
		"south" : "/data/home/c/chao/hell/yi",
		"east" : __DIR__"wuliner13",
		"west" : __DIR__"nanjie4",
	]));
	set("price_build", 1000);
	setup();
}
