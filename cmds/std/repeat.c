// cut.c

#include <ansi.h>

inherit F_CLEAN_UP;
mapping repeat_quest_level = (["liu mang":1,
							"xiao hunhun":1,
							  "guan bing":1,
							   "yang guo":3,
								"long nv":2,
								  "tuoba":1,
							"ma chaoxing":1,
								 "du she":1,
							  "huanan hu":1,
								 "dao ke":1,
]);

mapping repeat_quest_name = (["liu mang":"暴打流氓",
						   "xiao hunhun":"惩戒小混混",
							 "guan bing":"教育官兵",
							  "yang guo":"刺杀杨过",
							   "long nv":"刺杀小龙女",
								 "tuoba":"刺杀拓跋",
						   "ma chaoxing":"刺杀马超兴",
								"du she":"清理毒蛇",
							 "huanan hu":"清理华南虎",
								"dao ke":"屠净刀客",
]);

mapping repeat_quest_number = (["liu mang":50,
							 "xiao hunhun":50,
							   "guan bing":30,
								"yang guo":1,
								 "long nv":1,
								   "tuoba":1,
							 "ma chaoxing":1,
								  "du she":50,
							   "huanan hu":50,
								  "dao ke":30,
]);

mapping english_number = (["一":"one",
						   "二":"two",
						   "三":"three",
						   "四":"four",
]);
int distribution_quest(object me);
int finish_quest(object me);

//封装zj弹窗
string popup(string str)
{
	string msg;
	msg = ZJOBLONG + str;
	msg = replace_string(msg, "\n", ZJBR);
	return msg + "\n";
}
//带按键的zj弹窗
string popup_key(string str)
{
	str = ZJOBACTS2 + ZJMENUF(2, 2, 9, 30) + str;
	return str + "\n";
}
//可输入字符串的直接弹窗
string popup_input(string str, string order)
{
	return INPUTTXT(str, order + "$txt#") + "\n";
}

int main(object me, string arg)
{
	object ob;
	string *repeat_information;
	string str, msg;

	repeat_information = keys(repeat_quest_name);

	if (!arg)
	{

		if (me->query("repeat") && time() >= (me->query("repeat/time") + 3600))
		{

			me->delete ("repeat");

			return notify_fail(popup("任务时间到，任务自动作废，请重新抽取任务。"));
		}
		//每隔四小时自动分配任务
		if (time() >= me->query("quest_give/time") + 14400 || !me->query("quest_give"))
		{
			write(popup("时间已到，自动分配新任务。"));
			distribution_quest(me);
		}

		if (me->query("quest_give") && !me->query("quest_give/number"))
			return notify_fail(popup(sprintf("当前任务已全部完成，你可以在%s后再刷新领取新的任务！", CHINESE_D->chinese_time(me->query("quest_give/time") + 14400 - time()))));

		repeat_information = me->query("quest_give/number");

		str = "你目前可以随机领取到如下循环任务\n";
		str += "这些任务将在" + CHINESE_D->chinese_time(me->query("quest_give/time") + 14400 - time()) + "后刷新\n";
		str += HIC "≡" HIY "一一一一一一一一一一一一一一一一一一一一" HIC "≡" NOR "\n";
		// 名称(已完成数/总数)[领取状况]
		foreach (msg in repeat_information)
			//	    if (!me->query("quest_give/finish/"+msg))
			str += sprintf("【%d级】%s(%d/%d)[%s]\n", repeat_quest_level[msg], repeat_quest_name[msg], me->query("repeat/npc_" + msg), repeat_quest_number[msg], me->query("repeat/quest_" + msg) ? HIY "已领取" NOR : HIR "未领取" NOR);

		if (me->query("repeat"))
			str += sprintf("你已领取%s任务，目前距离任务结束还有%s，请你抓紧时间。\n", repeat_quest_name[me->query("repeat/name")], CHINESE_D->chinese_time(me->query("repeat/time") + 3600 - time()));
		str += "你可以执行如下操作：\n";
		str += HIC "≡" HIY "一一一一一一一一一一一一一一一一一一一一" HIC "≡" NOR;
		str = popup(str);
		msg = "";
		if (me->query("repeat"))
			msg += "使用加速卡:repeat accelerate" ZJSEP;
		msg += "领取随机任务:repeat receive" ZJSEP;
		msg += "提交完成任务:repeat finish";
		str += popup_key(msg);
		write(str);
	}
	repeat_information = me->query("quest_give/number");

	//第二次检测防止指令领取
	if (me->query("quest_give") && !me->query("quest_give/number"))
		return notify_fail(popup(sprintf("当前任务已全部完成，你可以在%s后再刷新领取新的任务！", CHINESE_D->chinese_time(me->query("quest_give/time") + 14400 - time()))));

	if (arg == "receive")
	{
		string receive;
		if (me->query("repeat"))
			return notify_fail(popup("你已经领取过任务了，先把它完成了吧"));

		receive = repeat_information[random(sizeof(repeat_information))];

		me->set("repeat/quest_" + receive, 1);
		me->set("repeat/name", receive);
		me->set("repeat/time", time());
		write(popup(sprintf("恭喜你随机抽取到了%s的任务，任务要求在一小时内完成，否则自动放弃，请抓紧时间吧！", repeat_quest_name[receive])));
	}

	if (arg == "finish")
	{
		string receive = me->query("repeat/name");
		if (!me->query("repeat"))
			return notify_fail(popup("你还是先领取一个任务吧，不然想提交空气啊？"));

		if (me->query("repeat/npc_" + receive) < repeat_quest_number[receive])
			return notify_fail(popup("你还没有完成这个任务呢，怎么？想白嫖啊？"));

		return finish_quest(me);
	}

	if (arg == "accelerate")
	{
		object obj;
		string obj_name;
		if (!me->query("repeat"))
			return notify_fail(popup("你还是先领取一个任务吧，不然想加速空气啊？"));
		obj_name = english_number[chinese_number(repeat_quest_level[me->query("repeat/name")])] + " card";
		//	write(obj_name+"\n");
		if (!objectp(obj = present(obj_name, me)))
			return notify_fail(popup("你还没有这种加速卡，怎么？想白嫖啊？"));
		obj->add_amount(-1);
		return finish_quest(me);
	}
	return 1;
}

int distribution_quest(object me)
{
	int i = 0;
	string *quest_give = ({});
	while (i < 4)
	{
		string quest_id, *quest_name = keys(repeat_quest_name);
		quest_id = quest_name[random(sizeof(quest_name))];
		if (sizeof(quest_give) && member_array(quest_id, quest_give) != -1)
			continue;
		quest_give += ({quest_id});
		i++;
	}
	me->delete ("quest_give");
	//先清除原有信息。
	me->set("quest_give/number", quest_give);
	me->set("quest_give/time", time());
	return 1;
}

int finish_quest(object me)
{

	string receive = me->query("repeat/name");
	int quest_exp, quest_pot;
	string *quest_give = ({});

	quest_exp = 2000 * pow(repeat_quest_level[receive], 2);
	quest_pot = 1500 * pow(repeat_quest_level[receive], 2);

	me->add("combat_exp", quest_exp);
	me->add("potential", quest_pot);
	me->delete ("repeat");
	//去除原先定义的任务。

	//检测任务数量信息
	quest_give = me->query("quest_give/number");
	quest_give -= ({receive});
	if (sizeof(quest_give))
		me->set("quest_give/number", quest_give);
	else
		me->delete ("quest_give/number");

	tell_object(me, popup(sprintf("恭喜你完成了%s的任务，获得如下奖励\n经验：%d\n，潜能：%d\n,请继续加油哦！", repeat_quest_name[receive], quest_exp, quest_pot)));
	return 1;
}
// int help(object me)
// {
// 	write( @HELP
// 你可以通过该指令领取一项随机任务。

// HELP );
// 	return 1;
// }
