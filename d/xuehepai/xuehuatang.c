//xuehuatang.c          合欢宗--血花堂

#include <ansi.h>
#include <room.h>
inherit ROOM;


void create()
{
        set("short", "血花堂");
	set("long", @LONG
这里是合欢宗的血花堂。这里和青云阁连为一体，错落有致，二者同
为古黄玉石的建筑。堂内四壁镂有合欢宗各派掌门的手迹，气势磅礴，从
这里向前延伸，分为三个出路，而身后被一扇大门挡住去路。
LONG);
	set("valid_startroom",1);
	set("exits", ([
        	"north" : __DIR__"qixuetang",
        	"northeast" : __DIR__"qingyunge",
        	"west" : __DIR__"zoulang1",
        	"east" : __DIR__"zoulang2",
        	"south" : __DIR__"gate",
	]));
        set("area", "龙门");
	setup();
        replace_program(ROOM);
}
