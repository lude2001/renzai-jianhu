string xue_skill()
{
    object me;
    int good;

    me = this_player();
    good = me->query("youxia/" + query("id") + "/good");

    if (good < 40000)
    {
        return "֪����Ѱ,��δ������,���ⲻ��������Ҿ�ѧ��\n";
    }

    if (me->query_skill(query("xue_skill")))
    {
        return "����������ͨ,��֪����,Ϊ�β�֪�����������������,����Ϊ��Ѱ·,������ڽ�������,��·����,�����Ĳ������վ�ڶ��塣\n";
    }

    me->set_skill(query("xue_skill"),10);

    return "��������,����֪��,������һ�׾�ѧ,���ձ㴫�����,�����г�һ�մ˹����,֪�Ҵ��,���������¸�һ���,����������ѧ֮����\n";

}

int accept_object(object who, object ob)
{
    int good,potential,amount;
    string *drink_msg = ({ "���պȵ�����ʹ�찡��","�������,����һ���","춣���������ļ������ǰ�������,����һ��ס�","���!���˷����۵��о��","��!�뽭��������ν����ʦ֮�����׹߶�,����һһ��֮��̩ɽ֮�������۵�����֮��������ʧ������������֮��Ҳ��"});
    if (!ob->query("youxia"))
    {
        tell_object(who,"�����Ķ������Ǳ��ó����˰�,�����ô���\n");
        return 0;
    }

    if (who->query("youxia/" + query("id") + "/time") / 86400 < time() / 86400)
    {
        who->delete("youxia/" + query("id") + "/today");
    }

    if (who->query("youxia/" + query("id") + "/today") >= 10)
    {
        command("say ��������ȵ��е㷦�ˣ����������ɣ�");
        return 0;
    }

    good = ob->query("youxia/good");
    potential = ob->query("youxia/potential");

    amount = ob->query_amount();

    if ((amount + who->query("youxia/" + query("id") + "/today")) > 10)
    {
        command("say ����֪һ������˶�Ʋ�����������У���������Ϊ�á�");
        return 0;
    }

    who->set("youxia/" + query("id") + "/time",time());
    who->add("youxia/" + query("id") + "/today",amount);
    who->add("youxia/" + query("id") + "/good",amount * good);
    who->add("potential",amount * potential);

    tell_object(who,sprintf("���%s����%d��%s��̸���۽񣬽���������ɣ�Ǳ��������%d�㡣\n", query("name"),amount,ob->query("name"),potential * amount));
    command("say " + rand_array(drink_msg));
    who->force_me("say " + rand_array(drink_msg));
    tell_object(who,sprintf("%s����ĺøж�������%d�㡣\n",query("name"),amount * ob->query("youxia/good")));
	return 1;
}