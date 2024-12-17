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
	set_name("枯寂人元丹", ({"kujirenyuan dan"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("value", 10000);
		set("yuanbao", 80);
		// set("no_sell",1);
		// set("no_give",1);
		// set("no_drop",1);

		set("unit", "颗");
		set("base_unit", "颗");
		set("base_weight", 10);
		set("base_value", 10000);
		//set("no_shop",1);
		set("long","这是一颗黑色的丹药，好像会增加自己的年龄。\n");
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
      if (me->is_busy())
                return notify_fail("你正忙着呢。\n");

	if (me->is_fighting())
		    return notify_fail("正在战斗中，不能使用"+ name() +"。\n");

	if (me->query("age") < 18)
	{
		me->add("potential",10000);
		tell_object(me,"你感受到了身体机能的反馈，激发了潜能获得了1万的潜能。\n");
	}

	me->add("mud_age",86400);
	tell_object(me,"你服下丹药以后，感觉身体的年龄增加了。\n");


	add_amount(-1);
	return 1;
}
