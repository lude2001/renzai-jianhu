// basic_sword.c

inherit ITEM;

void create()
{
	set_name("����ȭ��", ({ "cuff book", "book" }));
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long",
"������д��������ȭ������\n");
		set("value", 100000);			  
            set("no_give",1);
            set("no_drop",1);
		set("material", "paper");
		set("skill", ([
			"name": 	"cuff",
			"exp_required":	1000,
			"jing_cost":	20,
			"difficulty":	20,
			"max_skill":	180,
		]));
	}
}
