// time.c

#include <ansi.h>
#include <getconfig.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{

	write(sprintf("%s���ڵ�ʱ���ǣ�\n%s��\n" ,
		      HIR + LOCAL_MUD_NAME() + NOR,
		      NATURE_D->game_time(),));
		write (HIY"��Ļ�Աʱ�仹ʣ��"+CHINESE_D->chinese_time(me->query("zjvip/times"))+ "��"NOR"\n");	
	write("--------" + me->query("birthday") + "-----" + time() + "\n");
	return 1;
}

int help(object me)
{
     write(@HELP
ָ���ʽ: time

���ָ������(��)֪�����ڵ�ʱ����

HELP
    );
    return 1;
}