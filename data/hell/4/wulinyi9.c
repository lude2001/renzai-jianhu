// by luoyun

inherit ROOM;

void create()
{
	set("short", "����һ��");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"south" : "/data/home/k/kingyyyyy/hell/pyhf",
		"north" : "/data/home/k/kaiguawanjia/hell/biguan",
		"east" : __DIR__"wulinyi8",
		"west" : __DIR__"wulinyi10",
	]));
	//set("price_build", 1000);
	setup();
}
