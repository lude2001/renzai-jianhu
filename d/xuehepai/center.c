
inherit ROOM;
void create()
{
        set("short","洞府中心");
        set("long",@LONG
来到这里，好象到了水帘洞，居然别有洞天。看来是合欢宗前任的
十一位掌门的坐化之地，这是合欢宗的传统：为了不让合欢宗的武学失
传。你已经来到了洞府的中心地带。
LONG );
        set("valid_startroom",1);
        set("class","合欢宗");
        set("exits",([
                "west" : __DIR__"pubulei2",
                "enter" : __DIR__"mimi",
        ]));
        set("objects",([
			"/d/xuehepai/npc/ouyang1" : 1,
			// "/kungfu/class/xuehepai/ouyang1" : 1,
        ]));
//        set("no_clean_up"， 0);
        
		setup();
        replace_program(ROOM);
}

