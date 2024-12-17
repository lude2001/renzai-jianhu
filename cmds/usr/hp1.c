
#include <ansi.h>
 
inherit F_CLEAN_UP;

string status_color(int current, int max);
 
int main(object me, string arg)
{
	object ob;
	mapping my;
	string sp;

	seteuid(getuid(me));
	ob = me;
 

	// if (me->query("id") == "wwweee2")
	// {
	// 	write("线程阻塞排查。\n");
	// }
	
	if (!userp(me))
	return 1;
	
	my = ob->query_entire_dbase();

	if (my["max_jing"] < 1 || my["max_qi"] < 1)
		return notify_fail("无法察看" + ob->name(1) + "的状态。\n");

	if (me->query("env/sign1"))
	{
		me->delete("env/sign1");
		tell_object(me,"系统自带的机器人系统废弃，请使用客户端脚本。\n");
	}
	sp  = ZJHPTXT+ZJMENUF(3,3,25,40)+ZJHPTXT+sprintf("%s:100/100:%s",my["name"],"#000000");
	sp += "║" + sprintf("气血.%d:%d/%d/%d:%s:%s",my["qi"],my["qi"],my["eff_qi"],my["max_qi"]+ob->query_gain_qi(),"#99FF0000","exert recover");
	sp += "║" + sprintf("内力.%d:%d/%d:%s",my["neili"],my["neili"],my["max_neili"],"#990066FF");
	sp += "║" + sprintf("精神.%d:%d/%d/%d:%s:%s",my["jing"],my["jing"],my["eff_jing"],my["max_jing"],"#996600CC","exert regenerate");
	sp += "║" + sprintf("Exp：%d:%d/%d:%s",my["combat_exp"],1,1,"#AA673AB7");
	sp += "║" + sprintf("潜：%d:%d/%d/%d:%s",my["potential"]-my["learned_points"],my["potential"],my["potential"]-my["learned_points"],my["potential"],"#AA006400");

	sp += "\n";
	tell_object(me, sp);		
	
	if (!me->query_temp("fight_jx")&&me->is_fighting())
	{
	tell_object(me,"fightStart\n");
	me->set_temp("fight_jx",1);
	}
	else
	if (me->query_temp("fight_jx")&&!me->is_fighting())
	{
	me->delete_temp("fight_jx");
		tell_object(me,"fightStop\n");	
	}
	
	return 1;
}

int help(object me)
{
	write(@HELP
指令格式 : hp
	  hp <对象名称>		  (巫师专用)
 
这个指令可以显示你(你)或指定对象(含怪物)的精, 气, 神数值。
 
see also : score
HELP );
    return 1;
}


