// by luoyun

inherit ROOM;

void create()
{
	set("short", "����һ��");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"east" : "/data/home/t/tx151134/hell/yutang",
		"west" : "/data/home/y/yyouzhen2015/hell/jiuxiaoge",
		"north" : __DIR__"wulinyi3",
		"south" : __DIR__"wulinyi5",
	]));
	//set("price_build", 1000);
	setup();
}
