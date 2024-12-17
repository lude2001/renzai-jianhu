// time.c

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string str;
	if(!arg)
	{
		str = ZJOBLONG"你可以在角色信息版块处理以下问题：\n";
		str += ZJOBACTS2+ZJMENUF(3,3,10,30);
		str += "角色等级:uplv -l"ZJSEP"技能等级:uplv -s"ZJSEP"角色天赋:uplv -t"ZJSEP"放弃经验:abandon exp"ZJSEP"奇经十二脉:beat";
		str += ZJSEP"结义兄弟:brothers"ZJSEP"放弃经验:abandon exp"ZJSEP"召唤装备:summon all"ZJSEP"江湖称号:title"ZJSEP"屠人大赛:pkd"
		ZJSEP"会员时间:time"ZJSEP"修改绰号:nick"ZJSEP"战力排行:topten"ZJSEP"帮会系统:banghui"
		ZJSEP"综合排行:tops"ZJSEP"逃跑系数:wimpy"ZJSEP"退出游戏:quit";
		if (environment(me)->query("owner_build")==getuid(me))
			str += ZJSEP"修改密码:changepasswd"ZJSEP"奇经八脉:beat"ZJSEP"建立家园:crroom"ZJSEP"扩建家园:crroom"ZJSEP"修改家园:edroom"ZJSEP"增加功能:edroom"ZJSEP"拆除场景:delroom"ZJSEP"家园开关:closeroom";
/*		if(wizardp(me))
		{
			str += ZJSEP+HIG"修改属性"NOR":wizlian"ZJSEP+HIG"复制物品"NOR":clone"ZJSEP+HIG"创建NPC"NOR":crnpc"ZJSEP+HIG"删除NPC"NOR":delnpc";
			str += ZJSEP+HIG"放置NPC"NOR":putnpc"ZJSEP+HIG"创建物品"NOR":critem";
			str += ZJSEP+HIG"创建技能"NOR":crskill"ZJSEP+HIG"编辑技能"NOR":edskill"ZJSEP+HIG"查看排行"NOR":tops";
		}*/
		message("vision", str+"\n", me);
	}
	else if(arg=="-l")
		F_LEVEL->improve_level(me);
	else if(arg=="-t")
		F_LEVEL->up_tianfu(me);
	else if(arg=="-s")
		F_LEVEL->up_skills(me);
		else if (sscanf(arg, "%s %s", str, arg) == 2&&str=="-t")
	F_LEVEL->up_tianfu(me,arg);
	return 1;
}

int help(object me)
{
     write(@HELP
指令格式: uplv [-s]

这个指令让你消耗经验提升等级。

HELP
    );
    return 1;
}
