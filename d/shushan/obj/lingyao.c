//hanchat@txwx2005
inherit ITEM;
void create()
{
	set_name("灵药", ({ "ling yao", "yao" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long",
			"这是你炼制出来的灵药,不知道有多大的功效。\n" );
		set("unit", "粒");
		set("value", 1000);
	}
}