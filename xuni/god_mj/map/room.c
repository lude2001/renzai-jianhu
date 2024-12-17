// tower.c
inherit ROOM;

varargs void create(int x, int y, int z)
{
    object ob;

    set("short", "时间长河-" + y + " 里");
    set("long", @LONG
    无尽的时间长河当中,诞生出无数的传说，每一位传说都书写者自己的故事,没有人知道过去的长河有多远,也没有人知道未来的长河会奔向何方。
LONG);

    ob = new("/xuni/god_mj/npc/ying",y);
    ob->move(this_object());

    set("level",y);

    if (y >= 101)
    {
        set("exits", ([
            "south":__DIR__ "room/" + x + "," + (y - 1) + "," + z,
        ]));
    }
    else
    if (y > 1)
    {
      set("exits", ([
        "north":__DIR__ "room/" + x + "," + (y + 1) + "," + z,
        "south":__DIR__ "room/" + x + "," + (y - 1) + "," + z,
      ]));
    }
    else
    {
        set("exits", ([
            "north":__DIR__ "room/" + x + "," + (y + 1) + "," + z,
        ]));
    }

    if (y == 1)
    set("action_list", ([
		"挑战设置" : "enter",
	]));

}
void init()
{
	add_action("do_enter", "enter");
}

int do_enter(string arg)
{
    int level;
    object me = this_player();

    if (!arg)
    {
        return notify_fail(INPUTTXT("请输入需要挑战的里数，请注意你只能在时间长河第一里进行设置挑战，一旦前进将无法回头：","enter $txt#")+"\n");
    }

    sscanf(arg,"%d",level);

    if (level < 1)
    {
        return notify_fail("你只能设置1里以下的里数。\n");
    }

    if (level > 100)
    {
        return notify_fail("你只能设置100里以下的里数。\n");
    }

    me->set("god_mj/level",level);

    tell_object(me,sprintf("你设置的挑战层数为%d,如果你挑战成功，你将获得%d点经验潜能。\n",level,level * 10000));

    return 1;
}

int valid_leave(object me, string dir)
{
    object *objs = all_inventory(this_object());
    int level = this_object()->query("level");

    if (!me->query("god_mj/level"))
        return notify_fail("你需要设定你决定挑战的里数才能继续前进。\n");

	if (dir == "south")
		return notify_fail("时间长河永远直往前方，永不回头。\n");
    
    foreach (object ob in objs)
    {
        if (living(ob) && ob != me)
        {
            return notify_fail("你还是先击败此处英魂再说吧！\n");
        }

    }

    if (dir == "north")
    {
        if (me->query("god_mj/level") == this_object()->query("level"))
        {
            me->add("combat_exp",10000 * level);
            me->add("potential",10000 *  level);

            tell_object(me,sprintf("恭喜你挑战时间长河成功,获得了%d点经验潜能。\n",level * 10000));
        }
    }
    
    
	return ::valid_leave(me, dir);
}

//应该禁止房间刷新，防止构造函数中生成的npc被清理。\n
void reset()
{
    return;
}
