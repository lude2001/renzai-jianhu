
inherit F_CLEAN_UP;

int lv_fa(object me,string family_name);

int main(object me, string arg)
{

	string *chooseList = ({ "蜀山派","唐门世家","合欢宗" });
	string *yjList;
	int tg = 0;

	// if (!me->query("family"))
	// return notify_fail("你还是先找个门派再看看自己有没有被推荐的资格吧！\n");

	if (!me->query("yijing"))
	return notify_fail("你尚未归真如何可以获取推荐资格,年轻人不要好高骛远。\n");

	yjList = keys(me->query("yijing"));

	foreach (string name in yjList)
	{
		string family_name = me->query("yijing/" + name + "/" + "family/family_name");

		if (!me->query("yijing/" + name + "/family"))
			continue;

		if ((lv_fa(me,family_name) && FAMILY_D->query_family_leader(family_name) == me->query("id")) || wizardp(me))
			tg = 1;
	}

	if (!tg)
	return notify_fail("你没有在本周没有获得意境归真门派的首席大弟子身份，无法获得推荐资格。\n");


	if (me->query("family"))
	return notify_fail("你有门有派，无法获取资格，还是归真等待师门恩准出户后再说吧！\n");
	
	// if (!lv_fa(me,me->query("family/family_name")) || !FAMILY_D->query_family_leader(me->query("family/family_name")) != me->query("family/famiy_name"))
	// return notify_fail("你还没有获得" + me->query("family/family_name") + "首席弟子的身份，没有推荐资格。\n");


	if (!arg)
	{
		string *list = ({ }),msg = ZJOBLONG"请你选择需要推荐去的高阶门派\n";

		foreach (string choose in chooseList)
		{
			list += ({ choose + ":mengpai_tuijian " + choose });
		}

		msg += ZJOBACTS2 + implode(list,ZJSEP);
		msg += "\n";

		write(msg);
	}

	if (arg)
	{

		if (!member_array(arg,chooseList) == -1)
		return notify_fail("该门派尚未开放。\n");

		me->set("mengpai_tuijian/" + arg,1);

		write(sprintf("恭喜你以首席大弟子的身份，获得了推荐到%s的资格。\n",arg));

	}

    return 1;
}

//1代表经历过这次意境领悟
int lv_fa(object me,string family_name)
{
    if (!me->query("yijing"))
    return 0;
    
    foreach (string name in keys(me->query("yijing")))
    {
        if (me->query("yijing/" + name + "/family/family_name") == family_name)
        return 1;
    }
    return 0;
}