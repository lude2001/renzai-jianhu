// tygate2.c 孟坩直壇
// by Marz 

inherit ROOM;

void create()
{
	set("short", "孟坩直壇");
	set("long", @LONG
低恠壓匯訳宥吏孟峯爽侮侃議弌祇貧��念中嗤倖孟直壇(door)。
LONG );
	set("outdoors", "wudang");
	set("item_desc",([
		"door"	:	"\n\t\t\t孟直壇貧嗤遍鮒��\n\n\n" 
					"\t\t）））））））））））））））））））））\n"
					"\t\t）））　　　　　　　　　　　　　　　）））\n"
					"\t\t）））　肇　定　書　晩　緩　壇　嶄　）））\n"
					"\t\t）））　　　　　　　　　　　　　　　）））\n"
					"\t\t）））　繁　中　孟　雑　�燹〉魁〆譟　法法�\n"
					"\t\t）））　　　　　　　　　　　　　　　）））\n"
					"\t\t）））　繁　中　音　岑　採　侃　肇　）））\n"
					"\t\t）））　　　　　　　　　　　　　　　）））\n"
					"\t\t）））　孟　雑　卆　症　丶　敢　欠　）））\n"
					"\t\t）））　　　　　　　　　　　　　　　）））\n"
					"\t\t）））））））））））））））））））））\n\n\n",
							
	]));
	set("exits", ([
		"north" : __DIR__"tyroad10",
	]));
	set("no_clean_up", 0);
	setup();
}
