// gate��c  ����
// mlf��ƣ�lks���



#include <ansi.h>

#include <room.h>


inherit ROOM;

void create()

{

        set("short","�ϻ��ڴ���");
	set("long",@LONG

�����Ǻϻ��ڵĴ��ţ������Ϸ������ĽǷ��ܣ����������ĸ�����ʯ
������������ͼ�ڵװ�����������������һ����ң����С�Ѫ�����¡���
��Ѫ����֣������پ���Ϊ��ɽ��ʦʢ�������顣���ص��������϶�����
������һ���ǡ��󽭶�����������������ͩһҹ���䡱��һ���ǡ�������
ȥ�����ǽ�Я�齭�����Ρ�����������������׳־����Ȼ������
LONG);
	set("valid_startroom",1);

	set("outdoors","����");
	set("exits",([

        	"north" : __DIR__"xuehuatang",
        	"south" : "/d/longmen/shanlu5",
	]));
	
	set("objects",([
		__DIR__"npc/guanshi" : 1,

	]));

	setup();

    replace_program(ROOM);
}
