
inherit ROOM;

void create()
{
	set("short", "���ֶ���");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"west" : "/data/home/s/szer/hell/szer",
		"east" : "/data/home/b/baidu321/hell/liudao",
		"north" : __DIR__"wuliner6",
		"south" : __DIR__"dongjie4",
	]));
	set("price_build", 1000);
	setup();
}
