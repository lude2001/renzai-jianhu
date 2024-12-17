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
		return notify_fail("�������ǩ�����ˣ���Ŀǰ������ǩ����"+HIY+times+NOR+"���졣\n");

	if(times>6)
	{
		tell_object(me,"�������һ��ǩ����\n");
		//me->set("day_sign_times",6);
		me->delete("day_sign_times");
		times = 0;
	}/*
	if(time()/86400 - last/86400 > 1)
	{
		tell_object(me,"������û��ǩ����¼��������¼�ӽ��쿪ʼ��\n");
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
	tell_object(me,"������ǩ��"+HIY+times+NOR+"�Σ����"+HIY+pot+NOR+"�㾭���Ǳ��,ÿ������ɨ�����ã�Ԫ�����ã�����һ�Ρ�\n");
	list = keys(gifts);
	for(i=0;i<sizeof(list);i++)
	{
		file = list[i];
		if((gifts[file]+times*10) > random(100))
		{

			ob = new(file);
			tell_object(me,"������"+ob->short()+"��\n");
			ob->move(me);
		}
	}
	return 1;
}

//����ǩ������---�жϽ����Ƿ��Ƕ���ڻ�ڼ䣬����ǽ������ڽ����ӿ�
//({��, ��, ʱ, ��, ��, ��, ����, ��, ʱ��, ʱ��, ����ʱ})
int duanwu_jie_daysign(object me)
{
	int month, day, nowTime;

	nowTime = time();
	month = localtime(nowTime)[4] + 1;
	day = localtime(nowTime)[3];

	tell_object(me,sprintf("������%d��%d�Ž����ڼ�ǩ����ø��ཱ��Ŷ!\n,",month,day));

	if (month == 6 && day <= 5)
	{
		duanwu_jie_reward(me,day);
	}

	return 1;
}

//����ڽ�������
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

		tell_object(me,sprintf("�����˶����ʹ������%s(%d)\n",ob->query("name"),number));
		ob->move(me);
		

	}

}

int help(object me)
{
	write(@HELP
ǩ��
HELP
	);
	return 1;
}
