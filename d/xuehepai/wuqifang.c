// wuqiku.c ������

// mlf���,lks���



#include <ansi.h>



inherit ROOM;



void create()

{

	set("short","������");

	set("long",

          "�����Ǻϻ��ڵ����������������ֻ����������ȫ����������ǽ�ı�
�����ϰڷŵĶ��ǳ�������ǹ��ì��ꪣ����������棬�ң�鳵ȡ������

���Լ�ϲ������������ʦ����̡���Ȼ��Ҳ�����Ȱ�ʦ����������Ӧ����

����\n"NOR

     	);

     	set("valid_startroom",1);

	set("exits",([

                  "south" : __DIR__"chufang",
     	]));

     	set("objects",([

		//"/clone/weapon/dandao" : 1,

		//"/d/xuehepai/obj/tiegong" : 1,
		//"/clone/weapon/changjian" : 1,

        // "/clone/weapon/tielianzi" : 2,
		//"/clone/weapon/changbian" : 1,
     	]));

     	setup();

     	replace_program(ROOM);

}

     