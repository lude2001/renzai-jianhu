#include <ansi.h>
inherit ROOM;

void create()
{
        set ("short", "�һ�������");
        set ("long", @LONG
�������һ����ߣ���ˮ�峺��ˮ��ƽ����������
���ޱߵ��������������һ����Ʈ�뽭�У��沨����������ͣ
����һ���ɴ���
LONG);
        set("to", "/d/wudu/jiang1");
        set("exits", ([
                "east" : __DIR__"cun1",
                "south" : __DIR__"xiao1",
        ]));

        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
		/*
        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));*/

        set("outdoors", "wudujiao");
        setup();
}
