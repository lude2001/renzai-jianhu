#include <ansi.h>

int start_ken(object me);
int main(object me, string arg)
{ 
string str;
    if (! arg){
        str = ZJOBLONG"奖池当前有百分之4的几率抽到宝石，百分之五抽到公共技能";
        str += ZJBR"150元宝抽一次, 1400元宝十连。";
        str += ZJBR"建议经验足够技能提升到180级再进行抽奖！";
        str += ZJBR"否则抽到公共技能下线等级会掉！！";
        str += ZJBR"概不负责！！";
        str += "\n"ZJOBACTS2+ZJMENUF(4,4,8,30); 
        if (present("ten card",me))
        	str += "十连抽:luckdraw ten"ZJSEP;
        if  (present("one card",me))
        	str += "单抽卡:luckdraw one"ZJSEP;
        str += "元宝单抽:luckdraw yuanbao"ZJSEP;
        str += "元宝十连:luckdraw yuanbao_sl";
        write(str+"\n");
        return 1;
    }
    if(arg == "yuanbao"){
        if(me->query("yuanbao")<150)
            return notify_fail("请确保你有足够的元宝。\n");       
            me->add("yuanbao",-150);
            start_ken(me);
    }
    
    if (arg == "yuanbao_sl")
    {
        int i;
        
        if (me->query("yuanbao") < 1400)
            return notify_fail("请确保你有足够的元宝。\n");
        
        me->add("yuanbao", -1400);
        for(i = 0; i < 10; i++)
        {
            start_ken(me);
        }
        return 1;
    }
    
    if(arg == "one")
    {
    	object ob;
    	if (!objectp(ob = present("one card",me)))
        {
            if (!ob->query("yuanbao"))
    		return notify_fail("你又没有单抽卡，喵。\n");
        }
        if (!ob->query("yuanbao"))
        return notify_fail("你又没有单抽卡，喵。\n");
    	ob->add_amount(-1);
    	start_ken(me);
    	return 1;
    }
    
    if (arg == "ten")
    { 
    object ob;
    int i=0;
       if (!objectp(ob = present("ten card",me)))
       return notify_fail("你又没有十连抽卡，喵。\n");    
       ob->add_amount(-1);
       while (i<10)
       {
       start_ken(me);
       i++;
       }
       return 1;
    }
    return 1;

}
int start_ken(object me)
{
//贵重物品 元宝几率
    string *ob_list = ({
        "/clone/gift/dan_chongmai3",
        "/clone/gift/dan_chongmai3",
        "/clone/gift/dan_chongmai3",
        "/u/cx/luck/butian",
        "/u/cx/luck/tiancs",
        "/u/cx/luck/tiancs",
        "/u/cx/luck/jiuzhuan",
        "/clone/vip/card_name",
        "/clone/vip/card_name",
    });
    
    //葡萄类的
    string *pt_list = ({
        "/u/cx/luck/putao",
        "/u/cx/luck/daputao",
        "/u/cx/luck/daputao",
        "/u/cx/luck/daputao",
        "/u/cx/luck/daputao",
        "/u/cx/luck/putao",
        "/u/cx/luck/lingzhi",
        "/clone/gift/hundunshi",
         "/clone/gift/dan_chongmai1",
        "/clone/gift/dan_chongmai2",
        "/u/cx/luck/putao",
        "/u/cx/luck/lingzhi",
         "/clone/gift/dan_chongmai1",
        "/clone/gift/dan_chongmai2",
        "/u/cx/luck/putao",
        "/u/cx/luck/lingzhi",
         "/clone/gift/dan_chongmai1",
        "/clone/gift/dan_chongmai2",
        "/u/cx/luck/putao",
        "/u/cx/luck/lingzhi",
         "/clone/gift/dan_chongmai1",
        "/clone/gift/dan_chongmai2",
        "/u/cx/luck/putao",
        "/u/cx/luck/lingzhi",
         "/clone/gift/dan_chongmai1",
        "/clone/gift/dan_chongmai2",
        
    });
    
    //技能类的
    string *skill_list = ({
      //  "jiuyang-shengong",
       // "shenzhaojing",
        "qishang-quan",
        "baihua-quan",
        "hanbing-mianzhang",
        "xuanming-zhang",
        "sougu",
         "zhuihun-jian",
        "yunlong-bian",
        "hanxing-bada",
        "bizhen-qingzhang",
         "huanyin-zhi",
        "ningxue-shenzhao",
        "sanfen-jianshu",
        "zijinbagua-dao",
    });

    //宝石类的
    string *gem_list = ({
        "/clone/gem/hujiagem",
        "/clone/gem/wanjian",
        "/clone/gem/lonelygem",
        "/clone/gem/xuedaogem",
        "/clone/gem/luoye",
        "/clone/gem/liuyang-rx",
        "/clone/gem/lonelyfxgem",
        "/clone/gem/lonelyymgem",
         "/clone/gem/xueshangem",
         "/clone/gem/manmiao-gem",
         "/clone/gem/hmgonggem",
         "/clone/gem/liumai-qi",
         "/clone/gem/liumai-six",
         "/clone/gem/xianglong-xiang",
         "/clone/gem/qitun-gem",
         "/clone/gem/shedao-chang1",
    });
    
     mapping skills;
    string str,*sk,skill;
    int random,i;
    object obj;
    
    random = random(100)+1;
        if(random<=1 || me->query("luckdraw/number") >= 100){
            obj = new(gem_list[random(sizeof(gem_list))]);
            me->delete("luckdraw/number");//抽到宝石以后清除保底
            
            if (random(30) == 1)
            {
            me->set("special_skill/lun", 1);
            write("恭喜你获得了本期彩蛋，天赋绝技：六道轮回.\n");
            CHANNEL_D->do_channel(this_object(),"rumor",me->query("name")+"获得了本期彩蛋，天赋绝技：六道轮回!\n");
            }
            
        }else if(random<=1){
            skill = skill_list[random(sizeof(skill_list))];
            //判断会的技能中有没有此技能
            skills = me->query_skills();
		    sk = keys(skills);
            for(i=0; i<sizeof(skills); i++) {
                if(skill == sk[i]){
                	log_file("luckdraw", ctime(time()) + "   " + me->name() + me->query("id") + "  抽到已拥有武功" + skill + "\n");
                    write("你抽到了一个你已经学会的技能，这次就不算啦！\n");
                    return 1;
                }
            }

            me->set_skill(skill,180);
       //     me->add("yuanbao",-150);
            log_file("luckdraw", ctime(time()) + "   " + me->name() + me->query("id") +  "  抽到" + skill + "\n");
            write("恭喜抽到【"+ skill +"】!\n");
            CHANNEL_D->do_channel(this_object(),"rumor",me->query("name")+"抽到了一个技能【"+ skill +"】!\n");
            return 1;
        }else if(random<=85){
            obj = new(pt_list[random(sizeof(pt_list))]);
        }else{
            obj = new(ob_list[random(sizeof(ob_list))]);
        }
        log_file("luckdraw", ctime(time()) + "   " + me->name() + me->query("id") + "  抽到" + obj->name() + "\n");
        obj->move(me);
        
        me->add("luckdraw/number",1);//计算保底
        write("恭喜抽到【"+ obj->query("name") +"】!\n");
  //      me->add("yuanbao",-150);
        CHANNEL_D->do_channel(this_object(),"rumor",me->query("name")+"抽到了一个物品【"+ obj->query("name") +"】!\n");
        return 1;
}