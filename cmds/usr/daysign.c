#include <ansi.h>
inherit F_CLEAN_UP;
int duanwu_jie_reward(object me,int day);
int duanwu_jie_daysign(object me);
int main(object me, string arg)
{
	string *list,file;
	int i,last,times,pot;
	mapping gifts;
	object ob;
	object shilian_card;
	
	gifts = ([
		"/clone/shizhe/book_tianfu":10,
		"/clone/shizhe/putao":10,
	]);
	
	last = me->query("last_day_sign");
	times = me->query("day_sign_times");
	if(time()/86400 == last/86400)
		return notify_fail("你今天已签过到了，你目前已连续签到【"+HIY+times+NOR+"】天。\n");

	if(times>6)
	{
		tell_object(me,"你完成了一轮签到。\n");
		//me->set("day_sign_times",6);
		me->delete("day_sign_times");
		times = 0;
	}/*
	if(time()/86400 - last/86400 > 1)
	{
		tell_object(me,"你昨天没有签到记录，连续记录从今天开始。\n");
		me->delete("day_sign_times");
		times = 0;
	}*/

	me->set("last_day_sign",time());
	me->add("day_sign_times", 1);
	times += 1;
	pot = random(1000) + 1000 + times*500;
	me->add("potential",pot);
	me->add("combat_exp",pot);
	duanwu_jie_daysign(me);
	me->delete("bangpai/finish");
	
	me->set("wolongsd/qd_number",1);
	tell_object(me,"你连续签到"+HIY+times+NOR+"次，获得"+HIY+pot+NOR+"点经验和潜能,每日卧龙扫荡费用（元宝费用）抵消一次。\n");
	list = keys(gifts);
	for(i=0;i<sizeof(list);i++)
	{
		file = list[i];
		if((gifts[file]+times*10) > random(100))
		{

			ob = new(file);
			tell_object(me,"你获得了"+ob->short()+"。\n");
			ob->move(me);
		}
	}
	return 1;
}

//端午签到方法---判断今天是否是端午节活动期间，如果是进入端午节奖励接口
//({秒, 分, 时, 日, 月, 年, 星期, 天, 时差, 时区, 夏令时})
int duanwu_jie_daysign(object me)
{
	int month, day, nowTime;

	nowTime = time();
	month = localtime(nowTime)[4] + 1;
	day = localtime(nowTime)[3];

	tell_object(me,sprintf("今天是%d月%d号节日期间签到获得更多奖励哦!\n,",month,day));

	if (month == 6 && day <= 5)
	{
		duanwu_jie_reward(me,day);
	}

	return 1;
}

//端午节奖励方法
int duanwu_jie_reward(object me,int day)
{
	mapping list;
	string path,number;

	mapping rewardList = ([
		1:([ "/clone/vip/dan_chongmai1":20,"/clone/baiyi/onecard":2,"/clone/vip/putao1":2 ]),
		2:([ "/clone/vip/dan_chongmai2":20,"/clone/baiyi/onecard":4,"/clone/vip/putao1":2 ]),
		3:([ "/clone/vip/dan_chongmai3":20,"/clone/baiyi/onecard":6,"/clone/vip/putao1":2 ]),
		4:([ "/clone/vip/dan_chongmai4":20,"/clone/baiyi/onecard":8,"/clone/vip/putao1":2 ]),
		5:([ "/clone/vip/dan_chongmai1":20,"/clone/vip/dan_chongmai2":20,"/clone/vip/dan_chongmai3":20,"/clone/vip/dan_chongmai4":20,"/clone/baiyi/tencard":1,"/clone/vip/putao1":2 ]),
	]);

	list = rewardList[day];
	
	foreach (path in keys(list))
	{
		object ob;

		ob = new_bind(path); 
		number = list[path];
		ob->set_amount(number);

		tell_object(me,sprintf("你获得了端午大使奖励的%s(%d)\n",ob->query("name"),number));
		ob->move(me);
		

	}

}

int help(object me)
{
	write(@HELP
签到
HELP
	);
	return 1;
}
