private void init_player(object me);

int main(object me, string arg)
{
	string id;
	object player;
	int level;

	string id1, id2;
	object player1, player2;
	object room;

	if (sscanf(arg, "%d %s", level, id) == 2)
	{
		player = find_player(id);

		if (!userp(player) || !player->query_temp("link_ob"))
		{
			write("��ȡ�ȼ�#@#ʧ��#@#" + id + "\n");
			return 0;
		}
		else if ((level = player->query("level")) >= 0)
		{
			write("��ȡ�ȼ�#@#�ɹ�#@#" + id + "#@#" + level + "\n");
			return 1;
		}

		return 1;
	}

	if (sscanf(arg, "%s %s", id1, id2) == 2)
	{
		if (!userp(player1 = find_player(id1)) || !userp(player2 = find_player(id2)))
			return 0;

		room = new("/d/jingjichang/room");
		init_player(player1);
		init_player(player2);
		player1->move(room);
		player2->move(room);
		player1->kill_ob(player2);
		player2->kill_ob(player1);
		return 1;
	}

	return 1;
}

private void init_player(object me)
{
	me->set_override("unconcious", (: call_other, __FILE__, "check_out" :));
	me->set_override("die", (: call_other, __FILE__, "check_out" :));
	me->set_temp("backup/killer", me->query_killer());
	me->set_temp("backup/want", me->query_want());
	me->set_temp("in_pkd", 1);
	me->set("backup/condition", me->query_condition());
	me->clear_condition();
}

private void restore_status(object me)
{
	mapping my;
	mapping cnd;
	string *ks;
	int i;

	me->delete_override("unconcious");
	me->delete_override("die");
	me->delete_override("quit");
	me->remove_all_enemy(1);
	me->remove_all_killer();
	me->clear_condition();
	me->receive_damage("qi", 0);
	me->apply_killer(me->query_temp("backup/killer"));
	me->apply_want(me->query_temp("backup/want"));

	cnd = me->query("backup/condition");
	me->delete("backup/condition");
	me->delete_temp("block_msg/all");
	if (! mapp(cnd)) return;
	ks = keys(cnd);
	for (i = 0; i < sizeof(ks); i++)
		me->apply_condition(ks[i], cnd[ks[i]]);

	my = me->query_entire_dbase();
	if (my["qi"] < 1)       my["qi"] = 1;
	if (my["eff_qi"] < 1)   my["eff_qi"] = 1;
	if (my["jing"] < 1)     my["jing"] = 1;
	if (my["eff_jing"] < 1) my["eff_jing"] = 1;
}

int check_out(object me)
{
	object ob;
	mapping my;
	string msg;
	string room;
	int score;

	room = base_name(environment(me));
	if (!room->query("jingjichang"))
		return 0;

    if( ob = me->query_last_damage_from() )
            msg = WHT "\n$N��" + ob->name(1) + "������ˣ��Ǳ����ӣ�\n\n" NOR;
    else
            msg = WHT "\n$N�������ˣ��Ǳ����ӣ�\n\n" NOR;
	my = me->query_entire_dbase();
	my["eff_qi"] = my["max_qi"];
	my["eff_jing"] = my["max_jing"];
	my["qi"] = 1;
	my["jing"] = 1;

	tell_object(me, HIR "\n�������ǰһ��ģ��...�������ˣ�"NOR"\n");
	message_vision(msg, me);

	restore_status(me);
	me->move("/d/city/kedian");
	message("vision", "һ����Ӱٿ�Ĵ��˳������漴���ǡ�ž����һ�����ͼ�" + me->name() +"ˤ���˵��ϣ�һ��������������ӡ�\n", environment(me), ({ me }));
	tell_object(me, "�������У�����ñ������������������ص�ˤ���˵��ϡ�\n");
	if (! living(me))
		me->revive();
	return 1;
}