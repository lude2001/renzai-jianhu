//qixuetang。c           合欢宗--泣血堂

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "泣血堂");
	set("long", @LONG
这里是泣血堂，属于合欢宗的内堂重地。为防止外敌来袭，要来此地
关卡重重。这里是一个庄重，又很典雅的建筑，四周用红幔包裹，显得极
为森严，大堂内有十二道柱梁，每根柱梁上镂有十二条栩栩如生的飞天巨
龙，还附有一些珍禽异兽。顶梁上雕了意气风发的“血河天下”四个大字
，使人不油对合欢宗肃然起敬！此处为合欢宗弟子每年选秀大会及派内大
小事务商议所在地。因此，守卫不时来往其间，可见派风严谨。
LONG);
	set("exits", ([	
        	"eastdown" : __DIR__"zoulang5",
        	"north" : __DIR__"xueku",
        	"northwest" : __DIR__"yanwuchang",
        	"south" : __DIR__"xuehuatang",
	]));
	setup();
          //"/clone/board/xuehe_b"->foo(); '帮派留言板，哈哈，用不了
	replace_program(ROOM);
}
