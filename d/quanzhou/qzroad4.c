// Room: /d/quanzhou/qzroad4.c
inherit ROOM;

void create()
{
	set("short", "ɽ·");
	set("long", @LONG
������һ��ɽ·�ϡ�ʱֵ���գ�·�Ե�ɽ���Ͽ����˽��ɫ���Ͳ˻���
�����ǽ������Ǽ��ˡ���������븣������ɽ����������һ����·����Ϣ��
С��ͤ��
LONG );
	set("exits", ([
		"north"   : __DIR__"jxnanmen",
		"west"    : __DIR__"qzroad3",
		"southup" : "/d/fuzhou/fzroad1",
		"east"    : __DIR__"chating",
	]));
	set("no_clean_up", 0);
	set("outdoors", "quanzhou");
	setup();
}
