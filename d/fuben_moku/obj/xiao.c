#include <weapon.h>
inherit XSWORD;

void create()
{
	set_name("Ӱ��", ({ "xiao" }));
	set_weight(7000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "֧");
		set("long", "����а�����۶��ɵ�һ֧�\n");
	    set("no_get", 1);
		set("material", "а��");
		set("wield_msg", "$N��ৡ���һ�����һ֧$n�������С�\n");
		set("unwield_msg", "$N�����е�$n��ؽ��ʡ�\n");
	}
	
	init_xsword(10);
	setup();
}