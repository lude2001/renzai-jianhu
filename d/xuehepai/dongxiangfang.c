// dongxiangfang。c 东厢房
// mlf设计，lks编程

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short","东厢房");
	set("long",@LONG
由于东厅功能的改变，这里也做连相应的变动。原来的东西全都换成
了一排床。弟子们练功累了可以来这里稍作休息，恢复疲劳。房间里唯一
的一张长桌上放着一些食物和水壶，让那些勤于练功的弟子们不用去食堂
就餐，当然这些吃的多是暂时充饥之物。
LONG   	);
     	set("valid_startroom",1);
	set("no_fight",1);
	set("exits",([
                "west" : __DIR__"zoulang2",
                "north" : __DIR__"zoulang4",
     	]));
     	set("objects",([
     		"/clone/food/baozi" : random(4),
                "/clone/food/jiudai" : random(2),
     	]));
     	setup();
     	replace_program(ROOM);
}
