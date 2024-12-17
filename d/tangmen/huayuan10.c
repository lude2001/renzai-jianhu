// Room: /dream/huayuan10.c
// xws 1998/11/05
inherit ROOM;
void create()
{
	set("short", "花园");
	set("long", @LONG
	这是一大片花园。唐门地处蜀南,占地广阔，气候适宜花草生长。加上唐门弟
练功之余，皆喜欢侍弄花草，所以整个花园品种繁多，终年花团锦簇,非常漂亮。花从
中很多罕见珍贵的花草，不单可以让人欣赏玩味，还有不少妙用。
LONG
	);
        set("outdoors", "tangmen");
	set("exits", ([
		"north" : __DIR__ "kuixinlou",
		"south" : __DIR__ "huayuan11",
        ]));
	setup();
	replace_program(ROOM);
}

