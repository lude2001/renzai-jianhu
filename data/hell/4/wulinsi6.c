
inherit ROOM;

void create()
{
	set("short", "�����Ľ�");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"north" : "/data/home/a/aad1123/hell/xmw",
		"west" : __DIR__"wulinsi5",
		"south" : __DIR__"wulinsi7",
	]));
	set("price_build", 1000);
	setup();
}
