// advance_force.c

inherit ITEM;

void create()
{
	set_name("�����ȷ��ܸ���", ({ "staff400-book"}));
	
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long",
"������д���������ȷ��ܸ��ġ�\n");
		set("value", 30000);
		set("material", "paper");
		set("yuanbao",3000);
		set("skill", ([
			"name": 	"staff",
			"exp_required":	1000,
			"jing_cost":	30,
			"difficulty":	25,
			"max_skill":	400,
			"min_skill":    300,
		]));
	}
}
int query_autoload() { return 1; }