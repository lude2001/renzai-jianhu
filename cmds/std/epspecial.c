// 对天赋说明版块
/*
参数说明
myspecial/天赋id/level 天赋等级
myspecial/天赋id/experience 天赋经验

可以使用潜能增加天赋经验
每一万潜能置换一点经验
*/
#include <ansi.h>

inherit F_CLEAN_UP;


void create() { seteuid(getuid()); }

int main(object me, string arg)
{
   string msg,talent;
   int exp;
   
	if (! arg) return notify_fail("你要查看什么天赋？\n");

  if (sscanf(arg,"%s %s %d",msg,talent,exp)==3&&msg=="add")
  {
    int pot = ((int)me->query("potential") - (int)me->query("learned_points"));

    if (pot < 10000*exp)
    return notify_fail(popup("你的潜能余额貌似不足以领悟天赋。"));
    
    if (exp <= 0)
    return notify_fail(popup("你填个0，你领悟个啥？"));


    me->add("myspecial/"+talent+"/experience",exp);
    me->add("potential",-10000*exp);

    return notify_fail(popup("领悟成功，扣除潜能"+10000*exp));
  }

	if (sscanf(arg,"%s %s",msg,talent)==2&&msg=="add")
  {
    int pot = ((int)me->query("potential") - (int)me->query("learned_points"));

    if (!me->query("special_skill/"+talent))
    return notify_fail(popup("你还没有这个天赋呢！"));

    if (pot < 10000)
    return notify_fail(popup("你的潜能余额貌似不足以领悟天赋。"));

    return notify_fail(popup_input(sprintf("你目前有%d点潜能，可以提升%d点天赋经验",pot,pot/10000),"epspecial add "+talent+" "));
  }

 
  	if(sscanf(arg, "%s %s", msg,talent)==2&&msg=="rise")
  	{
  	int next_level,experience;
  	
  	next_level = me->query("myspecial/"+talent+"/level")+1;
  	experience = me->query("myspecial/"+talent+"/experience");
  	
    if (experience <= 100*next_level*next_level)
    return notify_fail("你的天赋经验不足，不能升阶\n");
     
     me->add("myspecial/"+talent+"/level",1);
     me->add("myspecial/"+talent+"/experience",-100*next_level*next_level);
    
    return notify_fail("恭喜，你的天赋升阶成功！\n");
  	}
  	
	msg = ZJOBLONG;
    msg += "天赋名称："+SPECIAL_D(arg)->name()+ZJBR;
    msg += "天赋介绍："+SPECIAL_D(arg)->explain()+ZJBR;
    msg += "天赋等级："+me->query("myspecial/"+arg+"/level")+ZJBR;
    msg += "天赋经验："+me->query("myspecial/"+arg+"/experience")+ZJBR;
    msg += HIC "≡" HIY "一一一一一一一一一一一一一一一一一一一一" HIC "≡"NOR"\n";
    msg +=ZJOBACTS2+ZJMENUF(2,2,10,25);
    msg += "使用:special "+arg+ZJSEP;
    msg += "领悟:epspecial add "+ arg + ZJSEP;
    msg += "升阶:epspecial rise "+arg;
    write(msg+"\n");
    return 1;
}
	



int help(object me)
{
	write(@HELP
指令格式 : ride | qi <生物名>
 
这个指令可以让你骑上代步的已驯养的动物。
 
HELP
    );
    return 1;
}
