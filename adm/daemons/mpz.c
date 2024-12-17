
inherit F_DBASE;
#include <localtime.h>

#define NPC_ROOM 20

void check_time();
int start_mpz();
object *get_room_arr();
void remove_npc();
void *query_npc();

string zhangmen, enemy;
object *npc_arr = ({});

void create()
{
	seteuid(getuid());
	set("channel_id", "门派入侵系统");
	CHANNEL_D->do_channel( this_object(), "sys", "门派入侵系统已经启动。"NOR);
	set_heart_beat(0);
}

mapping family_dir = ([
	CLASS_D("shaolin/xuan-ci")  : "/d/shaolin/",
	CLASS_D("wudang/zhang")   : "/d/wudang",
	CLASS_D("gaibang/hong")  : "/d/gaibang",
	CLASS_D("quanzhen/wang") : "/d/quanzhen/",
	CLASS_D("huashan/yue-buqun")  : "/d/huashan/",
	CLASS_D("duan/duanzm")     : "/d/dali/",
	CLASS_D("murong/murongfu")   : "/d/morong/",
	CLASS_D("xueshan/jiumozhi")  : "/d/xueshan/",
	CLASS_D("lingjiu/xuzhu")  : "/d/lingjiu/",
	CLASS_D("emei/miejue")     : "/d/emei/",
	CLASS_D("taohua/huang")   : "/d/taohua/",
	CLASS_D("shenlong/hong") : "/d/shenlong/",
	CLASS_D("gumu/longnv")     : "/d/gumu/",
	CLASS_D("xingxiu/ding")  : "/d/xingxiu/",
	CLASS_D("xiaoyao/xiaoyaozi")  : "/d/xiaoyao/",
	CLASS_D("xuedao/laozu")   : "/d/xuedao/",
	CLASS_D("ouyang/ouyangfeng")   : "/d/baituo/",
	CLASS_D("hu/hufei")       : "/d/guanwai/",
]);


void heart_beat()
{
	check_time();
}

int ok = 0;
void check_time()
{
	int GMT = time() + localtime(0)[8];
	string d, times;
	int h, s;
	
	times = ctime(GMT);
	//Sun(星期日) Mon(星期一)  Tue(星期二)  Wed(星期三)  Thu(星期四)  Fri(星期五)  Sat(星期六)
	d = times[0..2];//星期
	h = to_int(times[10..12]);//时
	s = to_int(times[14..15]);//分
	
	if(h > 7 && h < 23)
	{
		if((s == 30) && !ok)
		{
			ok = 1;
			if (sizeof(npc_arr))	npc_arr = ({});
			start_mpz();
			remove_call_out("remove_npc");
			call_out("remove_npc", 1800);
			log_file("menpairuqin", times + "门派入侵选定" + load_object(zhangmen)->query("family/family_name") + "敌对为：" + enemy + "。1234\n");
			CHANNEL_D->do_channel(load_object(zhangmen), "chat", enemy + "的弟子真是太嚣张了，已经打上山门了！\n");
			log_file("menpairuqin", times + "门派入侵选定" + load_object(zhangmen)->query("family/family_name") + "敌对为：" + enemy + "。\n");
		}
	}
	
	if (s == 40)	ok = 0;
}

int start_mpz()
{
	int npc_count = 0;
	string *room_file, *enemy_arr;
	object room, npc;
	mapping exit;

	zhangmen = keys(family_dir)[random(sizeof(family_dir))];
	room_file = list_dirs(family_dir[zhangmen] + "*.c");
	enemy_arr = keys(family_dir);
	enemy_arr -= ({zhangmen});
	enemy = enemy_arr[random(sizeof(enemy_arr))]->query("family/family_name");
	while (npc_count < NPC_ROOM)
	{
		room = load_object(family_dir[zhangmen] + room_file[random(sizeof(room_file))]);
		if (!objectp(room))	continue;
		
		exit = room->query("exits");
		if (!room->query("short") || !mapp(exit) || !sizeof(exit) || room->query("no_fight"))
			continue;
		else
		{
			npc = new(__DIR__"npc/npc");
			npc->move(room);
			npc->set_name("red" + enemy + "弟子", ({"mp_npc"}));
			npc->set("family/family_name", enemy);
			npc_arr += ({npc});
			++npc_count;
		}
	}
	
	return 1;
}

void remove_npc()
{
	object temp;
	
	foreach(temp in npc_arr)
	{
		if (!find_object(file_name(temp)))	continue;
		temp->force_me("say 溜了溜了。\n");
		destruct(temp);
	}
	npc_arr = ({});
}

object *query_npc()
{
	return npc_arr;
}