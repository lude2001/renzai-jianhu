//���뾡��������󿪷�ԭ�򣬲�Ȼ�ǳ���
// by èè
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
//     tell_object(who, this_object()->query("name") + "������һ��,��:���ڸ�ʲô���㵽������һ�ߵģ�\n");
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

        //���me����Ѫ�ȶ����٣�me����
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
            //ֻ����ҽ���
            if (!userp(ob) || environment(ob) != environment(me))
            {
                continue;
            }
            
            //������ɵĻָ���Ӧ�������˺���ֵ
            if (ob->query_temp("huifu"))
            {
                me->add("djboss/" + ob->query("id"), ob->query_temp("huifu"));
                me->add("all_recive_damage", ob->query_temp("huifu"));
                
                //����������¼�Ļָ���
                ob->delete_temp("huifu");
            }
            
            tell_object(ob,sprintf(HIG"ֻ��%s������ͫһ��,�ֱ�Ϊ��������̬,ʩչ����������"NOR"��\n",me->query("name")));
            if (random(5) == 1)
            {
                tell_object(ob,"�㱻��һ����������,��ʧ500����Ѫ��\n");
                me->receive_curing("qi",5000);
                me->receive_heal("qi",1500);
                ob->receive_damage("qi", 500, me);
                ob->receive_wound("qi", 500, me);
                tell_object(ob,sprintf("�����Ѫ��%s���ա�\n",me->query("name")));
            }

            if (random(10) == 1)
            {
                tell_object(ob,"�㱻�ڶ�����������,��ʧ1000����Ѫ��\n");
                me->receive_curing("qi",8000);
                me->receive_heal("qi",2000);
                ob->receive_damage("qi", 1000, me);
                ob->receive_wound("qi", 1000, me);
                tell_object(ob,sprintf("�����Ѫ��%s���ա�\n",me->query("name")));
            }

            if (random(20) == 1)
            {
                tell_object(ob,"�㱻��������������,��ʧ1000����Ѫ��\n");
                me->receive_curing("qi",8000);
                me->receive_heal("qi",3000);
                ob->receive_damage("qi", 1000, me);
                ob->receive_wound("qi", 1000, me);
                tell_object(ob,sprintf("�����Ѫ��%s���ա�\n",me->query("name")));
            }

            if (random(25) == 1)
            {
                tell_object(ob,"�㱻���ĵ���������,��ʧ3000����Ѫ��\n");
                me->receive_curing("qi",20000);
                me->receive_heal("qi",4000);
                ob->receive_damage("qi", 3000, me);
                ob->receive_wound("qi", 3000, me);
                tell_object(ob,sprintf("�����Ѫ��%s���ա�\n",me->query("name")));
            }

            

        }


    }
}

varargs int receive_damage(string type, int damage, mixed who)
{
    object me = this_object();

    //��ʼͳ���˺� Start counting damage
    if (objectp(who))
    {
        if (random(20) == 1)
        {
            tell_object(who,sprintf(HIG"ֻ��%s����˫�ֻ���,���յ���,ʩչ����������ļ��⣬������˺��ص���"NOR"��\n",me->query("name")));
            who->receive_damage("qi", damage / 2, me);
            who->receive_wound("qi", damage / 2, me);
            return;
        }

        me->add("djboss/" + who->query("id"), damage);
        me->add("all_recive_damage", damage);
    }

    return ::receive_damage(type, damage, who);
}

// A way to reward the player ������ҽ����Ľӿ�
// me ���ܽ�������Ҷ���
// allDamage boss�ܵ��������˺�
// playerDamage ���ܽ�������Ҷ�boos��ɵ��˺�
// allPlayerNumber ���ж�boss��ɹ��˺������,����ͳ�ưٷֱ�
// state 1������������ 0����������
int reward_player(object me, int playerDamage, int allPlayerNumber, int state)
{
    //�����˺��ֳɵȷ�(�м�����Ҿ��м���)
    //һ�ݽ����Ļ���Ϊ10000
    //���������ܳ���40000

    int damagePercentage, baseRewardPercentage, allReward, allDamage; //���ڼ�����ȵı���
    int potentialReward, expReward;

    //�޷���Ӣ�Ľ��͵ı����ر�ע��
    object putao, chongmaidan;

    //�������--ϵͳ��
    if (!objectp(me))
        return 1;

    allDamage = this_object()->query("all_recive_damage");
    baseRewardPercentage = 10000;
    allReward = baseRewardPercentage * baseRewardPercentage;
    damagePercentage = playerDamage / (allDamage / allPlayerNumber); //��������

    //�������--��ҿ�
    potentialReward = baseRewardPercentage * damagePercentage;
    expReward = baseRewardPercentage * damagePercentage * 5 / 2; //�����ǻ�����2.5��

    putao = new_bind("/clone/vip/putao1");
    chongmaidan = new_bind("/clone/vip/dan_chongmai1");
    chongmaidan->set_amount(10);

    if (random(1000) == 1)
    {
        me->add("gem_duihuan",1);
        tell_object(me,"������Ǹ�ŷ��,�����1�ű�ʯ�һ���\n");
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
    tell_object(me, sprintf("���ڱ���ս���л����%d����,%dǱ��,%d����,һ����������,ʮ����Ʒ��������\n", expReward, potentialReward,potentialReward / 4));
}

int sort_damage(string a, string b)
{
    return this_object()->query("djboss/" + a) - this_object()->query("djboss/" + b);
}

//���ڴ���ʤ��
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

//����дһ����Ҵ���ӿ�
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
    //�˺�ͳ��
    killer = sort_array(keys(boss = this_object()->query("djboss")),(:sort_damage:));

    if (!sizeof(killer))
    {
        destruct(this_object());
        return 1;
    }   

    //ͳ��һ���������
    playerNumber = sizeof(killer);
    for (i = 0; i < sizeof(killer); i++)
    {
        if (objectp(ob = find_player(killer[i])))
        {
            int playerPot, playerExp;
            int topten, probability;
            topten = i + 1; //�±�+1��������

            //�����ǵз����ݲŲ��ܻ�ý���
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
               command("chat " + ob->short() + "���������Ϸ�ľ�ת�𵤣�");
               tell_object(ob,"�������ŷ�ʣ������һö��ת�𵤡�\n");
            }

            reward_player(ob, boss[killer[i]], playerNumber, state);
            message_vision("$N�ۼƶ�boss���" + boss[killer[i]] + "���˺���\n", ob);
            log_file("boss_daojian", sprintf("%s����boss��� %d      ���˺���ID=" + ob->query("id") + "��\n", ctime(time()), boss[killer[i]]));
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

    msg = "�Ҿ�Ȼ����,�������...��ϧ��.....";

    command("chat " + msg);
    CHANNEL_D->do_channel(this_object(), "rumor", "��˵" + ob->name() + "������" + name() + "����һ������������λ�������ʦ��������־��");

    //���һ��������10000��20000�ľ��飬�Լ�1000-2000��������1000�Ľ�������
    expi = random(10000) + 10000;
    poti = random(10000) + 10000;
    weiwangi = random(1000) + 10;
    scorei = random(1000) + 10;

    ob->add("combat_exp", expi);
    ob->add("potential", poti);
    ob->add("weiwang", weiwangi);
    ob->add("score", scorei);

    tell_object(ob, sprintf(HIG "������%s�㾭�顢%s��Ǳ�ܣ���������%s��������%s�㽭��������" NOR "\n",
                            chinese_number(expi), chinese_number(poti),
                            chinese_number(weiwangi), chinese_number(scorei)));

    dispose_win();                        
    dispose_players(1);

    ::die(ob);
    //call_out("destruct", 0, this_object());
}