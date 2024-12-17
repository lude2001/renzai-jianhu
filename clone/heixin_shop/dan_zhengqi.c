
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
	set_name(HIR"����������"NOR, ({"zhengqi dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ�������ҩ�裬��˵������������ĺ�Ȼ������\n");
		set("no_sell",1);
		set("no_put", 1);
        set("no_give",1);
        set("no_drop",1);
        set("no_get",1);
        set("no_teal", 1);
		set("base_unit", "��");
		set("base_weight", 10);
		set("base_value", 10000);
		set("yuanbao", 10);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
    int var;

    if (me->is_busy())
        return notify_fail("����æ���ء�\n");

	if (me->is_fighting())
		return notify_fail("����ս���У�����ʹ��"+ name() +"��\n");

    if (me->query("combat_exp")<me->query("shen"))
        return notify_fail("��ĺ�Ȼ�����Ѽ����ˣ�����ʹ��"+ name() +"��\n");
    else {
        var=10000;
        me->add("shen",var);

        message_vision("$NС�ķ�����һ" + query("unit") + name() + "��һ�ɺ�Ȼ������Ȼ������\n", me);

	    add_amount(-1);
        return 1;
    }

}