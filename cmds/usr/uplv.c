// time.c

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string str;
	if(!arg)
	{
		str = ZJOBLONG"������ڽ�ɫ��Ϣ��鴦���������⣺\n";
		str += ZJOBACTS2+ZJMENUF(3,3,10,30);
		str += "��ɫ�ȼ�:uplv -l"ZJSEP"���ܵȼ�:uplv -s"ZJSEP"��ɫ�츳:uplv -t"ZJSEP"��������:abandon exp"ZJSEP"�澭ʮ����:beat";
		str += ZJSEP"�����ֵ�:brothers"ZJSEP"��������:abandon exp"ZJSEP"�ٻ�װ��:summon all"ZJSEP"�����ƺ�:title"ZJSEP"���˴���:pkd"
		ZJSEP"��Աʱ��:time"ZJSEP"�޸Ĵº�:nick"ZJSEP"ս������:topten"ZJSEP"���ϵͳ:banghui"
		ZJSEP"�ۺ�����:tops"ZJSEP"����ϵ��:wimpy"ZJSEP"�˳���Ϸ:quit";
		if (environment(me)->query("owner_build")==getuid(me))
			str += ZJSEP"�޸�����:changepasswd"ZJSEP"�澭����:beat"ZJSEP"������԰:crroom"ZJSEP"������԰:crroom"ZJSEP"�޸ļ�԰:edroom"ZJSEP"���ӹ���:edroom"ZJSEP"�������:delroom"ZJSEP"��԰����:closeroom";
/*		if(wizardp(me))
		{
			str += ZJSEP+HIG"�޸�����"NOR":wizlian"ZJSEP+HIG"������Ʒ"NOR":clone"ZJSEP+HIG"����NPC"NOR":crnpc"ZJSEP+HIG"ɾ��NPC"NOR":delnpc";
			str += ZJSEP+HIG"����NPC"NOR":putnpc"ZJSEP+HIG"������Ʒ"NOR":critem";
			str += ZJSEP+HIG"��������"NOR":crskill"ZJSEP+HIG"�༭����"NOR":edskill"ZJSEP+HIG"�鿴����"NOR":tops";
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
ָ���ʽ: uplv [-s]

���ָ���������ľ��������ȼ���

HELP
    );
    return 1;
}
