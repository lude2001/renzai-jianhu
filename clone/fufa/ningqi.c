inherit ITEM;

void create()
{
	set_name("凝气符", ({"ningqi fu"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("value", 10000);
		set("unit", "张");
		set("no_put", 1);
		set("long","一张绘制完成的凝气符，感觉里面蕴藏巨大威能。\n");
	}
	set("only_do_effect", 1);
}

int do_effect(string arg)
{
    object * enemys;
    int random;
    int fu_damage;
    object who;
    
    who = this_player();
    
    if (!who->is_fighting())
    {
        write("只有战斗中才能使用凝气符。\n");
        return 1;
    }
     
     if (who->is_busy())
     {
         write("你正忙，无法使用凝气符。\n");
         return 1;
     }
    
    enemys = who->query_enemy();
    fu_damage = query("fu/damage");
    
    if (sizeof(enemys))
    {
        random = random(sizeof(enemys));
        
        if (!living(enemys[random]))
        {
            write("敌人都已经这样了，就不必使用凝气符了。\n");
            return 1;
        }
        
        if (who->query("family/family_name") == "武当派" || who->query("family/family_name") == "全真教")
        {
            enemys[random]->receive_wound("qi", fu_damage, who);
            who->start_busy(6);
            message_combatd(HIW"$N取出一张绘制特殊符咒的黄纸，口颂咒语，符咒化作火球射向$n胸膛。"NOR"\n" + "$n受到" + fu_damage + "伤害。\n", who, enemys[random]);
        }
        else
        {
            enemys[random]->receive_wound("qi", fu_damage / 2, who);
            who->start_busy(6);
            message_combatd(HIW"$N取出一张绘制特殊符咒的黄纸，口颂咒语，符咒化作火球射向$n胸膛。"NOR"\n" + "$n受到" + fu_damage / 2 + "伤害。\n", who, enemys[random]);
        }
    }
    else
    {
        write("你现在没有敌人哦。\n");
        return 1;
    }
    
    destruct(this_object());
    return 1;
}