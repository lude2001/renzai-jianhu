// flower-leaf.c
 
#include <weapon.h>
#include <ansi.h>
 
inherit THROWING;
void create()
{
	set_name(HIR"����"NOR, ({ "flower leaf", "hua ban", "ban" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "���ʵ�õ�廨�Ļ��꣬���滹���⾧Ө��¶�顣\n");
		set("unit", "��");
		set("value", 0);
		set("base_unit", "Ƭ");
		set("base_weight", 1);
		set("base_value", 0);
		set("material", "wood");
		set("damage", 2);	//Here the damage=int_throwing, added by King
		set("wield_msg", HIC"$NѸ�ٵشӰ��������ͳ�һЩõ�廨�꣬�������оʹ�������"NOR"\n");
		set("unwield_msg",HIC"$N������ʣ�µ�õ�廨�꾡���Żذ������С�"NOR"\n");
	}
	set_amount(50);
	init_throwing(2);
	setup();
}