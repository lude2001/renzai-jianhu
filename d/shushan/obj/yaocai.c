//hanchat@txwx2005
inherit ITEM;
void create()
{
	set_name("上等药材", ({ "yaocai", "cai" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long",
			"这是蜀山山顶的稀有药材,若拿这个来练丹肯定非常有效用。\n" );
		set("unit", "株");
		set("value", 1);
	}
}