//book_blade.c

inherit ITEM;

void create()
{
	set_name("��������顽", ({"blade book", "book"}));
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else 
	{
		set("unit", "��");
		set("value", 1000);
		set("material", "paper");
		set("skill", ([
			"name": "blade",
			"exp_required": 100,
			"sen_cost": 20,
			"difficulty": 20,
			"max_skill": 20,
		]));
	}
}
