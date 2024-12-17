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
	set_name("�ݼ���Ԫ��", ({"kujirenyuan dan"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("value", 10000);
		set("yuanbao", 80);
		// set("no_sell",1);
		// set("no_give",1);
		// set("no_drop",1);

		set("unit", "��");
		set("base_unit", "��");
		set("base_weight", 10);
		set("base_value", 10000);
		//set("no_shop",1);
		set("long","����һ�ź�ɫ�ĵ�ҩ������������Լ������䡣\n");
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
      if (me->is_busy())
                return notify_fail("����æ���ء�\n");

	if (me->is_fighting())
		    return notify_fail("����ս���У�����ʹ��"+ name() +"��\n");

	if (me->query("age") < 18)
	{
		me->add("potential",10000);
		tell_object(me,"����ܵ���������ܵķ�����������Ǳ�ܻ����1���Ǳ�ܡ�\n");
	}

	me->add("mud_age",86400);
	tell_object(me,"����µ�ҩ�Ժ󣬸о���������������ˡ�\n");


	add_amount(-1);
	return 1;
}
