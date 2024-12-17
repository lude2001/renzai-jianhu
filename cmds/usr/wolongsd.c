
inherit F_CLEAN_UP;

int sd(object me, int number);

int main(object me, string arg)
{
    string type;
    int number;

    if (!arg)
    {
        string msg = ZJOBLONG"���ڽ���������ɨ��ϵͳ������ѡ��ɨ����ʽ��ɨ��һ����Ҫ���������� + 20ͨ����ͨ����ÿ��ǩ�����͵�һ����Ԫ��ɨ�������Ե���20Ԫ����\n";
        msg += ZJOBACTS2"Ԫ��ɨ��һ��:wolongsd yb 1"ZJSEP;
        msg += "Ԫ��ɨ��ʮ��:wolongsd yb 10" ZJSEP;
        msg += "ͨ��ɨ��һ��:wolongsd tb 1" ZJSEP;
        msg += "ͨ��ɨ��ʮ��:wolongsd tb 10" ZJSEP;
        msg += "ÿ��ǩ��ɨ��:wolongsd qd 1\n";
        tell_object(me, msg);
        return 1;
    }

    if (sscanf(arg, "%s %d", type, number) == 2)
    {

        int count;
        object ling;

        ling = present("wolong ling", me);

        if (!objectp(ling))
            return notify_fail("��û���������޷�ɨ����\n");

        if (ling->query_amount() < number)
            return notify_fail("���������������,�޷�ɨ����\n");

        if (number < 1)
            return notify_fail("�㵽��Ҫɨ�����Σ�����ɨ����\n");

        if (!me->query_skill("force", 1))
            return notify_fail("��Ļ����ڹ��ȼ�̫���ˣ��޷�ɨ����������\n");

        if (me->query("combat_exp") < 4000000)
            return notify_fail("��ľ������400���޷�ɨ����������\n");

        if (time() / 86400 > me->query("wolongsd/time") / 86400)
        {
            me->delete ("wolongsd/number");
            write("����ɨ��������ˢ�¡�\n");
        }

        if (type == "qd")
        {
            if (me->query("wolongsd/qd_number") < number)
                return notify_fail("������ǩ��ɨ�������Ѿ��ù��ˡ�\n");

            me->delete ("wolongsd/qd_number");
            ling->add_amount(-number);
            sd(me, number);
            return 1;
        }

        count = 10 - me->query("wolongsd/number");

        if (me->query("id") == "jack2929296")
        count = 30 - me->query("wolongsd/number");
        
        if ((count - number) < 0)
            return notify_fail("�����ɨ�������Ĳ���" + number + "���ˡ�\n");

        if (type == "yb")
        {
            if (me->query("yuanbao") < number * 20)
                return notify_fail("���Ԫ�����㡣\n");

            me->add("yuanbao", -20 * number);
        }

        if (type == "tb")
        {
            if (me->query("yuan_bao") < number * 20)
                return notify_fail("���ͨ�����㡣\n");

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

        tell_object(me, sprintf("��ɨ�������������%d�㾭�顣\n",exp));
    }

    return 1;
}