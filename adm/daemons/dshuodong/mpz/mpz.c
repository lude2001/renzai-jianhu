inherit F_DBASE;
#include <localtime.h>

#define NPC_ROOM 20

int start();
object *get_room_arr();
void remove_npc();
void *query_npc();

string zhangmen, enemy;
object *npc_arr = ({});

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

int start()
{
	int npc_count = 0;
	string *room_file, *enemy_arr;
	object room, npc;
	mapping exit;

	if (sizeof(npc_arr))	npc_arr = ({});
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
			npc = new(__DIR__"npc");
			npc->move(room);
			npc->set_name("red" + enemy + "����", ({"mp_npc"}));
			npc->set("family/family_name", enemy);
			npc_arr += ({npc});
			++npc_count;
		}
	}
	
    log_file("menpairuqin", ctime(time()) + "��������ѡ��" + load_object(zhangmen)->query("family/family_name") + "�ж�Ϊ��" + enemy + "��1234\n");
	CHANNEL_D->do_channel(load_object(zhangmen), "chat", enemy + "�ĵ�������̫�����ˣ��Ѿ�����ɽ���ˣ�\n");
	log_file("menpairuqin", ctime(time()) + "��������ѡ��" + load_object(zhangmen)->query("family/family_name") + "�ж�Ϊ��" + enemy + "��\n");
	
	return 1;
}

void remove_npc()
{
	object temp;
	
	remove_call_out("remove_npc");
	foreach(temp in npc_arr)
	{
		if (!find_object(file_name(temp)))	continue;
		temp->force_me("say �������ˡ�\n");
		destruct(temp);
	}
	npc_arr = ({});
}

object *query_npc()
{
	return npc_arr;
}