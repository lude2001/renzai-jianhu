// mtroad6.c  ɽ��ƽ��

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
������ɭ���е�һ��Сƽ�ء�����û�֣�Ұ�����������ܶ�����
�ܵ�ɭ�֡�ʱ��ʱ��������Ұ��˻�У�����������������һ����ͻأ
���𣬼����վ���
LONG );
	set("outdoors", "motianya");
	set("exits", ([
	    "east"  : __DIR__"mtroad4",
	    "west"  : __DIR__"mtroad4",
	    "north" : __DIR__"mtroad4",
	    "south" : __DIR__"mtroad4",
	]));

	setup();
}
