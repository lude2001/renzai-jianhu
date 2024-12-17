inherit F_DBASE;
#include <localtime.h>

void create()
{
	seteuid(getuid());
	set("channel_id", "��ʱ�ϵͳ");
	CHANNEL_D->do_channel( this_object(), "sys", "��ʱ�ϵͳ�Ѿ�������"NOR);
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
	//Sun(������) Mon(����һ)  Tue(���ڶ�)  Wed(������)  Thu(������)  Fri(������)  Sat(������)
	d = times[0..2];//����
	h = to_int(times[10..12]);//ʱ
	s = to_int(times[14..15]);//��
	
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