// by luoyun

inherit ROOM;

void create()
{
	set("short", "����һ��");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"west" : "/data/home/z/zhang0zi0yi0/hell/zhenhun",
		"east" : "/data/home/q/q1639284573/hell/chinese",
		"north" : __DIR__"dongjie3",
		"south" : __DIR__"wulinyi7",
	]));
	//set("price_build", 1000);
	setup();
}
