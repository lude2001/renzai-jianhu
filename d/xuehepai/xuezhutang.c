//xuezhutang��c  by baby

#include <room.h>

inherit ROOM;

void create()
{	
	seteuid(getuid());
       set("short", "Ѫ����");
	set("long", @LONG
�����Ǻϻ��ڵ�Ѫ���á��˴��������̲����ڵأ������������ϣ���
̤������о�����͸�����������ϻ���֮�����ܰ���Ⱥ�ۣ��������֣�
�����ΰ��Ͻ����Ź������Ƿֲ����ġ����ڵ���������֮ǿ���ڶ���ɵ�
����һָ����ȻѪ�ӵ��Ӻ����ڽ���������Ȼ���ɵ�������Ȼ�ò��ٺ���
֮ͽ����ðȻǰ�����ơ������Ĵ������̾ߺͼҷ���ʹ�˲���ë���Ȼ��
LONG);	
	set("valid_startroom",1);
	set("exits", ([
		"east" : __DIR__"weitiange",
		"west" : __DIR__"xueku",
	]));

        set("area", "����");

        setup();

	replace_program(ROOM);
}
