// by luoyun

inherit ROOM;

void create()
{
	set("short", "����һ��");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"east" : "/data/home/c/ccc7520/hell/xueyuege",
		"west" : "/data/home/d/d412464611/hell/xiaowu",
		"south" : __DIR__"wulinyi13",
		"north" : __DIR__"wulinyi15",
	]));
	//set("price_build", 1000);
	setup();
}
