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
			write("获取等级#@#失败#@#" + id + "\n");
			return 0;
		}
		else if ((level = player->query("level")) >= 0)
		{
			write("获取等级#@#成功#@#" + id + "#@#" + level + "\n");
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
            msg = WHT "\n$N被" + ob->name(1) + "打成重伤，狼狈而逃！\n\n" NOR;
    else
            msg = WHT "\n$N身受重伤，狼狈而逃！\n\n" NOR;
	my = me->query_entire_dbase();
	my["eff_qi"] = my["max_qi"];
	my["eff_jing"] = my["max_jing"];
	my["qi"] = 1;
	my["jing"] = 1;

	tell_object(me, HIR "\n你觉得眼前一阵模糊...这下完了！"NOR"\n");
	message_vision(msg, me);

	restore_status(me);
	me->move("/d/city/kedian");
	message("vision", "一个黑影倏的窜了出来，随即就是“啪”的一声，就见" + me->name() +"摔倒了地上，一副半死不活的样子。\n", environment(me), ({ me }));
	tell_object(me, "半昏半迷中，你觉得被人拎了起来，又重重的摔倒了地上。\n");
	if (! living(me))
		me->revive();
	return 1;
}