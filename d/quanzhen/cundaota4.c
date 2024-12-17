// cundaota4.c 存道塔顶
#include <ansi.h>

inherit ROOM;
int do_jingxiu(string arg);
int jingxiu(object me);
void create()
{
	set("short", "存道塔顶");
	set("long", @LONG
这里是存道塔的塔顶，塔梯到这里就到了尽头。墙壁上开着几
个窗户(window)，几个中年道人正捧着书苦苦研读。
LONG
	);
	set("exits", ([
		"southdown" : __DIR__"cundaota3",
	]));
	set("objects", ([
		__DIR__"npc/zhangjing" : 1,
	]));

	set("item_desc", ([
		"【窗口】": "窗外白云飘过，似乎你一伸手就可以抓住一片。\n",
	]) );

	set("count",1);
	setup();
}
void init()
{ 
	add_action("do_jingxiu", "jx");
}

int do_jingxiu(string arg)
{
	object me;
	int cost;

	me = this_player();
	if (me->is_busy())
		return notify_fail("等你忙完了手头的事情再说！\n");

	if (me->is_fighting())
		return notify_fail("你边打架一边静修？真有你的。\n");

	if (me->query("jing") < me->query("max_jing") * 7 / 10)
		return notify_fail("你现在的精不够，无法静修。\n");

	if (me->query_skill("taoism", 1) < 250)
		return notify_fail("你对道学心法理解太浅，静修获得不了什么进境。\n");

	if (! arg || ! sscanf(arg, "%d", cost))
		return notify_fail("你要花多少潜能进行静修？\n");

	if (cost >= me->query("potential") - me->query("learned_points"))
		return notify_fail("你现在没有这么多的潜能！\n");

	if (cost < 100)
		return notify_fail("这点也太少了吧？至少要花一百点潜能才能有所进步。\n");

	message_vision("$N找了一个地方坐了下来，闭目冥神，开"
		       "始专心研究道学心法。\n", me);

	me->set_temp("pending/jingxiu", 1);
	me->set_temp("potential_cost", cost);
	me->set_short_desc("正坐在地下冥神静修。");
	me->start_busy((:call_other, __FILE__, "jingxiu" :),
		       (:call_other, __FILE__, "halt_jingxiu" :));
	return 1;
}

int jingxiu(object me)
{
	int cost;

	cost = me->query_temp("potential_cost");
	if (cost > 0)
	{
		cost = random(cost) + 1;
		if (cost > 3) cost = 3;
	} else
		cost = 0;

	me->improve_skill("taoism", me->query_int() / 5 +
			  random(me->query_skill("taoism", 1) * cost));
	me->add("learned_points", cost);
	if (me->add_temp("potential_cost", -cost) > 0)
		return 1;

	me->set_temp("pending/jingxiu", 0);
	me->set_short_desc(0);
	message_vision("$N静修完毕，面露微笑，站了起来。\n", me);
	return 0;
}

int halt_jingxiu(object me)
{
	tell_object(me, "你睁开眼睛，站了起来。\n");
	tell_room(environment(me), me->name() + "慢慢的睁开了双眼，站了起来。\n", me);
	me->set_temp("pending/jingxiu", 0);
	me->delete_temp("potential_cost");
	me->set_short_desc(0);
	return 1;
}
