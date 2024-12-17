#include <ansi.h>
inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
	string file;
	string str;
	object ob;
 
	if (! environment(me)) 
		return 0; 

	if (! arg )
		return help(me);
			       
	if (me->is_busy())
		return notify_fail("����æ���ء�\n");

	if (me->is_ghost()) 
		return notify_fail("���㻹������˵�ɡ�\n"); 
		
	if (me->is_in_prison())   
		return notify_fail("�����������ء�\n");

	if (! me->query("born"))
		return notify_fail("�㻹û�г����أ�\n");

	if (me->query("doing"))
		return notify_fail("�㻹���ʲô����\n");
		
	if (environment(me)->query("no_magic"))
		return notify_fail("�㷢�������е�Ź֣�\n");		
	
	if (arg == "back")
	{			
		if (me->query_temp("jun_quest/party"))
			return notify_fail("�㻹����ս����ʹ�ã���\n");

		if (present("biao huo", me))
			return notify_fail("�����ϴ�������������ʩչ��\n");
		
		if (present("letter", me) || present("receipt", me)) 
			return notify_fail("�����ϴ����ܺ�������ʩչ��\n");
		
		file = "/d/city/kedian";
		
		if (base_name(environment(me)) == file)
			return notify_fail("���Ѿ������ݿ͵��ˡ�\n");
			
		if (! get_object(file))
			return notify_fail("��о����ƺ���ʲô���Ծ���\n");

		message("vision", me->name() + "������������ǰ���ٻ���һ��Բ������������ǰ��"
			"�ռ䣬ֻ��Բ�ڵĿռ���ս�" + me->name() + "�����˽�ȥ��\n",
			environment(me), ({me}));
		
		tell_object(me, "��ӿ͵��ĳ������ռ��ѷ��������\n");

		me->move(file);
		message("vision", me->name() + "�ӿ͵��ĳ������ռ��ѷ��������\n",
			environment(me), ({me}));

		return 1;
	}

     str = me->query_temp("pet_id");      
		     
     if (! stringp(file = me->query("can_whistle/" + str)))
		return notify_fail("�㲢û�����ħ���ޡ�\n");

	if (file_size(file + ".c") < 0)
		return notify_fail("�㲢û�����ħ����!\n");
				
	if (arg == "change" && ! me->query("beastdied"))
	{
		if (! objectp(ob = present(str, environment(me))))
			return notify_fail("������Ȱ����ħ�����ٻ�����������\n");
		
		if (ob->query("owner") != me->query("id"))
			return notify_fail("���ħ���޲�����������ԡ�\n");
				
		if (! living(ob)) return notify_fail("���ħ����Ŀǰ���ڻ���״̬�ء�\n");

		message_vision("$N������������ǰ���ٻ���һ��Բ����"
			"һ������$n����������\n", me, ob);
		
		if (! ob->receive_change(me))
		{
			message_vision("Ȼ��ʲôҲû�з��� :)\n", me);			
			return 1;
		} 
	} else
	if (arg == "recover" && ! me->query("beastdied"))
	{
		 if (! objectp(ob = present(str, me)))
			return notify_fail("�����ϲ�û���κ�������ħ���ޡ�\n");
				       
		if (ob != me->query_temp("is_changing"))
			return notify_fail("�����ϲ�û���κ�������ħ���ޡ�\n");  

		if (ob->query("owner") != me->query("id"))
			return notify_fail("�����ϲ�û���κ�������ħ���ޡ�\n");
					
		if (! living(ob)) return notify_fail("���ħ����Ŀǰ���ڻ���״̬�ء�\n");

		message_vision("$N�������ǣ������������ĺ�������$n�������������\n", me, ob);
		
		if (! ob->receive_recover(me))
		{
			message_vision("Ȼ��ʲôҲû�з��� :)\n", me);			
			return 1;
		}		  
	}
	/* 
	else
	if (arg == "reborn" && me->query("beastdied"))
	{
		if (me->query_skill("huisheng-jue", 1) < 100)
			return notify_fail("��Ļ����������������޷���ħ����������\n"); 

		if (me->query("neili") < me->query("max_neili") * 9 / 10)
			return notify_fail("�����������������棬����óȻ���ã�\n");

		if (me->query("jingli") < me->query("max_jingli") * 9 / 10)
			return notify_fail("�����ھ������ã�����óȻ���ã�\n");

		if (me->query_skill("force") < 200)
			return notify_fail("����ڹ�����������ʵ������óȻ���á�\n");

		if (me->query("max_neili") < 3000)
			return notify_fail("�㳢������һ���������޷�˳"
				   "������һ�����죬����ʩչ���������\n");

		if (me->query("max_jingli") < 1000)
			return notify_fail("����ͼ�������þ��������Ǹо�����Ƿȱ��\n");				
		
		if (me->query("experience") < me->query("learned_experience") + 1000) 
			return notify_fail("�����ڻ��۵�ʵս��ỹ̫�٣��޷�óȻ���á�\n");

		message_sort(HIR "$N���о�����ָ��أ�ͬʱ��ת������������"
			"���澭����ԴԴ������������ע���ء�"NOR"\n", me); 

		me->start_busy(1);
	
		me->add("max_neili", -500);
		me->set("neili", (int)me->query("max_neili"));
		me->add("max_jingli", -300);
		me->set("jingli", (int)me->query("max_jingli"));	
		me->add("learned_experience", 1000);
		me->delete("beastdied");
		tell_object(me, HIW "������Ƭ�̣�����ħ����"
			HIW "�ƺ�������������ڲ�Զ��������΢΢һЦ��"NOR"\n");									     
		
	} 
	*/
	else return help(me);
	return 1;
}

int help(object me)
{
 write(@HELP
ָ���ʽ : recall change|recover <id>
��ħ��������������������ħ���޸����ָ��Ϊ< recall reborn >
�ص����ݿ͵��ָ��Ϊ < recall back >��
HELP
    );
    return 1;
}
