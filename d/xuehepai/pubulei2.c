
inherit ROOM;
void create()
{
        set("short","����");
        set("long",@LONG
�������������ˮ��������Ȼ���ж��졣�����Ǻϻ���ǰ�ε�
ʮһλ���ŵ�����֮�أ����Ǻϻ��ڵĴ�ͳ��Ϊ�˲��úϻ��ڵ���ѧʧ
������ȥ���Ұɣ�˵��������ʲô������������
LONG );
        set("valid_startroom",1);
        set("class","�ϻ���");
       set("exits",([
                "south" : __DIR__"pubulei1",
                "east" : __DIR__"center",
        ]));
//        set("no_clean_up"�� 0);
        setup();
           replace_program(ROOM);
}


