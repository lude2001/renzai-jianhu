// spy.c
// by ReyGod  in  12/16/1996  in BUPT

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	//判断所有的玩家，如果身上拥有多个储物袋那就打印出来
	object *obs,ob;

	obs = users();

	foreach (ob in obs)
	{
		int number = 0;
		string chuwu;
		object *wupings,wp;
		chuwu = "chuwu dai";
		wupings = all_inventory(ob);
		foreach (wp in wupings)
		{
			//如果wp的ip字符串包含chuwu字符串，那就说明这个玩家身上有储物袋
			if (strsrch(wp->query("id"),chuwu) != -1)
			{
				number++;
			}


		}

		if (number > 1)
		{
			write(ob->query("name")+"身上有"+number+"个储物袋。\n");

			//销毁多余的储物袋
			foreach (wp in wupings)
			{
				if (strsrch(wp->query("id"),chuwu) != -1)
				{
					number--;
					if (number > 0)
					{
						destruct(wp);
					}
				}
			}
			//打印ob还有多少个储物袋。
			write(ob->query("name")+"现在还有"+number+"个储物袋（清理后）。\n");
		}



	}

	return 1;
}
