

inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"south" : "/data/home/a/aa225/hell/yun",
		"north" : "/data/home/x/xiong123/hell/shanzhuang",
		"east" : __DIR__"wulinsan17",
		"west" : __DIR__"nanjie5",
	]));
	set("price_build", 1000);
	setup();
}
