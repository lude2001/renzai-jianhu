
inherit ROOM;

void create()
{
	set("short", "�����Ľ�");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"south" : "/data/home/q/qwe941013/hell/ouhuang",
		"north" : "/data/home/t/tmd8/hell/qinglou",
		"west" : __DIR__"beijie6",
		"east" : __DIR__"wulinsi2",
	]));
	set("price_build", 1000);
	setup();
}
