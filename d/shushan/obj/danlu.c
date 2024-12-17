//shushan2 by yushu@SHXY 2000.12
inherit ITEM;
#define BYAOCAO       "/d/shushan/obj/yaocai"
void create()
{
  set_name("金丹炉", ({ "jin danlu", "danlu" }) );
  set_weight(300000);
  set_max_encumbrance(8000);
  if( clonep() )
    set_default_object(__FILE__);
  else {
    set("unit", "鼎");
    set("long", "这是一鼎道家用来炼丹的大金炉, 你可以用(liandan)来炼制丹药。\n");
    set("value", 2000);
  }
}

void init()
{
	add_action("do_liandan", "liandan");
}

int do_liandan()
{
	object yaocai, lingyao;
	object me=this_player();
	if(!yaocai=present("yaocai", me))
		return notify_fail("你身上没有药材...你想拿什么练啊!\n");
	if(base_name(yaocai)!=BYAOCAO)
		return notify_fail("嘿嘿...想来这招? 可惜hanchat很聪明哦!\n");
	if(me->query_skill("force", 1)<1000)
		return notify_fail("你的基本内功太低了，没办法承受炼丹过程的热度。\n");
	if(me->query("eff_qi")<1000)
		return notify_fail("你已经受伤了，万一血流进金丹炉怎么办,还是快去疗伤吧!\n");
	message_vision ("$N将身上的药材投入金丹炉，开始炼制了起来！\n",me);
	me->start_busy(20);
	if(random(10)>8)
	{
		tell_object(me, "丹药练制成功！\n");
		lingyao=new("/d/shushan/obj/lingyao");
		lingyao->move(me);
		destruct(yaocai);
		return 1;	
	}
	else
	{
		tell_object(me, "你一不留神被金丹炉内的熊熊烈火给烧伤了！\n");
		me->set("eff_qi", 100);
		return 0;
	}
}

