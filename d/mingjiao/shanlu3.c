// Room: /d/mingjiao/shanlu3.c
inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
����ɽ·���ͣ�����һ�˶����·�����ͱڸ��ʣ�·�ҽ�����
����Ԩ��ʵ����һ�򵱹ء����Ī������Ҫ֮�����������ʣ���Ҫ
���������������ˡ�����·�ң���Ȼ����һ���ʯ���߽����ɣ���
Ϊ������ʯ����������������Զ���ƺ���
LONG );
	set("exits", ([
		"southdown" : __DIR__"shanlu2",
		"northup"   : __DIR__"shanlu4",
		"up"	: __DIR__"xuantianshi",
	]));
	set("no_clean_up", 0);
	set("outdoors", "mingjiao");
	setup();
}

int valid_leave(object me, string dir)
{
    if ((random((int)me->query_skill("dodge")) <= 20) && dir=="up")    
    {
	return notify_fail("��ʹ����һ�ģ���ʯ����������Զ�͵���������ˤ�ı������ף������ö������Ṧ�ˡ�\n");
    }
    if ((random((int)me->query_skill("dodge")) <= 35) && dir=="up")    
    {
	return notify_fail("�����һԾ��ȴ��ʯ������һ�ɶ�Զ�������ö������Ṧ�ˣ���ð׷�������\n");
    }
    if ((random((int)me->query_skill("dodge")) <= 60) && dir=="up")    
    {
	return notify_fail("������������ʯ��ֻ��һ����ˣ��ټӰѾ�����ȥ�������Ṧ��\n");
    }

    return ::valid_leave(me, dir);
}
