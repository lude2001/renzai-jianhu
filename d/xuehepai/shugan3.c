#include <room.h>
inherit ROOM;

void create()
{
        set("short", "树干上");
        set("long", @LONG
你爬着爬着，发现浓密的树叶和树枝严重的扰乱了你的视线。正在这
时你突然发现浓浓的树叶和树枝竟然扒到了一处悬崖的边缘，你大喜过望
，连忙扒开树枝，向悬崖爬去。
LONG);

        set("exits", ([
//		"southdown" : __FILE__,
		"northdown" : __FILE__,
		"westdown" : __DIR__"shugan2",
//		"eastdown" : __FILE__,        
		"westup" : __FILE__,
		"northup" : __DIR__"pububian",
//		"southup" : __FILE__,
//		"eastup" : __FILE__,
        ]));
        set("outdoors", "龙门");
        setup();
        replace_program(ROOM);
}

int valid_leave(object me, string dir)
{
        int jingli_cost;

        me=this_player();

        jingli_cost=(-1) * (( me->query("max_jingli") ) / 20 );

        return ::valid_leave(me, dir);
}