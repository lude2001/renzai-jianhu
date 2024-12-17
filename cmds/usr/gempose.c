#include <ansi.h>

inherit F_CLEAN_UP;
#define GEM  "/clone/gem/"
int main(object me, string arg)
{
object suipian;
//碎片数量必须大于10
 if (objectp(suipian = present("gem suipian", me))&&to_int(suipian->query_autoload())>=10)
 {
   string obname,*all_gem;
   object gemob;
   all_gem=list_dirs(GEM);   
   
   if (me->query("balance")<5000000)
   return notify_fail("您的钱庄存款不足500两黄金。\n");
   
   me->add("balance",-5000000);
   if (random(10)==1)
    {
    suipian->add_amount(-10);
    gemob = new(GEM+all_gem[random(sizeof(all_gem))]);
    gemob->move(me);
    tell_object(me,"只见一声脆响，宝石碎片完美的融合起来，恭喜您获得了"+gemob->query("name")+"，运气不错哦！\n");
    }
    else 
    tell_object(me,"一声脆响过去，只见宝石碎片在融合过程剧烈排斥，又退了回来。\n");
    
   }
   else 	return notify_fail("您身上的宝石碎片数量不够啊。\n");
   return 1;
}