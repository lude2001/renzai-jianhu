//Room: qunyuys4.c

inherit ROOM;

void create()
{
	set("short", "Ⱥ��¥����");
	set("long", @LONG
һ�����ҡ����з���һ�Ŵ󴲣����������廨�Ľ�������ͷ������
�������£��������������һ��Ϸˮԧ�죬��ɫ���ã����������
�ϵ���һ�����򣬺�������һ��������һֻ��ױ���ӡ���ǰ����������
����Ь��һ���еģ�һ��Ů�ģ����Ŷ��á�
LONG);
	set("exits", ([ /* sizeof() == 1 */
		"west" : __DIR__"qunyulou2",
	]));
	set("objects", ([
       	 	__DIR__"npc/qingyi" : 1,
	]) );

	setup();
}