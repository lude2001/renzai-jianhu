//zrping。c           龙门后山—朝日坪

#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
        set("short", HIW"朝日坪"NOR);
	set("long", @LONG
这里是后山朝日坪。据说合欢宗开山祖师在此坐化，因此派内众弟子
不时上来在此苦修武技，更希望能发现祖师遗迹，求得本派高深武学？？
？，一株万年古松自山崖外长了上来，高耸入云。
LONG);
	set("exits", ([
                        "east" : __DIR__"houshan",
	]));
	set("item_desc", ([
		"shu" : "这株古松据说是万年前盘古开天时生长而成的。\n",
	]));

	set("action_list", ([
		"爬树" : "pa shu",
		]));
        set("outdoors","龙门");
        set("valid_startroom",1);
	setup();
}

void init()
{
	add_action("do_climb","climb");
	add_action("do_climb","pa");
}

int do_climb(string arg)
{
	object ob;
       ob=this_player();

	if ( arg && arg == "shu" )
	{
                if ( (int)ob->query_skill("dodge", 1) < 100 )
		{
			tell_object(ob, HIR "你的功夫还不够高，爬上去恐怕会摔死的。\n" NOR, ob);
			return 1;
		}

		message_vision(HIC "$N攀着繁茂的树枝一步步爬了上去。\n" NOR, ob);
		ob->move(__DIR__"shugan1");
		return 1;
	}
	else
		return notify_fail("你要向哪里爬？\n");
}