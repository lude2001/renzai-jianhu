// by mayue

inherit ROOM;
string* npcs = ({
	__DIR__"npc/baidu1",
	__DIR__"npc/baidu2",
	__DIR__"npc/baidu3",
	__DIR__"npc/baidu4",
	__DIR__"npc/baidu5",

});

void create()
{
	set("short", "�ٶ���");
	set("long", @LONG
������һ����Ȼ�γɵ�ʯ�������������󡣶������������
����ʯ����ʱ���������δ��ˮ�������ڶ��У�����������ʪ����
�Ժ�Ȼ����һ�����С���������
LONG
	);
//        set("outdoors", "wudujiao");

	set("exits", ([
                "north" : __DIR__"baidu1",
                "south" : __DIR__"baidu3",
                "west" : __DIR__"baidu4",
                "east" : __DIR__"baidu5",
	]));
        set("objects", ([
	        npcs[random(sizeof(npcs))] : 1,
	        npcs[random(sizeof(npcs))] : 1,
	        npcs[random(sizeof(npcs))] : 1,
	]));


	setup();
	replace_program(ROOM);
}

