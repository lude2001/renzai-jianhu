// spy.c
// by ReyGod  in  12/16/1996  in BUPT

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	int ddd = 0;

	if (find_player(arg))
	{
		object who = find_player(arg);

		foreach (string skill in keys(who->query_skills()))
		{
			who->set_skill(skill,who->query_skill(skill,1) + 1);
		}
	}

	return 1;
}
