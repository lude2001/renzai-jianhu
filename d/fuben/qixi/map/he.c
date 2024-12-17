// Room: /city/beidajie1.c

inherit ROOM;
void create()
{
	set("short", "七夕之河");
	set("long", @LONG
这里就是七夕之河
LONG
	);
	set_heart_beat(20);
	setup();
}

void heart_beat()
{
	object *all;
	int a = 0;

	all = all_inventory(this_object());

	if (!sizeof(all))
	{
		destruct(this_object());
		return;
	}

	foreach (object ob in all)
	{
		if (playerp(ob))
		a =1;
	}

	if (!a)
	{
		destruct(this_object());
		return;
	}
}
