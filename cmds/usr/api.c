#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    log_file("api_log", ctime(time()) + "ִ���������" + me->query("name") + "���������" + arg + "\n");
    if (!arg)
	return notify_fail("ʲô����\n");

    if(arg == "guaji"){
            log_file("api_log", ctime(time()) + "�����ж�һ��\n");
        if (me->is_busy() && ! me->query("doing"))
        {
            log_file("api_log", ctime(time()) + "�����ж϶���\n");
            write("����ģ���߳̿�ʼ���߹һ�\n");
        }
		return 1;
    }
}