inherit ROOM;

int do_drop(object me, object obj, int raw);

void create()
{
	set("short", "������");
	set("long", @LONG
�����������Զ����޷������Ķ�����
LONG);
	
	set("exits", ([




	"northeast" : __DIR__"guangchang",
		]));
	setup();
}

void init()
{
	add_action("do_drop_main", "drop");
	add_action("disable", "get");
}

int do_drop_main(string arg)
{
	object obj, *inv, obj2, me;
	int i, amount;
	mixed info;
	string item;
	
	me = this_player();
	if (! arg)
		return notify_fail("��Ҫ����ʲô������\n");

	if (sscanf(arg, "%d %s", amount, item) == 2)
	{
		if (! objectp(obj = present(item, me)))
			return notify_fail("������û������������\n");

		if (wiz_level(me) < 3 && !(info = obj->query("no_drop")))
		{
			tell_object(me, ( obj->name() + "������������������\n"));
			return 0;
		}

		if (! obj->query_amount())
			return notify_fail( obj->name() + "���ܱ��ֿ�������\n");

		if (amount < 1)
			return notify_fail("����������������һ����\n");

		if (amount > obj->query_amount())
			return notify_fail("��û����ô���" + obj->name() + "��\n");
		else if (amount == (int)obj->query_amount())
			return do_drop(me, obj, 0);
		else
		{
			obj->set_amount((int)obj->query_amount() - amount);
			obj2 = new(base_name(obj));
			obj2->set_amount(amount);
			if (! do_drop(me, obj2, 0))
			{
				obj2->move(me);
				return 0;
			}
			return 1;
		}
	}

	if (arg == "all")
	{
			write("��ֻ��һ��һ���Ķ�����\n");
			return 1;

		inv = all_inventory(me);
		for(amount = 0, i = 0; i < sizeof(inv); i++)
		{
			if (! living(me)) break;
			amount += do_drop(me, inv[i], 1);
		}

		if (! amount)
		{
			write("��ʲô��û�ж�����\n");
			return 1;
		}

		message("vision", me->name() + "������һ�Ѷ�����\n",
			environment(me), ({ me }));
		write("�����ˡ�\n");
		return 1;
	}

	if (! objectp(obj = present(arg, me)))
		return notify_fail("������û������������\n");

	do_drop(me, obj, 0);
	return 1;
}

int do_drop(object me, object obj, int raw)
{
	mixed no_drop;
	object riding;

	if (obj == (riding = me->query_temp("is_riding")))
	{
		message_vision("$N��$n���Ϸ������¡�\n", me, riding);
		me->delete_temp("is_riding");
		obj->delete_temp("is_rided_by");
		obj->move(environment(me));
		return 1;
	}

	if (!clonep(obj))
	{
		write(obj->query("name")+"����һ��������ʧ�ˣ���\n");
		destruct(obj);
		return 1;
	}

	if (wiz_level(me) < 3 && !(obj->query("no_drop")))
		{
			write("�������������������������\n");
			return 0;
		}

	if (no_drop = environment(me)->query("no_drop"))
		return notify_fail(stringp(no_drop) ? no_drop : "���ﶫ��������ȥҲ��������\n");

	switch ((string)obj->query("equipped"))
	{
	case "worn":
		tell_object(me, obj->name() + "�������������ܶ�����\n");
		return 0;

	case "wielded":
		tell_object(me, obj->name() + "������װ�����ܶ�����\n");
		return 0;
	}
/*
	if (! obj->is_character() &&
	    ! obj->can_combine_to(environment(me)) &&
	    sizeof(filter_array(all_inventory(environment(me)),
				(: ! $1->is_character() :))) > MAX_ITEM_IN_ROOM)
	{
		tell_object(me, "���ﶫ��̫���ˣ����Ҷ�����" + obj->name() + "���Ҳ����ˡ�\n");
		return 0;
	}*/
/*
	if (wiz_level(me) < 3 &&  obj->query("no_drop"))
	{
		tell_object(me, "��������������㶪����\n");
		return 0;
	}
*/
	if (obj->move(environment(me)))
	{
		if (obj->is_character() && obj->query_weight() > 20000)
			message_vision("$N��$n�ӱ��Ϸ������������ڵ��ϡ�\n", me, obj);
		else
		{
			if (! raw)
				message_vision(sprintf("$N����%s%s$n��\n",
							obj->query_amount()?CHINESE_D->chinese_number(obj->query_amount()):"һ",
						       obj->query_amount()?obj->query("base_unit"):obj->query("unit")), me, obj);
			else
				write("�㶪����"+obj->query_amount()?CHINESE_D->chinese_number(obj->query_amount()):"һ" 
					+ obj->query_amount()?obj->query("base_unit"):obj->query("unit") +  obj->name() + "\n");
			destruct(obj);
			/*if (! obj->is_character() && ! obj->query("value") && ! obj->value())
			{
				//write("��Ϊ��������û�о����ֵ���������ǲ�����ע�⵽���Ĵ��ڡ�\n");
                        write(obj->query("name")+"��������ʧ�ˡ�\n");
				destruct(obj);
			}*/
		}
		return 1;
	}

	return 0;
}
