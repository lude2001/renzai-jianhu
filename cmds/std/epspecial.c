// ���츳˵�����
/*
����˵��
myspecial/�츳id/level �츳�ȼ�
myspecial/�츳id/experience �츳����

����ʹ��Ǳ�������츳����
ÿһ��Ǳ���û�һ�㾭��
*/
#include <ansi.h>

inherit F_CLEAN_UP;


void create() { seteuid(getuid()); }

int main(object me, string arg)
{
   string msg,talent;
   int exp;
   
	if (! arg) return notify_fail("��Ҫ�鿴ʲô�츳��\n");

  if (sscanf(arg,"%s %s %d",msg,talent,exp)==3&&msg=="add")
  {
    int pot = ((int)me->query("potential") - (int)me->query("learned_points"));

    if (pot < 10000*exp)
    return notify_fail(popup("���Ǳ�����ò�Ʋ����������츳��"));
    
    if (exp <= 0)
    return notify_fail(popup("�����0���������ɶ��"));


    me->add("myspecial/"+talent+"/experience",exp);
    me->add("potential",-10000*exp);

    return notify_fail(popup("����ɹ����۳�Ǳ��"+10000*exp));
  }

	if (sscanf(arg,"%s %s",msg,talent)==2&&msg=="add")
  {
    int pot = ((int)me->query("potential") - (int)me->query("learned_points"));

    if (!me->query("special_skill/"+talent))
    return notify_fail(popup("�㻹û������츳�أ�"));

    if (pot < 10000)
    return notify_fail(popup("���Ǳ�����ò�Ʋ����������츳��"));

    return notify_fail(popup_input(sprintf("��Ŀǰ��%d��Ǳ�ܣ���������%d���츳����",pot,pot/10000),"epspecial add "+talent+" "));
  }

 
  	if(sscanf(arg, "%s %s", msg,talent)==2&&msg=="rise")
  	{
  	int next_level,experience;
  	
  	next_level = me->query("myspecial/"+talent+"/level")+1;
  	experience = me->query("myspecial/"+talent+"/experience");
  	
    if (experience <= 100*next_level*next_level)
    return notify_fail("����츳���鲻�㣬��������\n");
     
     me->add("myspecial/"+talent+"/level",1);
     me->add("myspecial/"+talent+"/experience",-100*next_level*next_level);
    
    return notify_fail("��ϲ������츳���׳ɹ���\n");
  	}
  	
	msg = ZJOBLONG;
    msg += "�츳���ƣ�"+SPECIAL_D(arg)->name()+ZJBR;
    msg += "�츳���ܣ�"+SPECIAL_D(arg)->explain()+ZJBR;
    msg += "�츳�ȼ���"+me->query("myspecial/"+arg+"/level")+ZJBR;
    msg += "�츳���飺"+me->query("myspecial/"+arg+"/experience")+ZJBR;
    msg += HIC "��" HIY "һһһһһһһһһһһһһһһһһһһһ" HIC "��"NOR"\n";
    msg +=ZJOBACTS2+ZJMENUF(2,2,10,25);
    msg += "ʹ��:special "+arg+ZJSEP;
    msg += "����:epspecial add "+ arg + ZJSEP;
    msg += "����:epspecial rise "+arg;
    write(msg+"\n");
    return 1;
}
	



int help(object me)
{
	write(@HELP
ָ���ʽ : ride | qi <������>
 
���ָ������������ϴ�������ѱ���Ķ��
 
HELP
    );
    return 1;
}
