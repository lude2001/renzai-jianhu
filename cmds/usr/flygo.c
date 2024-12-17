// miss 追寻物品

#include <ansi.h>

inherit F_CLEAN_UP;
string *anjian=({
"签到:daysign",
"抽奖:luckdraw",
// "领取储物袋:flygo daizi",
// "打造装备:walk 莫邪",
// "回师门:walk 师傅",
// "自建房屋:flygo room",
// "师门兑换:smdh",
// "官府任务:walk 程药发",
// "主线任务:maintask",
"在线玩家:who",
// "魔窟:flygo moku",
// "幻境:flygo huanjing",
// "草人试炼:flygo caoren",
// "元宝贡献奖励:fanli",
// "贡献自选奖励:new_fanli",
// "华山论剑:flygo lunjian",
// "师门扫荡:shimensd",
// "卧龙扫荡:wolongsd",
// "冲脉丹合成:cmhc",
//"七夕之河:flygo qixi",
// "时间长河:flygo god_mj",
// "高阶门派资格审批:mengpai_tuijian",
});
mapping where=([
"qiandao":"/d/city/wumiao",
"daizi":"/d/wizard/guest_room",
"room":"/data/hell/4/guangchang",
"lunjian" : "/d/lunjian/enter",
"turen" : "/d/pk/entry",
"qianchi" : "/d/fuben/qianchipu/qianchipu",
]);
int main(object me, string str)
{

	if(environment(me)->query("no_magic", 1))
		return notify_fail("这里无法使用这个功能。\n");
	
 if(!str)
 {
string bynb,msg;
msg=ZJOBLONG"萌新功能键，请选择\n"ZJOBACTS2+ZJMENUF(4,4,8,30);
  foreach (bynb in anjian)
 msg+= bynb+ZJSEP;

 if (environment(me)->query("outdoors") == "hell" || environment(me)->query("owner_build")==getuid(me))
 {
	msg +="建立家园:crroom"ZJSEP"扩建家园:crroom"ZJSEP"修改家园:edroom"ZJSEP"增加功能:edroom"ZJSEP"拆除场景:delroom"ZJSEP"家园开关:closeroom"ZJSEP;
 }

 msg+="寻路:walk\n";
 tell_object(me,msg);
 return 1;
 }

	if (me->is_ghost())
		return notify_fail("你还是等还了阳再说吧。\n");
	if (me->is_busy())
		return notify_fail("你现在正忙。\n");
	if (me->is_fighting())
		return notify_fail("你正在战斗中。\n");

    {	//副本
    	object room;
    	
        if (str == "moku")
        {
        	if(!objectp(room = new("/d/fuben_moku/moku")))
        	{
        		write("副本开启失败。\n");
        		return 1;
        	}
        	if(!room->start_fuben_moku(this_player()))
        		destruct(room);
        	return 1;
        }
        if (str == "caoren")
        {
        	if(!objectp(room = new("/d/fuben_caoren/shilianchang")))
        	{
        		write("副本开启失败。\n");
        		return 1;
        	}
        	if(!room->start_fuben_caoren(this_player()))
        		destruct(room);
        	return 1;
        }
        
        if (str == "huanjing")
        {
            "/d/fuben_huanjing/huanjing"->start_fuben(me);
            return 1;
        }
        
//         if (str == "qixi")
// 		{
// 			"/d/fuben/qixi/enter"->enquire_fuben(me);

// 			return 1;
// 		}
		
		if (str == "god_mj")
		{
            if (me->query("yuanbao") < 50)
            {
                write("你的元宝数目不足50。\n");
                return 1;
            }
            
            if (me->query("god_mj/time") / 86400 >= time() / 86400)
            {
                write("你今天已经挑战过时间长河了。\n");
                return 1;
            }
            
//             if (me->query("id") != "wwweee2")
// 			{
// 				write("测试中.\n");
// 				return 1;
// 			}
			
			if (!me->query("guizhen"))
			{
			   write("你尚未归真，没有领悟武学的真意，擅自进入时间之河容易丢失性命。\n");
			   return 1;
			}
			
			me->add("yuanbao",-50);
            me->set("god_mj/time",time());
            
            //加一个时间戳防止地图重复
			me->move(new("/xuni/god_mj/map/room/" + time() + ",1,1"));

			return 1;
		}
    }

 if (stringp(where[str]))
 me->move(where[str]);
return 1;	
}

int help(object me)
{
write(@HELP
指令格式 :
baiyi牛逼！
HELP
    );
    return 1;
}
