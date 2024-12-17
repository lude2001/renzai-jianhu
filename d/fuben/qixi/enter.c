//#include "include/enquire_fuben.h"
#include <localtime.h>

int enquire_fuben(object who, object fb_mem)
{
	int i, last_time;
	object *team;
	object room,npc;

	if (!(team = who->query_team()))
	{
		write("你还没有加入到队伍中。\n");
		return 0;
	}
	
	if ( team[0] != who) 
	{
		write("只有队伍首领才能开启副本。\n");
		return 0;
	}
	
	if (sizeof(team) != 2)
	{
		write("七夕之河只能两人组队进入。\n");
		return 0;
	}
	
	for (i=0;i<sizeof(team);i++)
	{
		if (!team[i]){
			write("你的队伍出现了问题，请解散并重新组建。\n");
			return 0;
		}
		
		if (!present(team[i],environment(who))){
			write("咦？怎么好象人不全啊？"+team[i]->query("name")+"怎么没来？\n");
			return 0;
		}
		
		if (!interactive(team[i])) 
		{
			write(team[i]->query("name")+"现在不在线，换成其他人吧。\n");
			return 0;
		}

		if (team[i]->query("qixi_time") / 86400 < time() / 86400)
		{
			team[i]->delete("qixi_count");
		}

		if (team[i]->query("qixi_count"))
		{
			write(team[i]->query("name") + "今天已经进入过七夕之河了！\n");
			return 0;
		}

	}
	
	room = new("/d/fuben/qixi/map/he");

	for (i=0;i<sizeof(team);i++)
	{
		team[i]->move(room);
		team[i]->set("qixi_time",time());
		team[i]->add("qixi_count",1);
		tell_object(team[i],"你成功进入了七夕之河。\n");
	}

	npc = new("/d/fuben/qixi/npc/guai");
	npc->move(room);

	return 1;
}
