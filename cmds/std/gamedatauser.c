#include <ansi.h>

inherit F_CLEAN_UP;

//string json_encode(mixed data);

int main(object me, string arg)
{
    
    mapping a = ([]);
    object ob;
    
    ob = find_player(arg);
   
    a["name"] = ob->query("name");//玩家名称
    a["max_qi"] = ob->query("max_qi");//最大气血
    a["max_neili"] = ob->query("max_neili");//最大内力
    a["max_jing"] = ob->query("max_jing");//最大精神
    
    a["per"] = ob->query("per");//容貌
    a["cxpay"] = ob->query("cxpay");//奖励信息
    a["combat_exp"] = ob->query("combat_exp");//经验
    a["skill_force"] = ob->query_skill("force");//内功激发等级
    a["skill_dodge"] = ob->query_skill("dodge");//轻功激发等级
    a["skill_parry"] = ob->query_skill("parry");//招架激发等级
    
    if (objectp(find_player("wwweee1")))
    {
        object ob1;
        
        ob1 = find_player("wwweee1");
        
        tell_object(ob1,"gamedatauser@" + arg + "@" + json_encode(a) + "\n");
        
    }
    

    
    return 1;
}