// sserver.c

// This function selects a random target for offensive spells/functions.
object offensive_target(object me)
{
  me->clean_up_enemy();
  return me->select_opponent();
}

//1代表经历过这次意境领悟
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
//这个函数用来处理技能cd
int skill_cd(object me, string pfm_name, int cd)
{

  if (!objectp(me))
    return 1;
  me->set_temp("skillcd/" + pfm_name, time() + cd);
  tell_object(me, pfm_name + "技能进入" + cd + "秒冷却，请稍后再使用。\n");
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
    tell_object(me,"你的丹田被封闭" + number + "秒，期间无法使用技能。\n");
    
    return 1;
}

//用于计算相同类型的意境的数量
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