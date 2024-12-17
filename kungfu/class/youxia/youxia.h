string xue_skill()
{
    object me;
    int good;

    me = this_player();
    good = me->query("youxia/" + query("id") + "/good");

    if (good < 40000)
    {
        return "知己难寻,你未合我心,心意不达如何修我绝学？\n";
    }

    if (me->query_skill(query("xue_skill")))
    {
        return "你我心意相通,明知我意,为何不知修武需加以自我领悟,我以为你寻路,切勿过于借助外力,长路漫漫,修武心不诚如何站在顶峰。\n";
    }

    me->set_skill(query("xue_skill"),10);

    return "人生几何,难遇知己,我自悟一套绝学,今日便传于你吧,如你有朝一日此功大成,知我大道,与我在月下浮一大白,许能明我所学之奥妙\n";

}

int accept_object(object who, object ob)
{
    int good,potential,amount;
    string *drink_msg = ({ "今日喝的真是痛快啊！","如此美景,当浮一大白","於！君对修武的见解真是奥妙无穷,当浮一大白。","嗟哉!君此翻言论当中绝妙！","噫!想江湖上那所谓的宗师之名如雷惯耳,我曾一一与之在泰山之巅坐而论道，昔之所见，大失所望，不及君之道也！"});
    if (!ob->query("youxia"))
    {
        tell_object(who,"这样的东西还是别拿出来了吧,毫无用处。\n");
        return 0;
    }

    if (who->query("youxia/" + query("id") + "/time") / 86400 < time() / 86400)
    {
        who->delete("youxia/" + query("id") + "/today");
    }

    if (who->query("youxia/" + query("id") + "/today") >= 10)
    {
        command("say 今日与君喝的有点乏了，改日再来吧！");
        return 0;
    }

    good = ob->query("youxia/good");
    potential = ob->query("youxia/potential");

    amount = ob->query_amount();

    if ((amount + who->query("youxia/" + query("id") + "/today")) > 10)
    {
        command("say 君可知一日饮如此多酒不利于武道修行，还是适量为好。");
        return 0;
    }

    who->set("youxia/" + query("id") + "/time",time());
    who->add("youxia/" + query("id") + "/today",amount);
    who->add("youxia/" + query("id") + "/good",amount * good);
    who->add("potential",amount * potential);

    tell_object(who,sprintf("你和%s饮了%d杯%s，谈古论今，交流武道技巧，潜能提升了%d点。\n", query("name"),amount,ob->query("name"),potential * amount));
    command("say " + rand_array(drink_msg));
    who->force_me("say " + rand_array(drink_msg));
    tell_object(who,sprintf("%s对你的好感度提升了%d点。\n",query("name"),amount * ob->query("youxia/good")));
	return 1;
}