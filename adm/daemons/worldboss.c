/*duotreasure.c
by 潇湘夜雨(baiyi666) baiyi666
世界怪物系统
思路就是世界随机抽取！
*/
#include <ansi.h>

inherit F_DBASE;
#include <localtime.h>
//定义了世界大地图列表
mapping room_place = ([
	"白驼山"		: "/d/baituo/",
	"北京"			: "/d/beijing/",
	"长安" 			: "/d/changan/",
	"扬州"			: "/d/city/",
	"成都"			: "/d/city3/",
	"大理"			: "/d/dali/",
	"峨嵋山" 		: "/d/emei/",
	"佛山"			: "/d/foshan/",
	"丐帮" 			: "/d/gaibang/",
	"福州"			: "/d/fuzhou/",
	"关外"			: "/d/guanwai/",
	"归云山庄"	: "/d/guiyun/",
	"古墓" 			: "/d/gumu/",
	"杭州"			: "/d/hangzhou/",
	"黑木涯"		: "/d/heimuya/",
	"衡山" 			: "/d/hengshan/",
	"恒山"			: "/d/henshan/",
	"黄河"			: "/d/huanghe/",
	"华山派"		: "/d/huashan/",
	"灵鹫宫"			: "/d/lingjiu/",
	"灵州"			: "/d/lingzhou/",
	"梅庄"			: "/d/meizhuang/",
	"明教" 			: "/d/mingjiao/",
	"青城山"		: "/d/qingcheng/",
	"全真派" 		: "/d/quanzhen/",
	"泉州" 			: "/d/quanzhou/",
	"少林寺" 		: "/d/shaolin/",
	"神龙岛"		: "/d/shenlong/",
	"嵩山"			: "/d/songshan/",
	"苏州"			: "/d/suzhou/",
	"泰山"			: "/d/taishan/",
	"桃花岛"		: "/d/taohua/",
	"天龙寺"		: "/d/tianlongsi/",
	"万劫谷"		: "/d/wanjiegu/",
	"武当山"		: "/d/wudang/",
	"侠客岛"		: "/d/xiakedao/",
	"襄阳"			: "/d/xiangyang/",
	"逍遥派"		: "/d/xiaoyao/",
	"星宿海" 		: "/d/xingxiu/",
	"血刀门" 		: "/d/xuedao/",
	"雪山" 			: "/d/xueshan/",
	"燕子坞" 		: "/d/yanziwu/",
]);
//随机掉落的物品列表
string *duobao=({
"/clone/vip/dan_qingxin",
"/clone/vip/dan_zhengqi",
"/clone/vip/jinsha",
"/clone/vip/lingzhi",
});
int ok = 0;
int ok1 = 0;
string path_where=0;
int check_hp(object me,int value);
int choose_player(object me);
int top_list(object ob1,object ob2);

string *allroom_file,room_file,*allplace_name,place_name;//全局变量，以便调用
void create()
{
	seteuid(getuid());
	set("channel_id", "世界怪物系统");
	CHANNEL_D->do_channel( this_object(), "sys", "世界怪物系统已经启动。"NOR);
	set_heart_beat(20);//预启动
}

int clean_up()
{
	return 1;
}
void  load_room()
{
//读取所有的大地图名称
allplace_name=keys(room_place);
//随机读取一个大地图
place_name=allplace_name[random(sizeof(allplace_name))];
//读取一个大地图内全部的房间
allroom_file=stat(room_place[place_name]);
//只保留大地图目录内的.c文件（房间）
foreach (room_file in allroom_file)
{
if (strsrch(room_file,".c")==-1)
allroom_file-=({room_file});
}
//随机获取一个房间地点
room_file=room_place[place_name]+allroom_file[random(sizeof(allroom_file))];
}

void check_time()
{
	int GMT = time();
	string d, times;
	int h, s,value;
	object room, ob;
	times = ctime(GMT);
	//Sun(星期日) Mon(星期一)  Tue(星期二)  Wed(星期三)  Thu(星期四)  Fri(星期五)  Sat(星期六)
	d = times[0..2];//星期
	h = to_int(times[10..12]);//时
	s = to_int(times[14..15]);//分
//	用来处理世界怪物，晚上九点开始，到凌晨三点
	if ((h>=21||h<=3)&&(s==30||s==0))
	{
	object npc,obj,*npcs;
	//因为要产生新的世界怪物，原来的世界怪物应该清除 以节省内存
		npcs = children("/clone/worldboss/xinmo");
		foreach (npc in npcs)
		destruct(npc);
		//重新生成一个世界怪物
	npc=new("/clone/worldboss/xinmo");
	//随机读取一个奖励物品，放入怪物的背包
	obj=new(duobao[random(sizeof(duobao))]);

//value是什么呢?用来衡量一个物品的价值，世界怪物出现时只通报这个价值。
	if (obj->query("yuanbao"))
	value=obj->query("yuanbao")*10000;
	else
	if (obj->query("value"))
	value=obj->query("value")/2;
	else
	value=500000;	//最地低价值50两黄金，没毛病吧
	obj->move(npc);	
check_hp(npc,value);	
/*	
//用来检查世界怪物系统出现错误，测试
if (!objectp(room_file))
	{
	tell_object(find_player("baiyi666"),"房间错误\n");
	}*/
	
	while (1)//检查，为了避免掉落到不可战斗的地图。
	{
	load_room();
		if (!room_file->query("no_fight"))	
		break;
	}
	npc->move(room_file);
	find_player("baiyi666")->move(room_file);
	tell_object(find_player("baiyi666"),HBRED+place_name+room_file->query("short")+"房间\n"NOR);
	choose_player(npc);
	npc->force_me("chat 理智？哼，愚蠢的事物，本魔在"+place_name+"的"+room_file->query("short")+"挑战天下高手，让本魔来征服江湖！");
	}
	else
	return;
	//========================
	
}
//心跳检查
protected void heart_beat()
{	
	check_time();
}
//处理生成的世界怪物的状态量。
int check_hp(object me,int value)
{
int qi,neili;
 qi = me->query("max_qi")*20;
 neili = me->query("max_neili")*20;

me->set("max_qi",qi);
me->set("eff_qi",qi);
me->set("qi",qi);
me->set("max_neili",neili);
me->set("neili",neili);

return 1;
}
//随机选择前三名的玩家进行处理
int choose_player(object me)
{
   object *ob,*list,rand_player;
   
ob = filter_array(children(USER_OB),(: userp($1) && !wizardp($1) :));
        list = sort_array(ob, (: top_list :));
        
        if (sizeof(list)>3)//如果连三个玩家都没有，怎么办?哈哈       
        list = ({list[0],list[1],list[2]});//读取前三位
        
        rand_player = list[random(sizeof(list))];//随机读取一位玩家
        "/cmds/wiz/copyskill"->copy_skill(me,rand_player);//复制对应玩家的技能
        me->set_name(rand_player->name()+"·心魔", ({ getuid(rand_player)+" mo", "mo" }));
        me->set("name",rand_player->name()+"·心魔");//第二次比较保险
        return 1;
}

//直接用已经写好的排列规则
int top_list(object ob1,object ob2)
{
    return "/cmds/usr/topten"->top_list(ob1,ob2);    
}