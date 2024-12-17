// by mayue

inherit ROOM;
string* npcs = ({
	__DIR__"npc/qiandu1",
	__DIR__"npc/qiandu2",
	__DIR__"npc/qiandu3",
	__DIR__"npc/qiandu4",
	__DIR__"npc/qiandu5",

});

void create()
{
	set("short", "ǧ����");
	set("long", @LONG
������һ����Ȼ�γɵ�ʯ�������������󡣶������������
����ʯ����ʱ���������δ��ˮ�������ڶ��У�����������ʪ����
�Ժ�Ȼ����һ�����С���������
LONG
	);
//        set("outdoors", "wudujiao");

	set("exits", ([
                "south" : __DIR__"qiandu1",
                "north" : __DIR__"qiandu3",
                "west" : __DIR__"qiandu4",
                "east" : __DIR__"qiandu5",
	]));
        set("objects", ([
	        npcs[random(sizeof(npcs))] : 1,
	        npcs[random(sizeof(npcs))] : 1,
	]));


	setup();
	replace_program(ROOM);
}

