inherit ITEM;
void create()
{
        set_name( "蜀山仙术", ({ "book", "shu" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "上面写了蜀山仙风云体术。\n");
                set("value", 500);
                set("material", "paper");
                      set("skill", ([
			"name": "xianfeng-spells",
             "exp_required": 100000,
                "jing_cost": 300,
              "difficulty": 300,
	              "max_skill": 50,
]) );
        }
}

