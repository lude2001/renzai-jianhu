//zoulang1��c             �ϻ���--����

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
�����Ǻϻ�����������ȡ����������Ŵ�Ƭ�����֣�������죬��Ӱ
��涣���ʵ������⣬���в��ٱ���ϡ�е������м����У��������ϣ���
����������������ͨ�����᷿��
LONG);
	set("outdoors","����");
	set("valid_startroom",1);
	set("exits", ([
		"west" : __DIR__"qingfengge",
		"north" : __DIR__"weitiange",
		"east" : __DIR__"liangongfang1",
		"south" : __DIR__"dongxiangfang",
	]));
	setup();
}

int valid_leave(object me,string dir)
{
        object ob;

        mapping myfam;
	me=this_player();
        myfam=(mapping)me->query("family");

	if (dir=="east")
	{
        if (!myfam || myfam["family_name"]!="�ϻ���")
            return notify_fail("�㲻�Ǻϻ��ڵĵ��ӣ����ܽ�ȥ��\n");

        if ( me->query("gender")!="����")
            return notify_fail("�������е��ӵ���Ϣ�ң��㲻�ܽ�ȥ��\n");

	}
        return ::valid_leave(me, dir);

}