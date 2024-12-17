inherit F_DBASE;
#include <localtime.h>

void create()
{
	seteuid(getuid());
	set("channel_id", "定时活动系统");
	CHANNEL_D->do_channel( this_object(), "sys", "定时活动系统已经启动。"NOR);
	set_heart_beat(20);
}

int dutu_ok = 1;
int mpz_ok = 1;

void check_time()
{
	int GMT = time();
	string d, times;
	int h, s;
	object room, ob;
	times = ctime(GMT);
	//Sun(星期日) Mon(星期一)  Tue(星期二)  Wed(星期三)  Thu(星期四)  Fri(星期五)  Sat(星期六)
	d = times[0..2];//星期
	h = to_int(times[10..12]);//时
	s = to_int(times[14..15]);//分
	
	if (h >= 17 && h <= 20 && 0 == s && dutu_ok)
	{
	    __DIR__"dshuodong/dutu/dutu_beichou"->start();
	    dutu_ok = 0;
	}
	
	if(h > 8 && h < 22)
	{
		if((s == 30) && mpz_ok)
		{
		    __DIR__"dshuodong/mpz/mpz"->start();
	    	mpz_ok = 0;
		}
	}
	
	if (s == 20)
	    dutu_ok = 1;
	if (s == 50)
	    mpz_ok = 1;
}

void heart_beat()
{
    check_time();
}