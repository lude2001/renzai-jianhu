//xueheting。c  by baby

#include <room.h>

inherit ROOM;

void create()
{	
	seteuid(getuid());
	set("short", "血河厅");
	set("long", @LONG
这里便是合欢宗的藏宝室了，四周墙壁光亮鉴人，还有不少历代掌门
的书画作品，大厅的正中便是闻名遐迩，威镇武林的血河车(八骏四轮)，
车身上镂有历代掌门对于正派武学的精研心得，如果得之，学武可事半功
倍。真是“浩荡江湖，谁主沉浮，八骏血车，傲啸天下”。
LONG);	
	set("valid_startroom",1);

	set("objects",([
		__DIR__"npc/ren" : 1,
               __DIR__"obj/che" :1,
	]));

	set("exits", ([


        set("area", "龙门");

        setup();
}
