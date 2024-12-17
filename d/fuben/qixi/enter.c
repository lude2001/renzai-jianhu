//#include "include/enquire_fuben.h"
#include <localtime.h>

int enquire_fuben(object who, object fb_mem)
{
	int i, last_time;
	object *team;
	object room,npc;

	if (!(team = who->query_team()))
	{
		write("�㻹û�м��뵽�����С�\n");
		return 0;
	}
	
	if ( team[0] != who) 
	{
		write("ֻ�ж���������ܿ���������\n");
		return 0;
	}
	
	if (sizeof(team) != 2)
	{
		write("��Ϧ֮��ֻ��������ӽ��롣\n");
		return 0;
	}
	
	for (i=0;i<sizeof(team);i++)
	{
		if (!team[i]){
			write("��Ķ�����������⣬���ɢ�������齨��\n");
			return 0;
		}
		
		if (!present(team[i],environment(who))){
			write("�ף���ô�����˲�ȫ����"+team[i]->query("name")+"��ôû����\n");
			return 0;
		}
		
		if (!interactive(team[i])) 
		{
			write(team[i]->query("name")+"���ڲ����ߣ����������˰ɡ�\n");
			return 0;
		}

		if (team[i]->query("qixi_time") / 86400 < time() / 86400)
		{
			team[i]->delete("qixi_count");
		}

		if (team[i]->query("qixi_count"))
		{
			write(team[i]->query("name") + "�����Ѿ��������Ϧ֮���ˣ�\n");
			return 0;
		}

	}
	
	room = new("/d/fuben/qixi/map/he");

	for (i=0;i<sizeof(team);i++)
	{
		team[i]->move(room);
		team[i]->set("qixi_time",time());
		team[i]->add("qixi_count",1);
		tell_object(team[i],"��ɹ���������Ϧ֮�ӡ�\n");
	}

	npc = new("/d/fuben/qixi/npc/guai");
	npc->move(room);

	return 1;
}
