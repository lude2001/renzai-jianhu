//liangongfang��c         ���źϻ���--������

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "������");
	set("long", @LONG
�����Ǻϻ��ڶ����������������ϱ�ĵط��ְ��������࣬ԭ����
��Ϊ���������ڵ��������ڹ����ķ��ľ��ң�Ѫ���ڹ�ǿ��������������
��������ȫ����������û�˸��ڴ˴�������
LONG);
        set("valid_startroom",1);
	set("exits", ([
                        "east" : __DIR__"zoulang3",
	]));
        set("area", "����");
	setup();
	replace_program(ROOM);
}