//qingyunge。c           合欢宗--青云阁

inherit ROOM;

void create()
{
        set("short", "青云阁");
	set("long", @LONG
这里是合欢宗的青云阁。通常弟子都喜欢在这里畅谈江湖中的恩怨情
仇，还不时交流各自的武功心得，以求大家武学更上一层楼。所以这里经
常是热热闹闹，和血河平日的严肃大是不同。
LONG);
	set("no_fight", 1);
	set("valid_startroom", 1);
        set("no_sleep_room",1);
	set("exits", ([	
		"southwest" : __DIR__"xuehuatang",
		"east" : __DIR__"chufang",
	]));
	setup();
}
