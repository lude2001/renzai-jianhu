// suxin.c��̫�����项

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>
#include <condition.h>

inherit F_DBASE;
inherit F_SSERVER;
string query_name() { return "̫��" ZJBR "����"; }
string *pfm_type() { return ({
	"sword",
}); }

int perform(object me, object target)
{
	/*      mapping prepare_status;	//��������д�����и���
			string weapon, op_weapon, op_skill, *pname, msg;
			int my_power, op_power;
			int damage;*/
	string weapon, op_weapon, op_skill, msg;
	int my_power, op_power;
	int damage, damage1;

	if (!target)
		target = offensive_target(me);
	if (!target || !target->is_character() || !me->is_fighting(target))
		return notify_fail("��̫�����项ֻ�ܶ�ս���еĶ���ʹ�á�\n");
	if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword")
		return notify_fail("��û�ý�������ʹ�á�̫�����项��\n");
	if (target && target->query_temp("apply/shade_vision"))
		return notify_fail("�Է������ˣ��㿴����" + target->query("name") + "��\n");
	if (me->query_skill("taisu-force", 1) < 500)
		return notify_fail("���̫���ľ����δ�����޷�ʩչ̫�����飡\n");
	if (me->is_busy())
		return notify_fail("��������æ���أ�\n");
	if (me->query_skill("taisu-jian", 1) < 500)
		return notify_fail("���̫�ؽ�����Ϊ���㣬������ʹ��̫�����飡\n");
	if (me->query_skill("taisu-dodge", 1) < 500)
		return notify_fail("���̫�����粽��Ϊ���㣬������ʹ��̫�����飡\n");
	if (me->query_skill("taisu-force", 1) < 500)
		return notify_fail("���̫���ľ���Ϊ���㣬������ʹ��̫�����飡\n");
	if (me->query_skill_mapped("force") != "taisu-force")
		return notify_fail("�����õĲ���̫���ľ���ʹ���ˡ�̫�����项��\n");
	if (me->query_skill_mapped("sword") != "taisu-jian")
		return notify_fail("��û��ȷ�����ü��� ��\n");
	if (!(int)me->query("breakup"))
		return notify_fail("���ζ�����δͨ,�޷�ʹ��[" HIR "̫������" NOR "]\n");
	if (me->query("max_neili") < 10000)
		return notify_fail("���������Ϊ����ʹ�á�̫�����项��\n");
	if (me->query("neili") < 1000)
		return notify_fail("�����������ʹ�á�̫�����项��\n");
	if (me->query("jingli") < 200)
		return notify_fail("��ľ�������ʹ�á�̫�����项��\n");
	if (me->query_temp("autolian"))
		return notify_fail("�����ڷ����Զ����У�\n");
	if (me->query_temp("cooldown")) // CDд��	
		return notify_fail("�㴦�ڼ�����ȴ״̬�У�������ʹ�ðɡ�\n");

	if (!objectp(op_weapon = target->query_temp("weapon")))
	{
		op_skill = "unarmed";
	}
	else
	{
		op_skill = op_weapon->query("skill_type");
	}

	message_vision(HBWHT "$N��ͨ��Ĺ��ѧ��ʹ����̫������ľ�ѧ֮���裡\n" NOR, me, target);
	me->set_temp("cooldown", 1);	 // CDд��	
	call_out("del_cooldown", 5, me); // CDд��1
	my_power = me->query_skill("taisu-jian", 1) + me->query_skill("taisu-jianfa", 1) + me->query_skill("taisu-force", 1) + me->query_skill("force") + me->query_skill("taisu-dodge", 1) + me->query_skill("sword") + me->query("bodyreset");
	op_power = target->query_skill(op_skill) + target->query_skill("dodge", 1) + target->query_skill("parry", 1) + target->query("bodyreset");
	damage1 = me->query_skill("taisu-jian", 1) + me->query_skill("taisu-jianfa", 1) + me->query_skill("taisu-force", 1) + me->query_skill("sword", 1);

	message_vision(HIY "\n$N���һ�����۱�һ���漴" + weapon->name() + HIY "���ַɳ���\n" NOR, me, target);
	message_vision(CYN "\n$N˵���������ʶһ��̫�ؽ������������ܣ�\n" NOR, me, target);
	message_vision(HIY "\nֻ��" + weapon->name() + HIY "������ת����Ȼ�û�������ѩ����ԭ����̫�ؽ����ռ������Ƿ绨ѩ�£�\n" NOR, me, target);
	message_vision(HIY "$N���С�̫�����项ȷʵ����֮�ԣ�����ѩ�����裬�����λ�һ��Ѥ�ã�ѩ�����Ī�⻯��Ƭ�̱�������ǹ����$n��\n" NOR, me, target);

	msg = HIG "����ȴ�������飡\n" NOR;
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_REGULAR);
	msg += HIR "�鵽Ũʱ��ת����\n" NOR;
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_REGULAR);
	msg += HIY "�鵽���Թ�ȣ�\n" NOR;
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_REGULAR);
	msg += HIC "�����Թ������\n" NOR;
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_REGULAR);
	msg += HIM "�����Թſ���ޣ�\n" NOR;
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_REGULAR);
	msg += HIB "�������ǲ����£�\n" NOR;
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_REGULAR);
	message_vision(msg, me, target);
	damage = damage1 + random(damage1);
	target->receive_wound("qi", damage, me);
	target->receive_damage("qi", damage / 2, me);
	me->add("neili", -1000);
	me->add("jingli", -200);
	if (userp(me) && me->query("env/no_combat_msg") < 4)
		tell_object(me, HIW "�þ��жԵ�����Ѫ������Ϊ" + damage + "������Ϊ" + damage / 2 + "��\n" NOR);

	if (me->query_skill("taisu-jian") > 2000 && me->query_skill("taisu-moon") > 2000)
	{
		damage1 = me->query_skill("taisu-jian", 1) + me->query_skill("taisu-moon", 1) + me->query_skill("taisu-force", 1) + me->query_skill("force") + me->query_skill("taisu-dodge", 1) + me->query_skill("sword") + me->query("bodyreset") + target->query_str() / 10;
		damage = damage1 + random(damage1);
		if (random(my_power) > op_power / 3)
		{
			if (objectp(op_weapon))
			{
				message_vision(HIB "\n$N����������ֻ���˾�" + op_weapon->name() + "��ͼ����������ѩ����\n" NOR, me, target);
				message_vision(WHT "$N��Ȼ���û��ڴ������е�" + op_weapon->name() + WHT "������ڵ��ϡ�\n" NOR, me, target);
				op_weapon->add_amount(-1);
				op_weapon->move(environment(me));

				message_vision(HIR "\n$Nһ���Һ���������ѩ�����������\n" NOR, me, target);
				target->receive_wound("qi", damage, me);
				target->receive_damage("qi", damage / 2, me);
				me->add("neili", -1000);
				me->add("jingli", -1000);
				if (userp(me) && me->query("env/no_combat_msg") < 4)
					tell_object(me, HIW "�þ��жԵ�����Ѫ������Ϊ" + damage + "������Ϊ" + damage / 2 + "��\n" NOR);
			}

			if (random(me->query_str()) > (target->query_str()) / 2)
			{
				message_vision(HIR "\n$N�������㣬�����̫�ؽ������˼���Ѫ����\n" NOR, me, target);
				target->receive_wound("qi", damage, me);
				target->receive_damage("qi", damage / 2, me);
				me->add("neili", -1000);
				me->add("jingli", -1000);
				if (userp(me) && me->query("env/no_combat_msg") < 4)
					tell_object(me, HIW "�þ��жԵ�����Ѫ������Ϊ" + damage + "������Ϊ" + damage / 2 + "��\n" NOR);
			}
			else
			{
				message_vision(HIR "\n$N�������㣬�����̫�ؽ������˼���Ѫ�ۡ�\n" NOR, me, target);
				target->receive_wound("qi", damage / 3, me);
				target->receive_damage("qi", damage / 5, me);
				me->add("neili", -1000);
				me->add("jingli", -200);
				if (userp(me) && me->query("env/no_combat_msg") < 4)
					tell_object(me, HIW "�þ��жԵ�����Ѫ������Ϊ" + damage / 3 + "������Ϊ" + damage / 5 + "��\n" NOR);
			}
		}
		else
		{
			message_vision(HIG "\n$N�����������ò����׽����бܹ������ŵû�����䣡\n" NOR, me, target);
			me->add("neili", -500);
		}
	}

	if (me->query_skill("taisu-jian") > 3000 && me->query_skill("taisu-dodge") > 3000)
	{
		msg = HIY "\n̫�ؽ�����ת���裬ȥ�ƾ�ʱһ�Ѿ޴��" + weapon->name() + HIY "��۶�����\n" NOR;
		message_vision(msg, me, target);
		if (me->query("jm/gumu"))
			damage1 = me->query_skill("taisu-jian", 1) * me->query("int", 1) * 3 / 2 + me->query_skill("taisu-moon", 1) * me->query("dex", 1) * 3 / 2 + me->query_skill("taisu-force", 1) * me->query("int", 1) * 3 / 2 + me->query_skill("force") + me->query_skill("taisu-dodge", 1) * me->query("dex", 1) * 3 / 2 + me->query_skill("sword") + me->query("bodyreset") + target->query_str() + target->query("jing") / 150;
		else
			damage1 = me->query_skill("taisu-jian", 1) * me->query("int", 1) + me->query_skill("taisu-moon", 1) * me->query("dex", 1) + me->query_skill("taisu-force", 1) * me->query("int", 1) + me->query_skill("force") + me->query_skill("taisu-dodge", 1) * me->query("dex", 1) / 2 + me->query_skill("sword") + me->query("bodyreset") + target->query_str() / 2 + target->query("jing") / 200;
		damage = damage1 + random(damage1);
		if (random(me->query_dex(1)) > random(target->query_dex(1) / 3))
		{
			message_vision(HIG "\n$N˫��һ�㣬��ס��" + weapon->name() + "��\n" NOR, me, target);
			target->receive_wound("qi", damage, me);
			target->receive_damage("qi", damage / 2, me);
			me->add("neili", -1000);
			me->add("jingli", -200);
			if (userp(me) && me->query("env/no_combat_msg") < 4)
				tell_object(me, HIW "�þ��жԵ�����Ѫ������Ϊ" + damage + "������Ϊ" + damage / 2 + "��\n" NOR);
		}
		else
		{
			weapon->move(environment(me));
			message_vision("\n��������һ����" + weapon->name() + "�����˵��ϣ�\n" NOR, me, target);
			me->add("jingli", -200);
		}
	}
	me->start_busy(1);
	return 1;
}

void del_cooldown(object me) // CDд��1
{
	if (!objectp(me))
		return;
	if (me->query_temp("cooldown"))
	{
		me->delete_temp("cooldown");
		tell_object(me, HIM "�����һ�����������Ľ������ջص��\n" NOR);
	}
}