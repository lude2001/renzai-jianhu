// Room: /d/songshan/junjigate.c
inherit ROOM;

void create()
{
	set("short", "������Ժɽ��");
	set("long", @LONG
��ɽ�������ų� "����" �������Ǳ��Ƿ�̴��£���������
ȴ�ѳ�Ϊ��ɽ�������˵�ס�������Ͽ��Ե������̨��
LONG );
	set("exits", ([
		"southdown" : __DIR__"shandao6",
		"northup"   : __DIR__"chanyuan",
		"westup"    : __DIR__"fengchantai",
	]));
	set("objects", ([
		__DIR__"npc/tang" : 1,
		__DIR__"npc/wan" : 1,
	]));
	set("no_clean_up", 0);
	setup();
}
