

inherit ROOM;

void create()
{
	set("short", "���ֶ���");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"south" : "/data/home/i/indulge/hell/indulge",
		"north" : __DIR__"wuliner10",
		"west" : __DIR__"wuliner12",
	]));
	set("price_build", 1000);
	setup();
}
