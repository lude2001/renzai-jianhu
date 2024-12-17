// berserk.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string str,name,type,*pfms;
	mapping pfm;
	int i;

	if (!arg)
		return notify_fail("你想查看什么资料的详细资料？\n");

	if (file_size(SKILL_D(arg) + ".c") <= 0)
		return notify_fail("系统中没有你要查的这种技能。\n");
	str = ZJOBLONG"技能名字："+to_chinese(arg)+"("+arg+")";
	if(SKILL_D(arg)->query_txt())
		str += ZJBR + SKILL_D(arg)->query_txt();
	str += ZJBR"一一一一一一一一一一一一一一一一一一一一";
	str += ZJBR"绝技：";
	if(mapp(pfm = SKILL_D(arg)->query_pfm()))
		pfms = keys(pfm);
	for(i=0;i<sizeof(pfms);i++)
	{
		sscanf(pfm[pfms[i]],"%s:%s",name,type);
		str += ZJBR + replace_string(name,ZJBR,"") + "(" + pfms[i] + ")";
		if(file_size(SKILL_D(arg+"/perform/"+pfms[i])+".c")>0 && SKILL_D(arg+"/perform/"+pfms[i])->query_txt())
			str += ZJBR + SKILL_D(arg+"/perform/"+pfms[i])->query_txt();
		else if(file_size(SKILL_D(arg+"/exert/"+pfms[i])+".c")>0 && SKILL_D(arg+"/exert/"+pfms[i])->query_txt())
			str += ZJBR + SKILL_D(arg+"/exert/"+pfms[i])->query_txt();
		else if(file_size(SKILL_D(arg+"/"+pfms[i])+".c")>0 && SKILL_D(arg+"/"+pfms[i])->query_txt())
			str += ZJBR + SKILL_D(arg+"/"+pfms[i])->query_txt();
	}
	if(!i)
		str += "无";
		str += ZJBR"一一一一一一一一一一一一一一一一一一一一";
		str+="\n";
		str+=ZJOBACTS2+ZJMENUF(3,3,10,30);
		str+=HIY"激发"NOR+HIW+to_chinese(arg)+NOR":skills "+arg+ZJSEP;
//		str+=HIY"取消"NOR+HIW+to_chinese(arg)+NOR":jifa "+arg+" none"ZJSEP;
		str+=HIY"准备"NOR+HIW+to_chinese(arg)+NOR":prepare "+arg+ZJSEP;
		str+=HIY"研究"NOR+HIW+to_chinese(arg)+NOR":research "+arg+ZJSEP;
		str+=HIY"练习"NOR+HIW+to_chinese(arg)+NOR":lian "+arg+ZJSEP;
		str+=HIY"放弃"NOR+HIW+to_chinese(arg)+NOR":abandon "+arg+ZJSEP;
	write(str + "\n");

	return 1;
}

int help (object me)
{
	write(@HELP
指令格式: chaski
 
这个指令让你查看技能的详细资料。

HELP );
	return 1;
}
