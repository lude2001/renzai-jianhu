//youmingge。c  by baby

#include <room.h>
#include <skill.h>

inherit ROOM;

void create()
{	
	set("short", "幽冥阁");
	set("long", @LONG
这里是合欢宗总管萧萧天的住所。其人心性凶残，天资聪颖，自创不少
邪派的绝学，因此来此拜师学艺之人也不乏其人。阁楼的结构精巧细密，大
多出自于萧萧天之手，此人不愧为一代枭雄。房内四周悬挂不少道具器皿，
是用来制作机关和护具的，还有一张幽冥血翼挂于西面墙上。
LONG);	
	set("valid_startroom",1);
	set("objects",([
		__DIR__"npc/xiao" : 1,
	]));
	set("exits",([
		"east" : __DIR__"xueyu",
		"south" : __DIR__"zoulang3",
	]));

        set("area", "龙门");
        setup();
            replace_program(ROOM);
}
