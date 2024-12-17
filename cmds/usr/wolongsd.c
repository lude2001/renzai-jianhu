
inherit F_CLEAN_UP;

int sd(object me, int number);

int main(object me, string arg)
{
    string type;
    int number;

    if (!arg)
    {
        string msg = ZJOBLONG"人在江湖卧龙堡扫荡系统，请你选择扫荡方式。扫荡一次需要花费卧龙令 + 20通宝或通宝，每天签到赠送的一次免元宝扫荡，可以抵消20元宝。\n";
        msg += ZJOBACTS2"元宝扫荡一次:wolongsd yb 1"ZJSEP;
        msg += "元宝扫荡十次:wolongsd yb 10" ZJSEP;
        msg += "通宝扫荡一次:wolongsd tb 1" ZJSEP;
        msg += "通宝扫荡十次:wolongsd tb 10" ZJSEP;
        msg += "每日签到扫荡:wolongsd qd 1\n";
        tell_object(me, msg);
        return 1;
    }

    if (sscanf(arg, "%s %d", type, number) == 2)
    {

        int count;
        object ling;

        ling = present("wolong ling", me);

        if (!objectp(ling))
            return notify_fail("你没有卧龙令无法扫荡。\n");

        if (ling->query_amount() < number)
            return notify_fail("卧龙令的数量不够,无法扫荡。\n");

        if (number < 1)
            return notify_fail("你到底要扫荡几次？别乱扫荡。\n");

        if (!me->query_skill("force", 1))
            return notify_fail("你的基本内功等级太低了，无法扫荡卧龙堡。\n");

        if (me->query("combat_exp") < 4000000)
            return notify_fail("你的经验低于400万，无法扫荡卧龙堡。\n");

        if (time() / 86400 > me->query("wolongsd/time") / 86400)
        {
            me->delete ("wolongsd/number");
            write("卧龙扫荡次数已刷新。\n");
        }

        if (type == "qd")
        {
            if (me->query("wolongsd/qd_number") < number)
                return notify_fail("你今天的签到扫荡次数已经用光了。\n");

            me->delete ("wolongsd/qd_number");
            ling->add_amount(-number);
            sd(me, number);
            return 1;
        }

        count = 10 - me->query("wolongsd/number");

        if (me->query("id") == "jack2929296")
        count = 30 - me->query("wolongsd/number");
        
        if ((count - number) < 0)
            return notify_fail("你今天扫荡卧龙的不够" + number + "次了。\n");

        if (type == "yb")
        {
            if (me->query("yuanbao") < number * 20)
                return notify_fail("你的元宝不足。\n");

            me->add("yuanbao", -20 * number);
        }

        if (type == "tb")
        {
            if (me->query("yuan_bao") < number * 20)
                return notify_fail("你的通宝不足。\n");

            me->add("yuan_bao", -20 * number);
        }

        ling->add_amount(-number);
        sd(me, number);
        me->set("wolongsd/time", time());
    }

    return 1;
}

int sd(object me, int number)
{
    int exp;

    for (int i = 0; i < number; i++)
    {
        exp = 170 * me->query_skill("force", 1);

        me->add("combat_exp", exp);
        me->add("wolongsd/number",1);

        tell_object(me, sprintf("你扫荡卧龙堡获得了%d点经验。\n",exp));
    }

    return 1;
}