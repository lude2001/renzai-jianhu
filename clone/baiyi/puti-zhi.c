// puti-zi.c ������
#include <ansi.h>

inherit COMBINED_ITEM;

string query_autoload() { return query_amount() + ""; }

void autoload(string param)
{
	int amt;

	if (sscanf(param, "%d", amt) == 1)
		set_amount(amt);
}

void setup()
{
	set_amount(1);
	::setup();
}
void create()
{
	set_name(HIG "������" NOR, ({"puti zi-s", "zi"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("base_unit", "��");
		set("base_weight", 10);
		set("base_value", 100);
		set("long", HIG "����һ�ž�Ө����������ӣ�������ɽ������"
			    "ǰ����ϡ�ޱȣ�\n������������֮ʵ�����ܻ��ٽ�"
			    "����ǧ�֣������ͬ�١�\n");
		set("value", 50000);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	if ((int)me->query_condition("putizi_drug") > 0)
	{
		write("�����������Ϣδ���������������ܸе������嵴����"
		      "��óȻ��ʳ��\n");
		return 1;
	} else
	if (me->improve_neili(20 + random(31)))
	{
		me->set("neili", me->query("max_neili"));

		message_vision(HIY "$N" HIY "����һ�������ӣ���Ȼ��ֻ��һ�ɺ�"
			       "���ޱȵ�����ֱ�嶥�ţ���æ�˹����ɡ�"NOR"\n",
			       me);
		me->apply_condition("putizi_drug", 1000);
	} else
	{
		message_vision(HIY "$N" HIY "һ������������һ�������ӡ�"NOR"\n",
			       me);
		tell_object(me, "�����ûɶ�о������绨���óԡ�\n");
	}

	me->start_busy(random(5) + 5);
    add_amount(-1);
	return 1;
}