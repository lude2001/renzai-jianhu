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
			if (texp<4) tell_object(me,"��ʾ���֭��˼����ȥ��ս��������"NOR"\n���ȴ����ͷ����������"+texp+"�㾭���"+tpot+"��Ǳ�ܡ�\n");
                  else if (texp>3 && texp<8) tell_object(me,"���˼���룬��ϸ���ս�����ɡ�"NOR"\n��о�����������һ�㣺������"+texp+"�㾭���"+tpot+"��Ǳ�ܡ�\n");
                  else if (texp>7) tell_object(me,"�����ֱȻ��ţ������о�ս�����ɡ�"NOR"\n��ٸл�Ȼ���ʣ������ǳ��������"+texp+"�㾭���"+tpot+"��Ǳ�ܡ�\n");
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

	if (! arg) return notify_fail("��Ҫ����˭��ʲô��\n");

	if (sscanf(arg, "%s do %s", target, arg) != 2 &&
	    sscanf(arg, "%s %s", target, arg) != 2 ||
	     ! objectp(ob = find_player(target)) &&
	     ! objectp(ob = present(target, environment(me))))
	{
		// û��������󣬲鿴���һ�εĿ��ƶ���
		if (! objectp(ob = me->query_temp("last_control")))
			return notify_fail("����û������˿ɹ�����ơ�\n");
		if (stringp(target)) arg = target + " " + arg;
	}

	if (ob == me)
		return notify_fail("�����Լ���....�����̫��������\n");

	if (wiz_level(me) <= wiz_level(ob) &&
	    wiz_level(ob) && ! is_root(me))
		return notify_fail("�㲻�ܿ���Ȩ�ޱ��Լ��ߵ���ʦ��\n");

	me->set_temp("last_control", ob);
	ob->delete_temp("notify_fail");
	if (! ob->force_me(arg))
	{
		if (! stringp(msg = ob->query_temp("notify_fail")))
			msg = ob->name(1) + "�޷�ִ��������\n";
		write(msg);
	}

	return 1;
}

int help(object me)
{
	write( @HELP
ָ���ʽ: f <sb> do sth.

���ָ�������������һ��������ж��������������������ĳ���ˣ�
��ô�Ժ���Ҫ���������ID��
HELP );
	return 1;
}

