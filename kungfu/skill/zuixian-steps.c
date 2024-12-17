// chaos-steps.c

inherit SKILL;

string *dodge_msg = ({
	"$nһ���������ƶˡ��������$N��һ�С�\n",
	"$n�������һ�ݣ�ʹ��һ�С��������ӡ����ܹ���$N�Ĺ�����\n",
	"$nʹ����ǧ����������ǡ�ö����$N�Ĺ��ơ�\n"
       "����$n����Ʈ��,һ�С�Ц���쳾��,����һ�ݣ����ѱܿ���\n",
       "$nʹ�������¹�����,������ת��ٿ����һ��Ų�������ߣ��ܹ�����һ�С�\n",
       "$nһ�����������ʡ�,����΢�Σ��о����յرܿ���$N��һ�С�\n"
});

int valid_enable(string usage)
{
	return (usage=="dodge");
}

int valid_learn(object me)
{
        if( (int)me->query("max_neili") < 50 )
		return notify_fail("�������������û�а취���������²���\n");

	return 1;
}

string query_dodge_msg(string limb)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( (int)me->query("qi") < 30
        ||      (int)me->query("neili") < 30 )
		return notify_fail("������������������������������²���\n");
        me->receive_damage("qi", 30);
        me->add("neili", -30);
	return 1;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
	mixed result;
	int ap, dp, mp;

	if ((int)me->query_skill("zuixian-steps", 1) < 100 ||
	    ! living(me))
		return;

	mp = ob->query_skill("count", 1);
	ap = ob->query_skill("dodge") + mp;
	dp = me->query_skill("dodge", 1) / 2 +
	     me->query_skill("zuixian-steps", 1);

	if (ap / 2 + random(ap) < dp)
	{
		result = ([ "damage": -damage ]);

		switch (random(4))
		{
		case 0:
			result += (["msg" : HIW "ֻ��$n" HIW "΢΢һЦ����������ζ���$N"
					    HIW "��ǰ��ʱ������������$n" HIW "�Ļ�Ӱ����$N"
					    HIW "��ȫ�޷������ʵ��"NOR"\n"]);
			break;
		case 1:
			result += (["msg" : HIW "$n" HIW "���Ա�����бб������һ����ȴǡ"
					    "����$N" HIW "�Ĺ���ʧ֮���塣"NOR"\n"]);
			break;
		case 2:
			result += (["msg" : HIW "$N" HIW "��һ�����ĺÿ죬Ȼ��$n"
					    HIW "һ�����ƺ����Ѱ��������ȴ��$N"
					    HIW "��һ�иպñܿ���"NOR"\n"]);
			break;
		default:
			result += (["msg" : HIW "����$n" HIW "����һԾ���Ѳ�������Ӱ��$N"
					    HIW "���д󺧣�ȴ�ּ�$n" HIW "���籼��������"
					    "֮���ɣ���������˼�����ǡ�"NOR"\n"]);
			break;
		}
		return result;
	} else
	if (mp >= 100)
	{
		switch (random(4))
		{
		case 0:
			result = HIY "ֻ��$n" HIY "΢΢һЦ����������ζ���"
				 "��ʱ������������$n" HIY "�Ļ�Ӱ������$N"
				 HIY "��ͨ������������ʵ������������"NOR"\n";
			break;
		case 1:
			result = HIY "$n" HIY "���Ա�����бб������һ����Ȼ��$N"
				 HIY "�����棬��λ���岻�"NOR"\n";
			break;
		case 2:
			result = HIY "$n" HIY "һ�����ƺ����Ѱ��������ȴ��$N"
				 HIY "��һ�иպñܿ�������$N"
				 HIY "�������У�����ȴ�ǲ�ֹ��"NOR"\n";
			break;
		default:
			result = HIY "����$n" HIY "����һԾ���Ѳ�������Ӱ��$N"
				 HIY "����˼����������У����������޷���"NOR"\n";
			break;
		}
		COMBAT_D->set_bhinfo(result);
	}
}

int query_effect_dodge(object attacker, object me)
{
	int lvl;

	lvl = me->query_skill("zuixian-steps", 1);
	if (lvl < 50)  return 0;
	if (lvl < 100) return 30;
	if (lvl < 150) return 50;
	if (lvl < 200) return 80;
	if (lvl < 250) return 100;
	if (lvl < 300) return 120;
	if (lvl < 350) return 140;
	return 150;
}