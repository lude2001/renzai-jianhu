inherit ITEM;

void create()
{
	set_name("������", ({"ningqi fu"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("value", 10000);
		set("unit", "��");
		set("no_put", 1);
		set("long","һ�Ż�����ɵ����������о������̲ؾ޴����ܡ�\n");
	}
	set("only_do_effect", 1);
}

int do_effect(string arg)
{
    object * enemys;
    int random;
    int fu_damage;
    object who;
    
    who = this_player();
    
    if (!who->is_fighting())
    {
        write("ֻ��ս���в���ʹ����������\n");
        return 1;
    }
     
     if (who->is_busy())
     {
         write("����æ���޷�ʹ����������\n");
         return 1;
     }
    
    enemys = who->query_enemy();
    fu_damage = query("fu/damage");
    
    if (sizeof(enemys))
    {
        random = random(sizeof(enemys));
        
        if (!living(enemys[random]))
        {
            write("���˶��Ѿ������ˣ��Ͳ���ʹ���������ˡ�\n");
            return 1;
        }
        
        if (who->query("family/family_name") == "�䵱��" || who->query("family/family_name") == "ȫ���")
        {
            enemys[random]->receive_wound("qi", fu_damage, who);
            who->start_busy(6);
            message_combatd(HIW"$Nȡ��һ�Ż����������Ļ�ֽ������������仯����������$n���š�"NOR"\n" + "$n�ܵ�" + fu_damage + "�˺���\n", who, enemys[random]);
        }
        else
        {
            enemys[random]->receive_wound("qi", fu_damage / 2, who);
            who->start_busy(6);
            message_combatd(HIW"$Nȡ��һ�Ż����������Ļ�ֽ������������仯����������$n���š�"NOR"\n" + "$n�ܵ�" + fu_damage / 2 + "�˺���\n", who, enemys[random]);
        }
    }
    else
    {
        write("������û�е���Ŷ��\n");
        return 1;
    }
    
    destruct(this_object());
    return 1;
}