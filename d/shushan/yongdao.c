//【蜀山派】mhxy-yushu 2001/2
inherit ROOM;
#include <room.h>
#include <ansi.h>
void create ()
{
  set ("short","甬道");
  set ("long", @LONG

到了这里你就是进了蜀山剑派了，东西面世两个练武场，
再往前走就是三皇殿了。
LONG);

  set("outdoors", 2);
  set("exits", ([ /* sizeof() == 4 */
"north" : __DIR__"sanhuang",
  "out" : __DIR__"shanmen",
 "east" : __DIR__"e-lianwu",
 "west" : __DIR__"w-lianwu",
  ]));
create_door("out", "石门", "enter", DOOR_CLOSED);
setup();
}
