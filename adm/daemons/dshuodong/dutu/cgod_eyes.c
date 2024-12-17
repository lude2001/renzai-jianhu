inherit COMBINED_ITEM;

string query_autoload() { return query_amount() + ""; }

void autoload(string param)
{
	int amt;

	if (sscanf(param, "%d", amt) == 1)
		set_amount(amt);
}

void create()
{
	set_name(HIW"�ϵ�֮����Ƭ"NOR, ({"suipian"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("base_unit", "��");
		set("base_weight", 1);
        set("no_sell",1);
        set("no_give",1);
        set("no_drop",1);
        //set("no_get",1);
		set("base_value", 80000);
		set("long","�ϵ�֮����Ƭ�����������ϳ��ϵ�֮�ۡ�\n");
        set("only_do_effect", 1);
	}
	set_amount(1);
	setup();
}

int do_effect(object me)
{
    object ob;
    
	if(query_amount() < 100)
	{
		tell_object(me, "�����Ƭ��������Ŷ���Ͻ�����ռ��ɣ�\n");
		return 1;
	}
	else if (me->query("max_neili") < 500)
	{
	    write("�����������500���޷��ϳɡ�\n");
	    return 1;
	}
	else if(random(2))
	{	
		ob = new("/clone/baoshi/god_eyes");
		if (objectp(ob))
		    ob->move(me);
		else
		{
		    write("��������ϵ����Ա����\n");
		    return 1;
		}
		me->add("max_neili", -500);
		tell_object(me, "�㽫��Ƭƴ�ճ��ϵ�֮�۵���״��ע����������Ƭ����΢�⣬��Ƭ�����ں���һ��\n");
		add_amount(-100);
		return 1;
	}
	
    me->add("max_neili", -500);
	tell_object(me, "������Ƭ��ע����������ϧ�ϳ�ʧ�ܣ���Ƭ�������ӫ����ɢ�ڿ��С�\n");
	add_amount(-100);
	return 1;
}