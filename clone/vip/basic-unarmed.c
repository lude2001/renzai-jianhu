// basic_sword.c

inherit ITEM;

void create()
{
	set_name("基础拳脚", ({ "unarmed book", "book" }));
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long",
"封面上写著「基础拳脚）」\n");
		set("value", 100000);			  
            set("no_give",1);
            set("no_drop",1);
		set("material", "paper");
		set("skill", ([
			"name": 	"unarmed",
			"exp_required":	1000,
			"jing_cost":	20,
			"difficulty":	20,
			"max_skill":	180,
		]));
	}
}
