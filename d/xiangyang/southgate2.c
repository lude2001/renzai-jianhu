// Room: /d/xiangyang/southgate2.c
inherit ROOM;
#include <ansi.h>;

void create()
{
	set("short", "��ȸ����");
	set("long", 
"�����������ǵ��ϳ��ţ�ֻ�������Ϸ����������֡�"HIR"

		      ��ȸ��
"NOR"\n"
"�������ɹ��Ŵ��ַ������ǣ�����������൱���ܣ�һЩ�ٱ�
�������̲�Ҫ�������ǵ��ˡ������Ǻܴ�Ĳݵء�\n"
 );
	set("outdoors", "xiangyang");

	set("exits", ([
		"east"   : __DIR__"caodi4",
		"west"   : __DIR__"caodi5",
		"south"  : __DIR__"caodi6",
		"north"  : __DIR__"southgate1",
	]));
	set("objects", ([
		__DIR__"npc/pi"   : 1,
		__DIR__"npc/bing" : 2,
	]));
	setup();
}
