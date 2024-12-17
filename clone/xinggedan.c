#include <ansi.h>

inherit ITEM;
//int effect;

void create()
{
	set_name(HIG "性格丹" NOR, ({ "effect dan", "xgdan"}) );
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
                set("long", "性格转换可能造成各种影响，谨慎考虑。\n");
                set("yuanbao", 300);
		set("unit", "颗");
		set("only_do_effect", 1);
	}
}
void init()
{
	add_action("effect","effect");
}
string do_effect(object me)
{
write(ZJOBLONG"请选择性格：\n"
		ZJOBACTS2+ZJMENUF(2,2,6,30)+
"狡黠多变:effect 狡黠多变"ZJSEP
		"光明磊落:effect 光明磊落"ZJSEP
		"阴险奸诈:effect 阴险奸诈"ZJSEP
		"心狠手辣:effect 心狠手辣"ZJSEP
		"敬请期待:effect 无");
		return "。。。";
}

int effect(string arg)
{
	object me = this_player();
//	 this_player()->delete_temp("maze");
	if (arg=="狡黠多变") 
	  { me->set("character", "狡黠多变");
	  write("性格转换成功!\n");
	   	destruct(this_object());}
	else
	 if (arg=="光明磊落") 
	{   me->set("character", "光明磊落");
	write("性格转换成功!\n");
	   	destruct(this_object());}
	else 
	if (arg=="心狠手辣") 
{	 me->set("character", "心狠手辣");
write("性格转换成功!\n");
	 	destruct(this_object());}
	else 
	if (arg=="阴险奸诈") 
	{ me->set("character", "阴险奸诈");
	write("性格转换成功!\n");
		destruct(this_object());}
		else 	
{	write(HIR"\n敬请期待新性格！"NOR"\n");	}	
	return 1;
}

int query_autoload() { return 1; }


