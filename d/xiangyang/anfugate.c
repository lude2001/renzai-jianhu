// Room: /d/xiangyang/anfugate.c
inherit ROOM;

void create()
{
	set("short", "����ʹ����");
	set("long", @LONG
���ǰ���ʹ���ŵĴ��ţ�ͭƤ�����ƺ���Ϊ���أ�������
�������λε�ͭ�������Ž��գ�����ȴ����һ������Ц������
�ſڵ���ɱ�ܲ�Э���������������ʹ���˵����ӻ��ǹ�����
����ġ�
LONG );
	set("outdoors", "xiangyang");
	set("no_clean_up", 0);

	set("exits", ([
		"south" : __DIR__"anfupailou",
	]));
	setup();
}