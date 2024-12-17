// sserver.c

// This function selects a random target for offensive spells/functions.
object offensive_target(object me)
{
  me->clean_up_enemy();
  return me->select_opponent();
}

//1������������⾳����
int lv_fa(object me,string family_name)
{
    if (!me->query("yijing"))
    return 0;
    
    foreach (string name in keys(me->query("yijing")))
    {
        if (me->query("yijing/" + name + "/family/family_name") == family_name)
        return 1;
    }
    return 0;
}
//�����������������cd
int skill_cd(object me, string pfm_name, int cd)
{

  if (!objectp(me))
    return 1;
  me->set_temp("skillcd/" + pfm_name, time() + cd);
  tell_object(me, pfm_name + "���ܽ���" + cd + "����ȴ�����Ժ���ʹ�á�\n");
  call_out("remove_skill_cd", cd, me, pfm_name);
  
  return cd;
}

int remove_skill_cd(object me, string pfm_name)
{

  if (!objectp(me))
    return 1;
  me->delete_temp("skillcd/" + pfm_name);
  return 1;
}

int skill_jing(object me,int number)
{
    if (!objectp(me))
    return 1;
    
    me->set_temp("skill_jing",time() + number);
    tell_object(me,"��ĵ��ﱻ���" + number + "�룬�ڼ��޷�ʹ�ü��ܡ�\n");
    
    return 1;
}

//���ڼ�����ͬ���͵��⾳������
int same_yijing_number(object me, string type)
{
	string *yijingList;
	int number = 0;

	if (!me->query("yijing_list"))
		return 0;

	yijingList = keys(me->query("yijing_list"));

	foreach (string yijingName in yijingList)
	{
		if (me->query("yijing/" + yijingName + "/type"))
		{
			number++;
		}
	}

	return number;
}