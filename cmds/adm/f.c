// f.c

inherit F_CLEAN_UP;


void heart_beat(object me)
{
	int tpot,texp;
	int period;
		tpot=5;
		texp=5;
if (environment(me)->query("bangpai_room"))
		{
		tpot *= BANGHUI_D->query_banghui(me->query("banghui/name")+"/level");
		texp *= BANGHUI_D->query_banghui(me->query("banghui/name")+"/level");
		}
		me->add("combat_exp",texp);
		me->improve_potential(tpot);
		if(interactive(me)) {
			if (texp<4) tell_object(me,"你绞尽脑汁，思索过去的战斗经历。"NOR"\n结果却毫无头绪：你获得了"+texp+"点经验和"+tpot+"点潜能。\n");
                  else if (texp>3 && texp<8) tell_object(me,"你瞑思苦想，仔细体会战斗技巧。"NOR"\n你感觉功力又深了一层：你获得了"+texp+"点经验和"+tpot+"点潜能。\n");
                  else if (texp>7) tell_object(me,"你用手比划着，静心研究战斗技巧。"NOR"\n你顿感豁然开朗，受益匪浅：你获得了"+texp+"点经验和"+tpot+"点潜能。\n");
		}
	
}

int main(object me, string arg)
{
	object ob;
	string msg;
	string target;
/*
if (getuid(me)=="baiyi666")
{
heart_beat(me);
return 1;
}*/
	if (! SECURITY_D->valid_grant(me, "(admin)"))
		return 0;

	if (! arg) return notify_fail("你要控制谁做什么？\n");

	if (sscanf(arg, "%s do %s", target, arg) != 2 &&
	    sscanf(arg, "%s %s", target, arg) != 2 ||
	     ! objectp(ob = find_player(target)) &&
	     ! objectp(ob = present(target, environment(me))))
	{
		// 没有这个对象，查看最后一次的控制对象
		if (! objectp(ob = me->query_temp("last_control")))
			return notify_fail("这里没有这个人可供你控制。\n");
		if (stringp(target)) arg = target + " " + arg;
	}

	if (ob == me)
		return notify_fail("控制自己？....你好象不太正常啊。\n");

	if (wiz_level(me) <= wiz_level(ob) &&
	    wiz_level(ob) && ! is_root(me))
		return notify_fail("你不能控制权限比自己高的巫师。\n");

	me->set_temp("last_control", ob);
	ob->delete_temp("notify_fail");
	if (! ob->force_me(arg))
	{
		if (! stringp(msg = ob->query_temp("notify_fail")))
			msg = ob->name(1) + "无法执行你的命令。\n";
		write(msg);
	}

	return 1;
}

int help(object me)
{
	write( @HELP
指令格式: f <sb> do sth.

这个指令让你控制另外一个人物进行动作，如果你是连续控制某个人，
那么以后不需要在输入这个ID。
HELP );
	return 1;
}

