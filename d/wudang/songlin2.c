//Room: songlin2.c ����
//Date: Sep 22 1997

inherit ROOM;

void create()
{
      set("short","����");
      set("long",@LONG
������������������գ�������ֻ�о�������ǰ�󵽴�
������Ӱ��������һ�����������ã�������ӫӫ���׹⡣�㾪
��֮�䣬һ�Ų��ڸ����������ϣ�
LONG);
      set("outdoors", "wudang");
      set("objects", ([
	   CLASS_D("wudang") +"/famu": 2,
      ]));
      set("exits",([ /* sizeof() == 1 */
	  "north"  : __DIR__"songlin4",
	  "south"  : __DIR__"slxl2",
      ]));
//      set("no_clean_up", 0);
      setup();
      replace_program(ROOM);
}