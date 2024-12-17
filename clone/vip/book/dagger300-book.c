// advance_force.c

inherit ITEM;

void create()
{
	set_name("基本短兵总纲三", ({ "dagger300-book"}));
	
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long",
"封面上写著「基本短兵总纲三」\n");
		set("value", 30000);
		set("material", "paper");
		set("yuanbao",1000);
		set("skill", ([
			"name": 	"dagger",
			"exp_required":	1000,
			"jing_cost":	30,
			"difficulty":	25,
			"max_skill":	300,
			"min_skill":    200,
		]));
	}
}
int query_autoload() { return 1; }