// 这是一个由ai辅助完成的lpc程序			  
#include <ansi.h>

inherit F_CLEAN_UP;

mapping yj_f_name = (["unarmed":"真意", //基本拳脚
						 "cuff":"拳意", //基本拳法
					   "strike":"掌势", //基本掌法
					   "finger":"指诀", //基本指法
						 "hand":"手诀", //基本手法
						 "claw":"爪势", //基本爪法
						"sword":"剑意", //基本剑法
						"blade":"刀意", //基本刀法
						"staff":"杖诀", //基本杖法
					   "hammer":"锤势", //基本锤法
						 "club":"棍意", //基本棍法
						 "whip":"索意", //基本鞭法
					 "throwing":"暗诀"	//基本暗器
]);
int pop_yj(object me,string name);
int use_yj(object me,string name);
object offensive_target(object me);
int modify_attack_description(object me,string name,string newAttackDescription);
int modify_background_description(object me,string name,string newBackgroundDescription);
int modify_expend(object me,string name,int newExpend);
int modify_dodge_description(object me,string name,string newDodgeDescription);
string set_color(string arg);

int main(object me, string arg)
{ 
    string name,option,newModification;
    if (!arg)
    {
        string msg = ZJOBLONG"请选择你要查看的意境。\n";
        msg += ZJOBACTS2;
        
        if (!me->query("yijing"))
        {
            return notify_fail("你目前没有领悟任何意境。\n");
        }

        foreach (string yjName in keys(me->query("yijing")))
        {
            if (!is_chinese(yjName))
                continue;

            msg += yjName + yj_f_name[me->query("yijing/" + yjName + "/type")] + ":use_yj look " + yjName + ZJSEP;
        }

        msg += "刷新:use_yj\n";

        write(msg);
        return 1;

    }

    //判断从一个字符串匹配格式化输入3个字符
    if (sscanf(arg, "%s %s %s", name, option, newModification) == 3)
    {
        //判断是否有这个意境
        if (!me->query("yijing/" + name))
        {
            return notify_fail("你没有领悟这个意境。\n");
        }


        //统一走颜色设定接口
        newModification = set_color(newModification);

        //option为attack时调用修改意境攻击描述的函数，为dodge时调用修改闪避描述的函数,为msg时调用修改意境背景描述的函数
        if (option == "attack")
        {
            return modify_attack_description(me, name, newModification);
        }
        else if (option == "dodge")
        {
            return modify_dodge_description(me, name, newModification);
        }
        else if (option == "msg")
        {
            return modify_background_description(me, name, newModification);
        }
        else if (option == "expend")
        {
            return modify_expend(me, name, to_int(newModification));
        }
        else
        {
            return notify_fail("你要做什么？\n");
        }

    }

    if (sscanf(arg,"%s %s",option,name) == 2)
    {
        string msg;

        if (!me->query("yijing/" + name + "/msg"))
        return notify_fail("你没有这个意境。\n");

        if (option == "look")
        {
            return pop_yj(me,name);
        }

        if (option == "use")
        {
            return use_yj(me,name);
        }

        //option为attack，dodge,msg使用INPUTTXT让玩家输入新的修改
        if (option == "attack")
        {
            msg = "请设定你的攻击描述,可以使用颜色字符，例如 $HIR$为红色。$target_name$代表敌方的名字，$my_name$代表自己的名字，如果是兵器类型的意境,$weapon_name$代表自己兵器的名字。,英文斜杠+n代表换行";
            msg = INPUTTXT(msg, "use_yj " + name + " attack $txt#") + "\n";
            tell_object(me, msg);
            return 1;
        }

        if (option == "dodge")
        {
            msg = "请设定你的躲闪描述,可以使用颜色字符，例如 $HIR$为红色。$target_name$代表敌方的名字，$my_name$代表自己的名字。,英文斜杠+n代表换行";
            msg = INPUTTXT(msg, "use_yj " + name + " dodge $txt#") + "\n";
            tell_object(me, msg);
            return 1;
        }

        if (option == "msg")
        {
            msg = "请设定你的意境背景描述,可以使用颜色字符，例如 $HIR$为红色。背景你可以设定包括来源，创建灵感等信息，英文斜杠+n代表换行";
            msg = INPUTTXT(msg, "use_yj " + name + " msg $txt#") + "\n";
            tell_object(me, msg);
            return 1;
        }

        if (option == "expend")
        {
            msg = "请设定你的消耗等级（6 - 18）对应600-1800的内力消耗，6-18秒的cd。意境可以自定义消耗，内力和cd，随着付出的代价不同，可以造成的效果不同。分为四种类型，连招（6 -18），单招伤害（有效等级 *（6 - 18） / 4， 单体恢复（有效等级 * （6 - 18） / 8的气血，再恢复这个值一半的精神，即 / 4。） ";
            msg = INPUTTXT(msg, "use_yj " + name + " expend $txt#") + "\n";
            tell_object(me, msg);
            return 1;
        }


    }
	return 1;
}

int use_yj(object me,string name)
{
   
string *weaponType = ({
    "sword",   //基本剑法
    "blade",   //基本刀法
    "staff",   //基本丈法
    "hammer",  //基本锤法
    "club",	   //基本棍法
    "whip",	   //基本鞭法
});

    object weapon,target;
    string attackDesc,dodgeDesc,targetName;
    int mySkillLevel,targetSkillLevel;
    string skillType,yjSkillType,msg;
    int expend,cd;

    
    if (!me->is_fighting())
    {
        tell_object(me,"只有战斗中才可以使用意境技能。\n");
        return 1;
    }

    target = offensive_target(me);
    
    expend = me->query("yijing/" + name + "/expend");
    weapon = me->query_temp("weapon");

    skillType = me->query("yijing/" + name + "/type");
    yjSkillType = me->query("yijing/" + name + "/skill");

    mySkillLevel =  me->query_skill(skillType);
    targetSkillLevel = target->query_skill(skillType);

    attackDesc = me->query("yijing/" + name + "/attack_desc");
    dodgeDesc = me->query("yijing/" + name + "/dodge_desc");
    targetName = target->query("name");

    cd = me->query("yijing_use/cd/" + name) - time();


    if (member_array(name,weaponType) != -1 && !weapon)
    {
        if (weapon->query("skill_type") != me->query("yijing/" + name + "/type"))
        {
        tell_object(me,"你没有手持对应的兵器如何使用这个意境？\n");
        return 1;
        }
    }

    if (me->query("neili") < expend  * 150)
    {
        tell_object(me,"你的内力不足" + (expend * 150) + ",无法使用意境技能。\n");
        return 1;
    }

    if (cd > 0)
    {
        tell_object(me,sprintf("%s%s的技能还有%d秒的冷却时间，你现在无法使用该技能。\n",name,yj_f_name[skillType],cd));
        return 1;
    }

    if (weapon)
    attackDesc = replace_string(attackDesc,"$weapon_name$",weapon->query("name"));

    attackDesc = replace_string(attackDesc,"$my_name$",me->query("name"));
    attackDesc = replace_string(attackDesc,"$target_name$",targetName);

    if (weapon)
    dodgeDesc = replace_string(dodgeDesc,"$weapon_name$",weapon->query("name"));

    dodgeDesc = replace_string(dodgeDesc,"$my_name$",me->query("name"));
    dodgeDesc = replace_string(dodgeDesc,"$target_name$",targetName);

    attackDesc = replace_string(attackDesc,ZJBR,"\n");
    dodgeDesc = replace_string(dodgeDesc,ZJBR,"\n");

    msg = HIC + me->query("name") + "全身内劲爆发，使出了" + name + yj_f_name[skillType] + NOR"。\n";
    msg += attackDesc + "\n";


    msg += "我方命中系数:" + mySkillLevel + "--\n";
    msg += "敌方命中系数:" + targetSkillLevel + "--\n";
    
    if (mySkillLevel / 4 + random(mySkillLevel / 2) > targetSkillLevel / 2)
    {

        if (yjSkillType == "连招")
        {
            for (int i = 0; i < expend; i++)
            {
                if (! me->is_fighting(target))
                    break;
                if (random(5) < 2 && ! target->is_busy())
                    target->start_busy(1);
                
                if (!weapon)
                COMBAT_D->do_attack(me, target, 0, 0);
                else
                COMBAT_D->do_attack(me, target, weapon, 0);

                message_vision(msg, me, target);
                return 1;
            }
        }
        else if (yjSkillType == "单招伤害")
        {
            target->receive_damage("qi", mySkillLevel * expend / 3,me);
            target->receive_wound("qi", mySkillLevel * expend / 3,me);
            msg += HIC + targetName + "受到了"HIR + (mySkillLevel * expend / 3) + NOR"点气血的伤害。\n";
        }
        else if (yjSkillType == "单招恢复")
        {
            int qixue;
            qixue = mySkillLevel * expend / 4;
            me->receive_curing("qi",qixue);
            me->receive_curing("jing",qixue / 2);
            msg += HIC + me->query("name") + "恢复了"HIG + (qixue) + NOR"点气血。\n";
            msg += HIC + me->query("name") + "恢复了"HIG + (qixue / 2) + NOR"点精神。\n";
        }

    }
    else
    {
        msg += dodgeDesc;
    }

    msg += "\n";

    me->set("yijing_use/cd/" + name,time() + expend);
    me->add("neili",- expend * 150);

    if (environment(me)->query("short") != "刀剑归墟")
    message_vision(msg, me, target);

    return 1;

}
int pop_yj(object me,string name)
{
    string msg = ZJOBLONG"意境名称:" + name + "\n";

    msg += "意境背景描述:" + me->query("yijing/" + name + "/msg") + "\n";
    msg += "意境攻击描述:" + me->query("yijing/" + name + "/attack_desc") + "\n";
    msg += "意境闪避描述:" + me->query("yijing/" + name + "/dodge_desc") + "\n";
    msg += "意境消耗等级:" + me->query("yijing/" + name + "/expend") + "\n";
    msg += "技能类型:" + me->query("yijing/" + name + "/skill") + "\n";
    msg += "意境类型:" + yj_f_name[me->query("yijing/" + name + "/type")] + "\n";

    msg = replace_string(msg,"\n",ZJBR);
    msg += "--------------\n";
    msg += ZJOBACTS2;
    msg += "修改背景描述:use_yj msg "+ name +ZJSEP;
    msg += "修改攻击描述:use_yj attack "+ name +ZJSEP;
    msg += "修改闪避描述:use_yj dodge "+ name +ZJSEP;
    msg += "修改消耗等级:use_yj expend "+ name + ZJSEP;
    msg += "使用:use_yj use " + name + "\n";

    tell_object(me,msg);
    return 1;
}

object offensive_target(object me)
{
  me->clean_up_enemy();
  return me->select_opponent();
}

//修改意境攻击描述
int modify_attack_description(object me,string name,string newAttackDescription)
{

    //判断玩家是否有这个意境
    if (! me->query("yijing/" + name))
    {
        tell_object(me,"你没有这个意境。\n");
        return 1;
    } 

    //判断新的攻击描述需要在1-200字之间
    if ((strlen(newAttackDescription) < 2) || (strlen(newAttackDescription) > 400))
    {
        tell_object(me, "对不起，你的意境攻击描述不能太长或太短（1-200字）。\n");
        return 1;
    }

    //判断是否拥有200元宝
    if (me->query("yuanbao") < 200)
    {
        tell_object(me,"你的元宝不足。\n");
        return 1;
    }

    //扣除200元宝
    me->add("yuanbao",-200);


    //设定新的攻击描述
    me->set("yijing/" + name + "/attack_desc",newAttackDescription);

    //告诉玩家修改完成
    tell_object(me,"修改完成。\n");

    //显示玩家意境
    pop_yj(me,name);


    return 1;


}


//修改意境闪避描述
int modify_dodge_description(object me,string name,string newDodgeDescription)
{

    //判断玩家是否有这个意境
    if (! me->query("yijing/" + name))
    {
        tell_object(me,"你没有这个意境。\n");
        return 1;
    }

    //判断新的闪避描述需要在1-200字之间
    if ((strlen(newDodgeDescription) < 2) || (strlen(newDodgeDescription) > 400))
    {
        tell_object(me, "对不起，你的意境闪避描述不能太长或太短（1-200字）。\n");
        return 1;
    }

    //判断是否拥有200元宝
    if (me->query("yuanbao") < 200)
    {
        tell_object(me,"你的元宝不足。\n");
        return 1;
    }

    //扣除200元宝

    me->add("yuanbao",-200);

    //设定新的闪避描述
    me->set("yijing/" + name + "/dodge_desc",newDodgeDescription);

    //告诉玩家修改完成
    tell_object(me,"修改完成。\n");

    //显示玩家意境
    pop_yj(me,name);

    return 1;

}

//修改意境背景描述
int modify_background_description(object me,string name,string newBackgroundDescription)
{

    //判断玩家是否有这个意境
    if (! me->query("yijing/" + name))
    {
        tell_object(me,"你没有这个意境。\n");
        return 1;
    }


    //判断新的背景描述需要在1-300字之间
    if ((strlen(newBackgroundDescription) < 2) || (strlen(newBackgroundDescription) > 600))
    {
        tell_object(me, "对不起，你的意境背景描述不能太长或太短（1-300字）。\n");
        return 1;
    }

    //判断是否拥有200元宝
    if (me->query("yuanbao") < 200)
    {
        tell_object(me,"你的元宝不足。\n");
        return 1;
    }

    //扣除200元宝
    me->add("yuanbao",-200);

    //设定新的背景描述
    me->set("yijing/" + name + "/msg",newBackgroundDescription);

    //告诉玩家修改完成
    tell_object(me,"修改完成。\n");
    
    //显示玩家意境
    pop_yj(me,name);

    return 1;

}

//修改意境消耗等级
int modify_expend(object me,string name,int newExpend)
{

    //判断玩家是否有这个意境
    if (! me->query("yijing/" + name))
    {
        tell_object(me,"你没有这个意境。\n");
        return 1;
    }

    //判断是否拥有200元宝
    if (me->query("yuanbao") < 200)
    {
        tell_object(me,"你的元宝不足。\n");
        return 1;
    }

    //判断玩家的意境消耗等级是否在6-18之间
    if (newExpend < 6 || newExpend > 18)
    {
        tell_object(me,"意境消耗等级必须在6-18之间。\n");
        return 1;
    }

    //扣除200元宝
    me->add("yuanbao",-200);

    //设定新的消耗等级
    me->set("yijing/" + name + "/expend",newExpend);

    //告诉玩家修改完成
    tell_object(me,"修改完成。\n");

    //显示玩家意境
    pop_yj(me,name);

    return 1;

}

string set_color(string arg)
{
	arg = replace_string(arg, "$BLK$", BLK);
	arg = replace_string(arg, "$RED$", RED);
	arg = replace_string(arg, "$GRN$", GRN);
	arg = replace_string(arg, "$YEL$", YEL);
	arg = replace_string(arg, "$BLU$", BLU);
	arg = replace_string(arg, "$MAG$", MAG);
	arg = replace_string(arg, "$CYN$", CYN);
	arg = replace_string(arg, "$WHT$", WHT);
	arg = replace_string(arg, "$HIR$", HIR);
	arg = replace_string(arg, "$HIG$", HIG);
	arg = replace_string(arg, "$HIY$", HIY);
	arg = replace_string(arg, "$HIB$", HIB);
	arg = replace_string(arg, "$HIM$", HIM);
	arg = replace_string(arg, "$HIC$", HIC);
	arg = replace_string(arg, "$HIW$", HIW);
	arg = replace_string(arg, "$NOR$", NOR);

	return arg;
}