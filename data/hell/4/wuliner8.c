

inherit ROOM;

void create()
{
	set("short", "���ֶ���");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"west" : "/data/home/v/viga/hell/chongyg",
		"east" : "/data/home/s/sbsd250/hell/lsg",
		"north" : __DIR__"dongjie4",
		"south" : __DIR__"wuliner9",
	]));
	set("price_build", 1000);
	setup();
}
