#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    log_file("api_log", ctime(time()) + "执行命令，对象" + me->query("name") + "传入参数：" + arg + "\n");
    if (!arg)
	return notify_fail("什么？！\n");

    if(arg == "guaji"){
            log_file("api_log", ctime(time()) + "进入判断一。\n");
        if (me->is_busy() && ! me->query("doing"))
        {
            log_file("api_log", ctime(time()) + "进入判断二。\n");
            write("启动模拟线程开始离线挂机\n");
        }
		return 1;
    }
}