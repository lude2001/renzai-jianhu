//qixuetang��c           �ϻ���--��Ѫ��

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "��Ѫ��");
	set("long", @LONG
��������Ѫ�ã����ںϻ��ڵ������صء�Ϊ��ֹ�����Ϯ��Ҫ���˵�
�ؿ����ء�������һ��ׯ�أ��ֺܵ��ŵĽ����������ú�ᣰ������Եü�
Ϊɭ�ϣ���������ʮ����������ÿ������������ʮ�������������ķ����
����������һЩ�������ޡ������ϵ��������緢�ġ�Ѫ�����¡��ĸ�����
��ʹ�˲��ͶԺϻ�����Ȼ�𾴣��˴�Ϊ�ϻ��ڵ���ÿ��ѡ���ἰ���ڴ�
С�����������ڵء���ˣ�������ʱ������䣬�ɼ��ɷ��Ͻ���
LONG);
	set("exits", ([	
        	"eastdown" : __DIR__"zoulang5",
        	"north" : __DIR__"xueku",
        	"northwest" : __DIR__"yanwuchang",
        	"south" : __DIR__"xuehuatang",
	]));
	setup();
          //"/clone/board/xuehe_b"->foo(); '�������԰壬�������ò���
	replace_program(ROOM);
}
