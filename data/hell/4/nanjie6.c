
inherit ROOM;

void create()
{
	set("short", "�Ͻ�����");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"west" : "/data/home/l/luxiem/hell/lanxizhen",
		"south" : "/data/home/n/nmsl/hell/god",
		"north" : __DIR__"nanjie5",
		"east" : __DIR__"wulinsi22",
		//"west" : __DIR__"wulinsan19",
	]));
	set("objects", ([
	]));
	setup();
}
