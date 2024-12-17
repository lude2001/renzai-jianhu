// advance_force.c

inherit ITEM;

void create()
{
	set_name("基本杖法总纲五", ({ "staff500-book"}));
	
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long",
"封面上写著「基本杖法总纲五」\n");
		set("value", 30000);
		set("material", "paper");
		set("yuanbao",3000);
		set("skill", ([
			"name": 	"staff",
			"exp_required":	1000,
			"jing_cost":	30,
			"difficulty":	25,
			"max_skill":	500,
			"min_skill":    400,
		]));
	}
}
int query_autoload() { return 1; }