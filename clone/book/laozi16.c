// laozi16.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name( "���¾�����ʮ���¡�", ({ "jing", "daode jing" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long",
			CYN "\n"
			"\n\t\t\t��ʮ��\n\n"
			"\t���鼫���ؾ��ơ�\n"
			"\t���ﲢ�������Թ۸���\n"
			"\t����ܿܿ����������������Ի������Ի����������Ի����֪��\n"
			"Ի������֪���������ס�\n"
			"\t֪���ݣ����˹�������ȫ��ȫ���죬���˵������˾ã�û��������\n"
			""NOR"\n"
		);
		set("value", 500);
		set("material", "paper");
		set("skill", ([
			"name":	"taoism",	// name of the skill
			"exp_required":	 0,	// minimum combat experience required
			"jing_cost":    10, 	// jing cost every time study this
			"difficulty":	15,	// the base int to learn this skill
			"max_skill":	29,	// the maximum level you can learn
		]) );
	}
}