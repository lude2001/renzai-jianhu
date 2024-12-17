#include <room.h>
inherit ROOM;

void create()
{
        set("short", "树干上");
        set("long", @LONG
你爬着爬着，发现浓密的树叶和树枝严重的扰乱了你的视线。你努
力的扒开树枝往上爬，到处都是一样的景色。你不禁迷茫了。直觉告诉
你：你迷路了。
LONG);
        set("exits", ([
		"southdown" : __DIR__"zrping",
		"northdown" : __DIR__"shugans",
//		"westdown" : __FILE__,
//		"eastdown" : __FILE__,        
//		"westup" : __FILE__,
//		"eastup" : __FILE__,
		"southup" : __FILE__,
		"northup" : __DIR__"shugan2",
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


