inherit ROOM;
void create()
{
        set("short","��������");
        set("long",@LONG
�������������ˮ��������Ȼ���ж��졣�����Ǻϻ���ǰ�ε�
ʮһλ���ŵ�����֮�أ����Ǻϻ��ڵĴ�ͳ��Ϊ�˲��úϻ��ڵ���ѧʧ
�������Ѿ������˶��������ĵش����и��������������ϴ�����
LONG );
        set("valid_startroom",1);
        set("class","�ϻ���");
        set("exits",([
                 "out" : __DIR__"center",
        ]));
        set("objects",([
			"/d/xuehepai/npc/gui1" : 1,
			
        ]));
//        set("no_clean_up"�� 0);
        setup();
        replace_program(ROOM);
}

