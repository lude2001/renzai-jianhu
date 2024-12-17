inherit COMBINED_ITEM;

void create()
{
	set_name("»ÆÖ½", ({"huang zhi"}));
	set_weight(1);
	if( clonep() )
		set_default_object(__FILE__);
	else
	{
		set("base_unit", "ÕÅ");
		set("base_value", 5000);
		set("base_weight", 1);
		set("long","»­·ûÓÃµÄ»ÆÖ½¡£\n");
	}
	
	set_amount(1);
	setup();
}

string query_autoload() { return query_amount() + ""; }

void autoload(string param)
{
	int amt;

	if (sscanf(param, "%d", amt) == 1)
		set_amount(amt);
}
