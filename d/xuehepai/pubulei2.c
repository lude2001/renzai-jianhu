
inherit ROOM;
void create()
{
        set("short","洞府");
        set("long",@LONG
来到这里，好象到了水帘洞，居然别有洞天。看来是合欢宗前任的
十一位掌门的坐化之地，这是合欢宗的传统：为了不让合欢宗的武学失
传。快去找找吧，说不定会有什么奇遇。。。。
LONG );
        set("valid_startroom",1);
        set("class","合欢宗");
       set("exits",([
                "south" : __DIR__"pubulei1",
                "east" : __DIR__"center",
        ]));
//        set("no_clean_up"， 0);
        setup();
           replace_program(ROOM);
}


