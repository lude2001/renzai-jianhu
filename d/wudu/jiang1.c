#include <ansi.h>
inherit ROOM;

void create()
{
        set ("short", "�һ�������");
        set ("long", @LONG
�������һ��� (river)�ߣ���ˮ�峺��ˮ��ƽ����������
���ޱߵ��������������һ����Ʈ�뽭�У��沨����������ͣ
����һ���ɴ���
LONG);
        set("to", "/d/wudu/jiang2");
        set("exits", ([
                "west" : __DIR__"bianzhai3",
        ]));
/*
        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));*/

        set("outdoors", "wudujiao");
        setup();
        replace_program(ROOM);
}