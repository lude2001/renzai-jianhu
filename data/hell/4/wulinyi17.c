// by luoyun

inherit ROOM;

void create()
{
	set("short", "����һ��");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"west" : "/data/home/w/wdc123/hell/qingjingju",
		"east" : "/data/home/l/ljf123/hell/fenge",
		"south" : __DIR__"wulinyi16",
		"north" : __DIR__"wulinyi18",
	]));
	//set("price_build", 1000);
	setup();
}
