// advance_force.c

inherit ITEM;

void create()
{
	set_name("�����Ṧ�ܸ�һ", ({ "dodge100-book"}));
	
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long",
"������д���������Ṧ�ܸ�һ��\n");
		set("value", 30000);
		set("material", "paper");
		set("yuanbao",1000);
		set("skill", ([
			"name": 	"dodge",
			"exp_required":	1000,
			"jing_cost":	30,
			"difficulty":	25,
			"max_skill":	100,
			"min_skill":    0,
		]));
	}
}
int query_autoload() { return 1; }