
// This program is a part of NITAN MudLIB

inherit ROOM;

void create()
{
        set("short", "����������"); 
        set("long", @LONG
������ǡ���������������Ҳ���������������ӵ�Ժ��һ����ԭ
�ȱ��С��������������ǵȵ����������˵�ʱ�򣬾��������˸����֣�
�С�����������������Ϊ�����á����������ֱ�������ţ�����ȴ
�ѱ�ú��ס�����Ϊ��һ���á�����������������Ȼ�Ǹ��ܷ��ŵ�
�����ˣ����ڰ�ʮ���á��������������˾����ײ����͵ı����ˡ�
�������涼���˺ܴ�Ĵ��ӣ�������ȥ���������Ĵ���
LONG );
        
        set("type","house");
        set("indoors", "fugui");
        set("exits",([
                "east":__DIR__"suishilu2",
                "west":__DIR__"cuizhuyuan1",
                "south":__DIR__"cuizhuyuan2",
                "north":__DIR__"cuizhuyuan3",
        ]) ); 
		        set("objects",([
                CLASS_D("mojiao/fuhongxue") : 1,
        ]));
        set("coor/x",-610);
        set("coor/y",220);
        set("coor/z",80);
        setup();
        replace_program(ROOM);
} 