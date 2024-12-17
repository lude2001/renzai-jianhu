// tower.c
inherit ROOM;

varargs void create(int x, int y, int z)
{
    object ob;

    set("short", "ʱ�䳤��-" + y + " ��");
    set("long", @LONG
    �޾���ʱ�䳤�ӵ���,�����������Ĵ�˵��ÿһλ��˵����д���Լ��Ĺ���,û����֪����ȥ�ĳ����ж�Զ,Ҳû����֪��δ���ĳ��ӻᱼ��η���
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
		"��ս����" : "enter",
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
        return notify_fail(INPUTTXT("��������Ҫ��ս����������ע����ֻ����ʱ�䳤�ӵ�һ�����������ս��һ��ǰ�����޷���ͷ��","enter $txt#")+"\n");
    }

    sscanf(arg,"%d",level);

    if (level < 1)
    {
        return notify_fail("��ֻ������1�����µ�������\n");
    }

    if (level > 100)
    {
        return notify_fail("��ֻ������100�����µ�������\n");
    }

    me->set("god_mj/level",level);

    tell_object(me,sprintf("�����õ���ս����Ϊ%d,�������ս�ɹ����㽫���%d�㾭��Ǳ�ܡ�\n",level,level * 10000));

    return 1;
}

int valid_leave(object me, string dir)
{
    object *objs = all_inventory(this_object());
    int level = this_object()->query("level");

    if (!me->query("god_mj/level"))
        return notify_fail("����Ҫ�趨�������ս���������ܼ���ǰ����\n");

	if (dir == "south")
		return notify_fail("ʱ�䳤����Զֱ��ǰ����������ͷ��\n");
    
    foreach (object ob in objs)
    {
        if (living(ob) && ob != me)
        {
            return notify_fail("�㻹���Ȼ��ܴ˴�Ӣ����˵�ɣ�\n");
        }

    }

    if (dir == "north")
    {
        if (me->query("god_mj/level") == this_object()->query("level"))
        {
            me->add("combat_exp",10000 * level);
            me->add("potential",10000 *  level);

            tell_object(me,sprintf("��ϲ����սʱ�䳤�ӳɹ�,�����%d�㾭��Ǳ�ܡ�\n",level * 10000));
        }
    }
    
    
	return ::valid_leave(me, dir);
}

//Ӧ�ý�ֹ����ˢ�£���ֹ���캯�������ɵ�npc������\n
void reset()
{
    return;
}
