// Room: /d/shaolin/yidao2.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
	set("short", "大驿道");
	set("long", @LONG
一条尘土飞扬的大驿道。四周人来人往。挑担子的
行商，赶着大车的马夫，上京赶考的书生，熙熙攘攘，非常热闹。
不时还有两三骑快马从身边飞驰而过，扬起一路尘埃。东边有一个小院，据说名匠鲁班就在那里。
LONG );
	set("exits", ([
		"south" : __DIR__"yidao1",
		"north" : __DIR__"hanshui1",
		"west"  : "/d/city/shui",
		"east"  : "/d/room/xiaoyuan",
	]));
	set("outdoors", "nanyang");
	setup();
}

