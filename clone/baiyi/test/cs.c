// advance_force.c

inherit ITEM;

void create()
{
	set_name("book_name", ({ "book_id"}));
	
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "±æ");
		set("long",
"∑‚√Ê…œ–¥÷¯°∏book_name°π\n");
		set("value", 30000);
		set("material", "paper");
		set("yuanbao",yuanbao_number);
		set("skill", ([
			"name": 	"skill_id",
			"exp_required":	1000,
			"jing_cost":	30,
			"difficulty":	25,
			"max_skill":	max_level,
			"min_skill":    min_level,
		]));
	}
}
