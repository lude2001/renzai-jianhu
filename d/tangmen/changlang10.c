//room: /d/tangmen/changlang10.c
//  xws 1998/11/05
inherit ROOM;

void create()
{
  set("short","长廊");
  set("long",
      "这里一段长廊，两旁是红木廊柱，顶上有很漂亮的漆画和书法。每一段长廊的\n"
"书画恰好都组成了一个故事或是一个久远的传说。这里往北就是祭祖厅。\n"
     );

  set("exits",([
      "north" : __DIR__"jizuting",
      "south" : __DIR__"changlang11",
    ]));

 setup();
 replace_program(ROOM);
}




