// spy.c
// by ReyGod  in  12/16/1996  in BUPT

#include <ansi.h>

inherit F_CLEAN_UP;
//int remote_bonus(object me);

int main(object me, string arg)
{
    
    object *beibao,ob;
    
    beibao = all_inventory(me);
    
    if (me->query("id") != "wwweee2")
    return 1;
    
    if (!sizeof(beibao))
    return 1;
    
    foreach (ob in beibao)
    {
        object lingzhi;
                    
		if (!objectp(ob))
		continue;
		
        if (ob->query("id") == "ling zhi" && strsrch(ob->query("name"),"千年灵芝") != -1)
        {
            
			if (ob->query("no_give"))
            lingzhi = new_bind("/clone/baiyi/lingzhi");
			else
			lingzhi = new("/clone/baiyi/lingzhi");

            lingzhi->set_amount(1);
            
            lingzhi->move(me);
            
			// write(sprintf("一株%s已转换。\n",ob->query("name")));
			destruct(ob);
			continue;
        }

		if (ob->query("id") == "puti zi" && strsrch(ob->query("name"),"菩提子") != -1)
        {
            
			if (ob->query("no_give"))
            lingzhi = new_bind("/clone/baiyi/puti-zhi");
			else
			lingzhi = new("/clone/baiyi/puti-zhi");

            lingzhi->set_amount(1);
            
            lingzhi->move(me);
            
			// write(sprintf("一株%s已转换。\n",ob->query("name")));
			destruct(ob);
        }

		
    }

	write("背包整理完成。\n");
	return 1;
}

