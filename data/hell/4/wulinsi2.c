
inherit ROOM;

void create()
{
	set("short", "�����Ľ�");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"north" : "/data/home/y/yashiroxb/hell/langyage",
		"west" : __DIR__"wulinsi1",
		"east" : __DIR__"wulinsi3",
	]));
	set("price_build", 1000);
	setup();
}
