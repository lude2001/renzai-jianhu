#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "�ݵ�");
    set("long", @LONG
������һƬ����Ĳݵأ��м�����������ˣ�����ܿ����˸�ɫ��
�ʻ���һ�����紵�������µĿ����д������Ƶ����Ļ��㡣
LONG );

	set("exits", ([
		"west" : __DIR__"jingji/enter",
		"south" : __DIR__"kongdi",
		"north" : __DIR__"xiaowu",
	]));
	set("outdoors", "shenlong");
	setup();
}

