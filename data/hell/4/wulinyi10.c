// by luoyun

inherit ROOM;

void create()
{
	set("short", "����һ��");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"south" : "/data/home/q/q1096/hell/hai",
		"north" : "/data/home/l/l345821/hell/fushengge",
		"east" : __DIR__"wulinyi9",
		"west" : __DIR__"nanjie3",
	]));
	//set("price_build", 1000);
	setup();
}
