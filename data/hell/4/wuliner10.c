

inherit ROOM;

void create()
{
	set("short", "���ֶ���");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"west" : "/data/home/l/luolan/hell/jlg",
		"east" : "/data/home/m/myxyyj/hell/shiyijv",
		"north" : __DIR__"wuliner9",
		"south" : __DIR__"wuliner11",
	]));
	set("price_build", 1000);
	setup();
}
