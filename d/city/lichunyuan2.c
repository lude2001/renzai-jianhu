// Room: /city/lichunyuan2.c
// Dec.12 1997 by Venus
inherit ROOM;
void create()
{
	set("short", "����Ժ��¥");
	set("long", @LONG
��վ������Ժ��¥���������������첻�����ơ����õľ��Ծ��µ�
���ϵ��£�ͻȻ�������Ī�����ջ�ͳ嶯��
    �������������ǧ�������ڵ��ֶ����㣬���뵽���ǿ��ܾ�������
�����е��۸��ڶ�����ʱ��Ϊ���ġ�
LONG);
	set("exits", ([

	    "down" : __DIR__"lichunyuan",
	]));
	set("objects", ([
	    __DIR__"npc/guigong" : 1,
	]));
	set("no_clean_up", 0);
	set("no_fight", "1");
	set("no_steal", "1");
	set("no_beg", "1");
	set("piao_room", "1");
	setup();
}
int valid_leave(object me, string dir)
{
    me = this_player();
    if (me->query_condition("prostitute"))
      return notify_fail("�깫һ�ѱ�ס�㣺�����������ӣ�\n");
    else  return 1;
}