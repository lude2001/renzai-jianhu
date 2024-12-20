
// This program is a part of NITAN MudLIB

inherit ROOM;

void create()
{
        set("short", "有竹无肉轩"); 
        set("long", @LONG
这里便是『有竹无肉轩』，也和其他种满了竹子的院子一样，原
先本叫『听竹轩』。可是等到王动作主人的时候，就替它改了个名字，
叫『有竹无肉轩』，因为他觉得『听竹』这名字本来虽很雅，现在却
已变得很俗。他认为第一个用『听竹』作轩名的人虽然是个很风雅的
聪明人，但第八十个用『听竹』作轩名的人就是俗不可耐的笨蛋了。
轩中三面都开了很大的窗子，向外望去，满眼幽幽翠竹。
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
