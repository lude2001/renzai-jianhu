//yanwuchang。c           合欢宗演武场

inherit ROOM;

void init();
int do_lian(string);

void create ()
{
        set ("short", "演武场");
        set ("long", @LONG
这里是合欢宗的演武场。你的面前是百十个设计精巧的机关人，它们
被摆放成一个奇门五行阵，只要有人走进阵中它们就会自动攻击，不时的
有人被打出阵来，这里可以练练(jin)基本的招架功夫。
LONG);
	set("exits", ([
                "southeast" : __DIR__"qixuetang",
        ]));
		set("action_list", ([
			"进阵演武" : "jin zhen",
			]));
        setup();
}

void init()
{
        add_action("do_lian", "jin");
}

int do_lian(string arg)
{
        object me;
        int jingli_cost;
        int qi_cost;

        me = this_player();

        if ( !arg || ( arg != "zhen" ) )
                return notify_fail("你想干什么？\n");

        jingli_cost = (-1) * (5 + random(15));
	qi_cost = (-1) * (1 + random(5));

	if ( me->query("qi") <= ( - qi_cost ))
		return notify_fail("你太虚弱了，再练就要出人命了。\n");

	if ( me->query("jingli") <= ( - jingli_cost ) )
		return notify_fail("你太疲劳了，没有精力练功了。\n");

	if ( (int)me->query_skill("parry", 1) < 51 )  
        {
		write("你运气于周身上下，小心翼翼的走进木人阵中，不一会儿就被打的鼻青脸肿！\n可是你对基本招架有了一点了解。\n");
	        me->add("jingli", jingli_cost);
	        me->add("qi", qi_cost);
                me->improve_skill("parry", (15 + random(me->query("int") / 2)));
        }
	else
		if ( (int)me->query_skill("parry", 1) < 101 )  
        	{
		write("你运气于四肢，迈步走进木人阵中，不断挡开木人的袭击！\n你对基本招架有了一些认识。\n");
		        me->add("jingli", jingli_cost);
		        me->add("qi", qi_cost);
        	        me->improve_skill("parry", (20 + random(me->query("int") / 2)));
	        }
		else
			write("你甩手走进木人阵中，竟没有一个木人能够打中你的身体！\n你在这里已经学不到什么了！\n");
        return 1;
}
