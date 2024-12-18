// yihua-jiemu.c 移花接木
// by rtm 00.03

inherit SKILL;

string *parry_msg = ({
	"$N一招击在$n身上，却被$n暗运移花接木，将内力尽数移入地下。\n",
	"$n轻轻一带，$N发现自己招数回击过来，吓得往后倒退几步。\n",
        "$n手臂回转，在$N手肘下轻轻一推，$N招数落空。\n",
        "$n右手伸出，在$N手腕上轻轻一拉，$N收势不住，直往前扑去。\n",
        "$n身形不动，$N一招击下，有如石沉大海，不觉呆住了。\n",
	"$n左牵右引，$N如身处漩流，连续转了好几个圈。\n",
	"$n双手回圈，$N只觉得前面好象有一堵墙，再也攻不进去。\n",
	"$n轻轻一转，$N一招击在地上，只打得尘土飞扬。\n",
});

string *dodge_msg = ({
	"$N一招击在$n身上，却被$n暗运移花接木，将内力尽数移入地下。\n",
	"$n轻轻一带，$N发现自己招数回击过来，吓得往后倒退几步。\n",
        "$n手臂回转，在$N手肘下轻轻一推，$N招数落空。\n",
        "$n右手伸出，在$N手腕上轻轻一拉，$N收势不住，直往前扑去。\n",
        "$n身形不动，$N一招击下，有如石沉大海，不觉呆住了。\n",
	"$n左牵右引，$N如身处漩流，连续转了好几个圈。\n",
	"$n双手回圈，$N只觉得前面好象有一堵墙，再也攻不进去。\n",
	"$n轻轻一转，$N一招击在地上，只打得尘土飞扬。\n",
});

int valid_enable(string usage) 
{ 
    return (usage == "parry") || (usage == "dodge");
}

string query_parry_msg(string limb)
{
       return parry_msg[random(sizeof(parry_msg))];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_teach(object me)
{
         if ((int)me->query_skill("yihua-jiemu", 1) > 1)
                return notify_fail("移花接木乃移花宫宫主所创,向来不传男子。\n");
return 1;
 }



int valid_learn(object me)
{
        int lvl = (int)me->query_skill("yihua-jimu", 1);

        if ( !wizardp(this_player()) && (me->query("family/family_name") != "移花宫"))
                return notify_fail("你不是移花宫弟子不能使用冥雨神功.\n
                                    移花接木博大精深, 非移花宫弟子不传, 真不知道你是怎么学会的!\n
                                    要是让两位宫主知道了你可惨了.\n");



        if ( me->query("gender") != "女性")
            return notify_fail("移花接木乃移花宫宫主所创,向来不传男子。\n");

		if ((int)me->query_skill("mingyu-shengong", 1) < 120)
            return notify_fail("你的冥雨神功还不到家怎么能学移花接木呢？\n");

		if ((int)me->query_skill("force", 1) < 100)
            return notify_fail("就这么点基本内功还想学移花接木？\n");
		
		if ((int)me->query_skill("parry", 1) < (int)me->query_skill("yihua-jiemu", 1))
            return notify_fail("招架等级小于移花接木，无法继续学习。\n");
		
		if ((int)me->query_skill("dodge", 1) < (int)me->query_skill("yihua-jiemu", 1))
            return notify_fail("轻功等级小于移花接木，无法继续学习。\n");

		if ((int)me->query("max_neili", 1) < 550)
			return notify_fail("就这么点内力还想学移花接木？\n");

        if ((int)me->query_skill("force", 1) < lvl)
            return notify_fail("你的基本内功火候还不够，小心走火入魔！\n");

        return 1;
}
