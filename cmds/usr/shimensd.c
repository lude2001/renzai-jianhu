// spy.c
// by ReyGod  in  12/16/1996  in BUPT

#include <ansi.h>

inherit F_CLEAN_UP;
int remote_bonus(object me);

int main(object me, string arg)
{

    
    if (me->query("combat_exp") < 1500000)
    return notify_fail("经验小于150万，不能开启扫荡。\n");
    
    if (me->query("cxpay/gongxian") < 30)
    return notify_fail("贡献小于30无法扫荡。\n");
    
	if (!arg)
    {
		write(ZJOBLONG"你可以选择如下扫荡\n"ZJOBACTS2"元宝扫荡:shimensd yuanbao"ZJSEP"通宝扫荡:shimensd yuan_bao\n");
		return 1;
	}
	else if (arg == "yuanbao" || arg == "yuan_bao")
	{

		if (arg == "yuanbao")
		{
			if (me->query("yuanbao") < 50)
				return notify_fail("元宝数量不足。\n");

			me->add("yuanbao",-50);
		}
		else
		{
			if (me->query("yuan_bao") < 50)
			return notify_fail("通宝数量不足。\n");

			me->add("yuan_bao",-50);
		}

		if ((time() / 86400) > (me->query("shimensd/time") / 86400) && me->query("shimensd/number") >= 1000)
		{
			me->delete("shimensd/number");
		}

		if ((time() / 86400) >= (me->query("shimensd/time") / 86400) && me->query("shimensd/number") >= 1000)
		{
			write("你今天的师门扫荡次数已经用光了。\n");
			return 1;
		}
    
        
		me->set("shimensd/time",time());
		me->add("shimensd/number",50);
	}
	else
	{
	    return 1;
	}

	for (int i = 0;i<50;i++)
	{
		remote_bonus(me);
	}

	write("今天已经完成扫荡次数为:" + me->query("shimensd/number") + "次。\n");
	return 1;
}


// 远程奖励
int remote_bonus(object me)
{
	//mapping q;	      // WHO的任务
	string msg = "";	     // 掌门说的消息
	//object dob;	     // 打晕敌人的人
	int bonus;	      // 奖励(正整数，1是正常)
	//int t;		  // 用来计算时间的变量
	int exp;		// 获得的经验
	int pot;		// 获得的潜能
	int mar;		// 获得的实战体会
	int weiwang;	    // 获得的威望
	int score;	      // 获得的江湖阅历
	int lvl;		// 人物的等级
	//int quest_level;	// QUEST的等级
	int quest_count;	// 连续QUEST的数目
	//int timeover;	   // 标志：超时了？
	int added;	      // 做任务的时候额外出现的敌人或敌人逃走
	mixed special = 0;      // 是否有特殊奖励


	// bonus 为 1 表示正常奖励，为 2 表示扣除一半。
	bonus = 1;

	lvl = NPC_D->check_level(me);
	exp = 8 + random(5) + lvl;
	pot = 4 + random(3) + lvl;
	weiwang = 1 + random(3) + lvl / 2;
	score = 1 + random(3) + lvl / 2;
	quest_count = me->query("quest_count") + 1;

	// 根据任务完成的次数修正奖励
	if (quest_count >= 500)
	{
		// 连续完成了超过500次的任务
		exp += 80 + random(quest_count / 20 + 1);
		pot += 45 + random(quest_count / 25 + 1);
		mar = 45 + random(20);
		weiwang += 8 + random(20);
		score += 4 + random(15);
	} else
	if (quest_count >= 200)
	{
		// 连续完成了超过200次的任务
		exp += 70 + random(quest_count / 20 + 1);
		pot += 40 + random(quest_count / 25 + 1);
		mar = 20 + random(10);
		weiwang += 5 + random(15);
		score += 3 + random(10);
	} else
	if (quest_count >= 100)
	{
		// 连续完成了超过100次的任务
		exp += 50 + random(quest_count / 20 + 1);
		pot += 30 + random(quest_count / 25 + 1);
		weiwang += 3 + random(10);
		score += 2 + random(10);
	} else
	if (quest_count >= 10)
	{
		// 连续完成了超过10次的任务
		exp += 45 + random(quest_count / 20 + 1);
		pot += 25 + random(quest_count / 25 + 1);
		weiwang += 1 + random(5);
		score += 1 + random(5);
	}
	if (quest_count >= 1000)
	{
		msg += "想不到你连着上千次任务无一失手，看来我们" + me->query("family/family_name") + "后继有人矣。";
		special = "/clone/vip/dan_jiuzhuan1";
		quest_count = 0;
            me->add("quest_circle", 1);
	} else
	if ((quest_count % 50) == 0)
	{
		msg += "真是不赖，居然连着" + chinese_number(quest_count) + "次都没有失手。";
	}


	me->set("quest_count", quest_count);

	msg += "\n";
	tell_object(me, msg);
	me->delete("quest");
	if (! bonus) return 1;

	exp /= bonus;
	pot /= bonus;
	mar /= bonus;
	weiwang /= bonus;
	score /= bonus;

	tell_object(me,HIR"这是第" + quest_count + "轮师门"NOR"。\n");	// 0.01% to get a special object
	if ((quest_count>0 && (quest_count % 30) == 0)|| special)
	{
		QUEST_D->special_bonus(QUEST_D, me, special);
		tell_object(me,HIR"师门物品奖励触发！"NOR"。\n");
	}
	else
	if (random(10000) == 1||me->query("skill_bonus_set"))
	{
		QUEST_D->skill_bonus(QUEST_D, me);
		tell_object(me,HIR"师门技能奖励触发！"NOR"。\n");
    }
	QUEST_D->bonus(me, ([ "exp" : exp, "pot" : pot, "mar" : mar,
		      "weiwang" : weiwang, "score" : score ]), 1);
	return 1;
}