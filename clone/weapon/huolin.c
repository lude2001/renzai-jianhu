#include <weapon.h>

inherit SWORD;
#include <ansi.h>

void create()
{
set_name(HIY"火"+HIR"麟"+HIC"剑"NOR, ({ "huolin jian", "jian","huolin", "sword" }) );	
set_weight(15000);	
if( clonep() )
set_default_object(__FILE__);
else {
set("weapon_prop/karma", 15);	
set("weapon_prop/intelligence", 5);	
set("weapon_prop/strength", 35);	
set("unit", "把");
set("icon", "10020");
set("value", 30000000); 	
set("material", "steel");
set("long", "传说中的邪剑，剑身通体火红,搭配翡翠般绿的剑柄显得格外耀眼,据说此剑极具灵性,剑心邪异,是武林霸权的象征。\n");	
set("wield_msg", HIR"只听^铮^的一声,$n"+HIR"脱鞘弹射半空幻做一片红霞当头罩下,天地间顿时变得炽热异常.....\n"           	
YEL"红光闪烁隐约中一头全身喷火的麒麟恶扑而下，$N对其一招手中无声无息地多了把通体火红的$n。\n"NOR);      	
set("unwield_msg", HIR "$N举剑望空一挥$n"+HIR"脱手飞出,剑身发出刺眼红光,顿时空气中邪气更盛,红光再闪已然消失不见,定睛一看$n"+HIR"已入鞘中.\n"NOR);  	
} 

init_sword(500,2);      	
setup();
}
int hit_ob(object me,object victim,int damage_bonus)
{
victim->apply_condition("fire_poison", 200);
victim->start_busy(1);
return damage_bonus;
}
void init()	
{	
if(this_player()!=environment())	
add_action("do_get","get");	
}	
int do_get(string arg)	
{	
object me=this_player();	
object ob=this_object();	
string place;	
if(environment(ob)->query("short"))	
place = environment(ob)->query("short");	
else place = "一个不为人知的地方";	
if(arg=="huolin jian"){                  		
if(ob->move(me))	
message("channel:rumor",HIW"\n〖江湖传闻〗：听说"+me->name()+"在"+place+"弄到了一把"HIY"火"HIR"麟"HIC"剑\n\n"NOR,users());        	
me->add("jing",-(me->query("max_jing")/3));
me->set("neili",0);
return 1;	
}	
return 0;	
}	
int query_autoload() { return 1; }
