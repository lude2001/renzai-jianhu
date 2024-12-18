// enchase.c

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	string msg, item, tessera;
	object *baoshi,obj, dest;
	int i,place;


	if (! arg)
		return notify_fail("你要往什么道具上镶嵌物品？\n");

	if (me->is_busy())
		return notify_fail("先忙完了你的事情再做这件事情吧！\n");

	if (me->is_fighting())
		return notify_fail("你现在正在打架，没时间做这些事情。\n");
		
if (sscanf(arg, "%s with %s set %d", item, tessera,place)==3)
   {
	if (! objectp(obj = present(tessera, me)))
		return notify_fail("你身上没有这样东西可以用来镶嵌。\n");
		
	if (! objectp(dest = present(item, me)))
		return notify_fail("你身上没有这样道具。\n");
	
	if (dest->item_owner() != me->query("id"))
		return notify_fail("这武器不是你的啊...\n");
      
    if (me->query("max_neili")<200)
    return notify_fail("你的内力修为如此薄弱，怎么可能把宝石镶嵌进武器里呢？\n");
    
		me->add("max_neili",-200);
		
	if (random(3)>=1)
	return notify_fail("你想将"+obj->query("name")+"镶嵌进"+dest->query("name")+"，无奈受到强烈排斥，只好作罢。\n");
	
	write("恭喜你镶嵌成功！\n");
	
	return dest->inlay_gem(obj, place);	
	
	}
	
	if (sscanf(arg, "%s with %s", item, tessera) < 2)
	{
	if (! objectp(dest = present(arg, me)))
		return notify_fail("你身上没有这样道具。\n");
		baoshi = filter_array(all_inventory(me),(:$1->query("can_be_inlay"):));
		if(sizeof(baoshi))
		{
			msg = ZJOBLONG"请选择你要镶嵌的宝石：\n"ZJOBACTS2+ZJMENUF(3,3,10,30);
			for(i=0;i<sizeof(baoshi);i++)
			{
				msg += baoshi[i]->query("name")+"("+baoshi[i]->query("can_be_inlay/skill")+"):inlay "+arg+" with "+baoshi[i]->query("id");
				if(i<(sizeof(baoshi)-1)) msg += ZJSEP;
			}
		}
		else
		{
			msg = ZJOBLONG"你身上现在没有宝石，不能进行镶嵌！";
		}
		tell_object(me,msg+"\n");
		return 1;
	}
	
   if (sscanf(arg, "%s with %s", item, tessera)==2)
   {
   
     int hole;
  if (! objectp(dest = present(item, me)))
		return notify_fail("你身上没有这样道具。\n");   
     
		
     hole=dest->query("magic/hole");
    i = 1;
     msg = ZJOBLONG+dest->name()+"一共有"+hole+"个孔位，请选择你要镶嵌的孔位：\n"ZJOBACTS2+ZJMENUF(3,3,10,30);
			while(i <= hole)
			{
			 if (mapp(dest->query("hole/"+i)))
              {
              i++;
			  continue;
			  }
			   msg += "孔位"+chinese_number(i)+":inlay "+item + " with " + tessera + " set "+i;
			   if (i < hole)
				msg += ZJSEP;
				i++;
			}
			tell_object(me,msg+"\n");
			return 1;
   }
   
	return 1;
}

int help(object me)
{
write(@HELP
指令格式 : inlay <道具> with <特殊物品> set <孔位>

这个指令可以让你将某样特殊物品镶嵌到另外一种道具上，使得道具
具有特殊的能力。
HELP
    );
    return 1;
}
