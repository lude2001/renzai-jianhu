// Room: /d/quanzhou/penghu.c
// Date: May 7, 96   Jay

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
���Ϊ̨����������Ͽ���ƣ�̨�����ϡ��������ڶ�
Ϊ����������������������������
    ��������(zhou)��(chuan) ������½̨�����岨����
�У����������ζ��
LONG );
	set("item_desc", ([
		"chuan" : "һ���󺣴�����Զ��û�����Ĵ��ɲ��С�\n",
		"zhou"  : "һ��ˮ��ս�ۣ�ǰ��̨�壬���ÿ�����\n",
	]));
	set("objects", ([
		__DIR__"npc/liu": 1,
		"/d/city/npc/bing" : 4,
	]));
	set("outdoors", "quanzhou");
	setup();
}

void init()
{
	add_action("do_enter", "enter");
}

int do_enter( string arg)
{
	object ob;
	string dir;

	ob = this_player();
	if (arg !="chuan" && arg !="zhou")
	{
		tell_object(this_player() , "��Ҫȥ�Ķ���\n" ) ;
		return 1;
	}

	if (arg == "chuan")
	{
		message_vision("����һ�������ϴ���æ����һ��������ඣ�\n", ob);
		message_vision("�������𷫣�����������˳�纽�С�\n", ob);
		call_out("tdalu", 10, ob);
	} else
	{
		message_vision("ˮ��һ�������ϴ���æ����һ��������ඣ�\n", ob);
		message_vision("ˮ�����𷫣������򶫷���纽�С�\n", ob);
		call_out("ttaiwan", 10, ob);
	}

	ob->move(__DIR__"dahai");
	tell_object(ob, BLU "���ں��Ϻ����˺ܾúܾ�......."NOR"\n");
	return 1;
}

void tdalu(object ob)
{
	if (! objectp(ob) || find_object(__DIR__"dahai") != environment(ob))
		return;

	tell_object(ob , "�����ڵִ�����ԭ��һ���������С������´�����\n");
	ob->move(__DIR__"haigang");
}

void ttaiwan(object ob)
{
	if (! objectp(ob) || find_object(__DIR__"dahai") != environment(ob))
		return;

	tell_object(ob , "ս�����ڵִ���̨���һ���ưܳ��С������´�����\n");
	ob->move(__DIR__"chiqian") ;
}