// cundaota2.c ���������

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "���������");
	set("long", @LONG
�����Ǵ�����Ķ��㣬���������������������졣����տ���
Ҳ������Ҳ��ȫ��ȫ������ǽ�ȥ�Ķ��ˡ�
LONG
	);
	set("exits", ([
		"northup" : __DIR__"cundaota3",
		"southdown" : __DIR__"cundaota1",
	]));
	set("no_clean_up", 0);
	setup();
}