//TOHTQ7.C

inherit ROOM;

void create()
{
	set("short", "山洞");
	set("long", @LONG
山洞中似乎深不可测，洞壁上点着几盏松明，照得洞内一派光
亮。洞内虽然感到十分潮湿，可洞壁干燥坚实，大异平常。
LONG );
	set("exits", ([
		"north" :__DIR__"tohtq7",
		"west"  :__DIR__"tohtq5",
	]));
	set("outdoors", "mingjiao");
	set("no_clean_up", 0);
	setup();
}
