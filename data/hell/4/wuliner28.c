

inherit ROOM;

void create()
{
	set("short", "���ֶ���");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"south" : "/data/home/q/qq1432655879/hell/huanggong",
		"north" : "/data/home/d/dongfangming/hell/home",
		"west" : __DIR__"wuliner27",
		"east" : __DIR__"beijie4",
	]));
	set("price_build", 1000);
	setup();
}
