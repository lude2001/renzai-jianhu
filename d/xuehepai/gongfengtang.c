#include <ansi.h>

inherit ROOM;

void create()
{
        set("short","供奉堂");
        set("long",@LONG
合欢宗自开派以来，因不与外界来往，因此各代掌门都坐化于此，
从此，各代弟子将这里当作血河圣地，祈求先祖神灵保佑，甚至有不
少弟子前来此处修炼本派武学，以期有事半功倍的效果，然武技一途
只能通过勤学苦练，方有所成。
LONG);
        set("valid_startroom",1);
        set("exits",([
                "west" : __DIR__"zoulang5",
        ]));
        setup();
        replace_program(ROOM);
}