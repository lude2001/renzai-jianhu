inherit ROOM;

void create()
{
	set("short", "竞技场");
	set("long", "竞技场\n");

	set("jingjichang", 1);
	setup();
	if (clonep())
		set_heart_beat(1);
}

void init()
{
	add_action("disable", ({"use", "eat", "fu", "fly", "flygo", "walk", "recall"}));
}

int disable(string arg)
{
	write("这里无法使用这个指令。\n");
	return 1;
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

void player_win(object  me)
{
	object ob;
	mapping my;
	string msg;

	my = me->query_entire_dbase();
	my["jing"]   = my["eff_jing"]   = my["max_jing"];
	my["jingli"] = my["eff_jingli"] = my["max_jingli"];
	my["qi"]     = my["eff_qi"]     = my["max_qi"]+me->query_gain_qi();
	my["neili"]  = my["max_neili"];

	tell_object(me, HIR "\n恭喜你获得胜利！"NOR"\n");

	if(me->is_busy())
		me->interrupt_me(me,me->query_busy());

	restore_status(me);
	me->move("/d/city/kedian");
}

void heart_beat()
{
	object * player;

	player = filter_array(all_inventory(), (: userp($1) :));


	if (sizeof(player) == 2)
		return ;

	if (!sizeof(player))
	{
		destruct(this_object());
		return ;
	}

	if (sizeof(player) == 1)
	{
		player_win(player[0]);
		return ;
	}
}