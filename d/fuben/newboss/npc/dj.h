//代码尽量符合五大开发原则，不然非常乱
// by 猫猫
// void init()
// {
//     add_action("disable", ({ "kill"}));
// }

// int disable(string arg)
// {
//     object who = this_player();
    

//     if (arg != this_object()->query("id"))
//     return 0;

//     if (who->query_temp("daojian_fuben/state") == this_object()->query("boss"))
//     {
//     tell_object(who, this_object()->query("name") + "瞪了你一眼,道:你在搞什么鬼，你到底是那一边的！\n");
//     return 1;
//     }

//     // who->force_("kill" + arg);
//     return 0;
// }

void heart_beat()
{	
    object me = this_object();
    object *obs = me->query_enemy();
    if (!obs || !sizeof(obs))
    return;

    if (me->query("qi") < 10000)
    {
        me->die();
        return;
    }

    me->add("xztime",2);

    if (me->query("xztime") >= 1800)
    {
        object opponent;
        string targetId;
    
        if (me->query("id") == "hu yidao")
        targetId = "miao renfeng";
        else
        targetId = "hu yidao";
    
        opponent = present(targetId, environment(this_object()));
    
        if (!objectp(opponent) || userp(opponent))
        return;

        //如果me的气血比对手少，me先死
        if (me->query("qi") < opponent->query("qi"))
        {
            me->die();
            return;
        }
    }

    if (this_object()->is_fighting())
    {
        foreach (object ob in obs)
        {
            //只对玩家进行
            if (!userp(ob) || environment(ob) != environment(me))
            {
                continue;
            }
            
            //奶妈造成的恢复量应当计入伤害总值
            if (ob->query_temp("huifu"))
            {
                me->add("djboss/" + ob->query("id"), ob->query_temp("huifu"));
                me->add("all_recive_damage", ob->query_temp("huifu"));
                
                //计算后清除记录的恢复量
                ob->delete_temp("huifu");
            }
            
            tell_object(ob,sprintf(HIG"只见%s两个眼瞳一闪,分别化为刀剑的形态,施展出刀剑归真"NOR"。\n",me->query("name")));
            if (random(5) == 1)
            {
                tell_object(ob,"你被第一道真气击中,损失500点气血。\n");
                me->receive_curing("qi",5000);
                me->receive_heal("qi",1500);
                ob->receive_damage("qi", 500, me);
                ob->receive_wound("qi", 500, me);
                tell_object(ob,sprintf("你的气血被%s吸收。\n",me->query("name")));
            }

            if (random(10) == 1)
            {
                tell_object(ob,"你被第二道真气击中,损失1000点气血。\n");
                me->receive_curing("qi",8000);
                me->receive_heal("qi",2000);
                ob->receive_damage("qi", 1000, me);
                ob->receive_wound("qi", 1000, me);
                tell_object(ob,sprintf("你的气血被%s吸收。\n",me->query("name")));
            }

            if (random(20) == 1)
            {
                tell_object(ob,"你被第三道真气击中,损失1000点气血。\n");
                me->receive_curing("qi",8000);
                me->receive_heal("qi",3000);
                ob->receive_damage("qi", 1000, me);
                ob->receive_wound("qi", 1000, me);
                tell_object(ob,sprintf("你的气血被%s吸收。\n",me->query("name")));
            }

            if (random(25) == 1)
            {
                tell_object(ob,"你被第四道真气击中,损失3000点气血。\n");
                me->receive_curing("qi",20000);
                me->receive_heal("qi",4000);
                ob->receive_damage("qi", 3000, me);
                ob->receive_wound("qi", 3000, me);
                tell_object(ob,sprintf("你的气血被%s吸收。\n",me->query("name")));
            }

            

        }


    }
}

varargs int receive_damage(string type, int damage, mixed who)
{
    object me = this_object();

    //开始统计伤害 Start counting damage
    if (objectp(who))
    {
        if (random(20) == 1)
        {
            tell_object(who,sprintf(HIG"只见%s两个双手互博,手握刀剑,施展出刀剑归真的极意，将你的伤害回弹了"NOR"。\n",me->query("name")));
            who->receive_damage("qi", damage / 2, me);
            who->receive_wound("qi", damage / 2, me);
            return;
        }

        me->add("djboss/" + who->query("id"), damage);
        me->add("all_recive_damage", damage);
    }

    return ::receive_damage(type, damage, who);
}

// A way to reward the player 给予玩家奖励的接口
// me 接受奖励的玩家对象
// allDamage boss受到的所有伤害
// playerDamage 接受奖励的玩家对boos造成的伤害
// allPlayerNumber 所有对boss造成过伤害的玩家,用于统计百分比
// state 1代表正常奖励 0代表奖励削弱
int reward_player(object me, int playerDamage, int allPlayerNumber, int state)
{
    //把总伤害分成等份(有几个玩家就有几份)
    //一份奖励的基数为10000
    //最大基数不能超过40000

    int damagePercentage, baseRewardPercentage, allReward, allDamage; //用于计算初等的比例
    int potentialReward, expReward;

    //无法用英文解释的变量特别注释
    object putao, chongmaidan;

    //代码分离--系统块
    if (!objectp(me))
        return 1;

    allDamage = this_object()->query("all_recive_damage");
    baseRewardPercentage = 10000;
    allReward = baseRewardPercentage * baseRewardPercentage;
    damagePercentage = playerDamage / (allDamage / allPlayerNumber); //忽略余数

    //代码分离--玩家块
    potentialReward = baseRewardPercentage * damagePercentage;
    expReward = baseRewardPercentage * damagePercentage * 5 / 2; //经验是基数的2.5倍

    putao = new_bind("/clone/vip/putao1");
    chongmaidan = new_bind("/clone/vip/dan_chongmai1");
    chongmaidan->set_amount(10);

    if (random(1000) == 1)
    {
        me->add("gem_duihuan",1);
        tell_object(me,"你可真是个欧皇,获得了1张宝石兑换卷\n");
    }


    if (expReward > 150000)
    expReward = 150000;
    
    if (potentialReward > 80000)
    potentialReward  = 80000;
    
    if (!state)
    {
    expReward /= 2;
    potentialReward /= 2;
    }
    
    if (expReward < 10000)
    expReward = 10000;
    
    
    me->add("combat_exp", expReward);
    me->add("potential", potentialReward);
    me->add("weiwang",potentialReward / 4);
    putao->move(me);
    chongmaidan->move(me);
    tell_object(me, sprintf("你在本次战争中获得了%d经验,%d潜能,%d威望,一串神奇葡萄,十颗下品冲脉丹。\n", expReward, potentialReward,potentialReward / 4));
}

int sort_damage(string a, string b)
{
    return this_object()->query("djboss/" + a) - this_object()->query("djboss/" + b);
}

//用于处理胜利
int dispose_win()
{
    object opponent;
    string targetId;

    if (this_object()->query("id") == "hu yidao")
    targetId = "miao renfeng";
    else
    targetId = "hu yidao";

    opponent = present(targetId, environment(this_object()));

    if (!objectp(opponent) || userp(opponent))
    return 1;

    opponent->dispose_players(0);
    destruct(opponent);
    return 1;
}

//单独写一个玩家处理接口
int dispose_players(int state)
{
    int playerNumber, i;
    object ob;
    mapping boss;
    mixed *killer, killerDamageList;


    if (!this_object()->query("djboss"))
    {
        destruct(this_object());
        return 1;
    }   
    //伤害统计
    killer = sort_array(keys(boss = this_object()->query("djboss")),(:sort_damage:));

    if (!sizeof(killer))
    {
        destruct(this_object());
        return 1;
    }   

    //统计一下玩家数量
    playerNumber = sizeof(killer);
    for (i = 0; i < sizeof(killer); i++)
    {
        if (objectp(ob = find_player(killer[i])))
        {
            int playerPot, playerExp;
            int topten, probability;
            topten = i + 1; //下标+1就是排名

            //必须是敌方阵容才才能获得奖励
            if (!ob->query_temp("daojian_fuben/state") || ob->query_temp("daojian_fuben/state") == this_object()->query("boss"))
            continue;

            if (playerNumber >= 10 && topten < playerNumber / 2)
            {
                foreach (probability in ({ 50,60,70,80,90 }))
                {
                    if (topten < playerNumber * probability / 100)
                        break;
                }

            }
            else if (playerNumber <= 5 && topten <= 5)
            {
                probability = 90 - i * 10;
            }

            if (generate_probability(probability))
            {
               object jiuzhuan;
               
               jiuzhuan = new_bind("/clone/vip/dan_jiuzhuan");
               jiuzhuan->move(ob);
               command("chat " + ob->short() + "竟抢走了老夫的九转金丹！");
               tell_object(ob,"你可真是欧皇，获得了一枚九转金丹。\n");
            }

            reward_player(ob, boss[killer[i]], playerNumber, state);
            message_vision("$N累计对boss造成" + boss[killer[i]] + "点伤害。\n", ob);
            log_file("boss_daojian", sprintf("%s：对boss造成 %d      点伤害，ID=" + ob->query("id") + "。\n", ctime(time()), boss[killer[i]]));
        }
    }
}
void die()
{
    object ob;
    string msg;
    int expi, poti, weiwangi, scorei;
    int i;

    if (!objectp(ob = query_last_damage_from()))
        return;

    msg = "我居然败了,怎会如此...可惜了.....";

    command("chat " + msg);
    CHANNEL_D->do_channel(this_object(), "rumor", "听说" + ob->name() + "给予了" + name() + "致命一击，埋葬了这位武道大宗师不屈的意志。");

    //最后一击，给予10000到20000的经验，以及1000-2000的威望，1000的江湖阅历
    expi = random(10000) + 10000;
    poti = random(10000) + 10000;
    weiwangi = random(1000) + 10;
    scorei = random(1000) + 10;

    ob->add("combat_exp", expi);
    ob->add("potential", poti);
    ob->add("weiwang", weiwangi);
    ob->add("score", scorei);

    tell_object(ob, sprintf(HIG "你获得了%s点经验、%s点潜能，并增加了%s点威望、%s点江湖阅历。" NOR "\n",
                            chinese_number(expi), chinese_number(poti),
                            chinese_number(weiwangi), chinese_number(scorei)));

    dispose_win();                        
    dispose_players(1);

    ::die(ob);
    //call_out("destruct", 0, this_object());
}