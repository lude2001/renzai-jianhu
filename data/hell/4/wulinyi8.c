// by luoyun

inherit ROOM;

void create()
{
	set("short", "����һ��");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"south" : "/data/home/q/q18813438745/hell/bldcyy",
		"east" : "/data/home/q/qj7964512/hell/btzx",
		"north" : __DIR__"wulinyi7",
		"west" : __DIR__"wulinyi9",
	]));
	//set("price_build", 1000);
	setup();
}
