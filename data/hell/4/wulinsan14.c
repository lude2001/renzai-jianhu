

inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"south" : "/data/home/p/poke/hell/qingshan",
		"north" : __DIR__"wulinsan13",
		"west" : __DIR__"wulinsan15",
	]));
	set("price_build", 1000);
	setup();
}
