inherit ITEM;
#include <ansi.h>

void create()
{
	set_name("�Ǻ���", ({"langhao bi"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("value", 1000000);
		set("unit", "֧");
		set("long","һ֧�����������Ǻ��ʡ�\n");
	}
}

int query_autoload() { return 1; }
