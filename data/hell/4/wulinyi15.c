// by luoyun

inherit ROOM;

void create()
{
	set("short", "����һ��");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"west" : "/data/home/s/slyzy0515/hell/lsyany",
		"east" : "/data/home/t/tws12345/hell/guowo",
		"south" : __DIR__"wulinyi14",
		"north" : __DIR__"xijie3",
	]));
	//set("price_build", 1000);
	setup();
}
