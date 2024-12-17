#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
 
string query_name() { return "凝气"ZJBR"成符"; }
string *pfm_type() { return ({ "fufa", }); }

int perform(object me)
{
    object bi;
    object zhi;
    object mo;
    object fu;
    int a;
    int fu_damage;
	if (!environment(me)->query("is_jingxiu"))
	    return notify_fail("你要在武当藏经阁或全真静修室中才能使用凝气成符。\n");
	    
	if (me->is_busy())
	    return notify_fail("你现在正忙，无法使用凝气成符。\n");
	    
	if (me->is_fighting())
	    return notify_fail("你现在正在打架，无法使用凝气成符。\n");
	
	if (!living(me))
	    return notify_fail("你现在的状态无法使用凝气成符。\n");
	    
	if (me->query_skill("ningqishu", 1) < 300)
	    return notify_fail("你对凝气术的理解还不够，无法使用凝气成符。\n");
	    
	if (me->query("max_jing") < 2500)
	    return notify_fail("以你现在的精力无法画完凝气符。\n");
	
	if (me->query("max_neili") < 5000)
	    return notify_fail("以你现在的内力无法画完凝气符。\n");
	    
	if (me->query("neili") < me->query("max_neili"))
	    return notify_fail("你的内力不满，无法运转凝气术。\n");
	    
	if (me->query("jing") < me->query("max_jing") / 3)
	    return notify_fail("你的精神不满三分之一，无法运转凝气术。\n");
	    
	if (me->query("jingli") < me->query("max_jingli") / 3)
	    return notify_fail("你的精力不满三分之一，无法运转凝气术。\n");
	    
	if (!objectp(bi = present("langhao bi", me)))
	    return notify_fail("你身上没有狼毫笔。\n");
	
	if (!objectp(mo = present("zhu sha", me)))
	    return notify_fail("你身上没有朱砂。\n");
	    
	if (!objectp(zhi = present("huang zhi", me)))
	    return notify_fail("你身上没有符纸。\n");
	
	me->add("neili", -me->query("max_neili"));
	me->add("jing", -me->query("max_jing") / 3);
	me->add("jingli", -me->query("max_jingli") / 3);
	
	a = (me->query_skill("fufa", 1) + me->query_skill("taoism", 1)) / 2 + me->query_skill("force", 1) / 3;
	
	zhi->add_amount(-1);
	
	fu = new("/clone/fufa/ningqi");
	if (!objectp(fu))
	    return notify_fail("错误，请联系管理员处理。\n");
	
	fu_damage = a + random(a);
	fu->set("fu/damage", fu_damage);
	fu->set("long", fu->query("long") + "\n攻击力：" + fu_damage + "\n");
	fu->move(me);
	
	tell_object(me, "你运转凝气术，挥笔画下一道凝气符。\n");
	message("vision", me->query("name") + "运转凝气术，挥笔画下一道凝气符。\n", environment(me), ({me})); 
	me->start_busy(30);
	
	return 1;
}
