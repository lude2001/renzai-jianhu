
inherit ROOM;

void create()
{
	set("short", "С·");
	set("long", @LONG
������һ��С·�ϡ�ǰ���·��᫣����˺��١�ǰ����Լ�з��ݿɼ���
LONG );
	set("exits", ([
		"south" : __DIR__"zhuang1",
		"north" : __DIR__"zhuang3",
	]));
	set("objects", ([
		"/d/wudang/npc/tufei1" : 1,
	]));
 	set("outdoors", "beijing");
	setup();
}