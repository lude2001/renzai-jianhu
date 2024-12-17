// ����һ����ai������ɵ�lpc����			  
#include <ansi.h>

inherit F_CLEAN_UP;

mapping yj_f_name = (["unarmed":"����", //����ȭ��
						 "cuff":"ȭ��", //����ȭ��
					   "strike":"����", //�����Ʒ�
					   "finger":"ָ��", //����ָ��
						 "hand":"�־�", //�����ַ�
						 "claw":"צ��", //����צ��
						"sword":"����", //��������
						"blade":"����", //��������
						"staff":"�Ⱦ�", //�����ȷ�
					   "hammer":"����", //��������
						 "club":"����", //��������
						 "whip":"����", //�����޷�
					 "throwing":"����"	//��������
]);
int pop_yj(object me,string name);
int use_yj(object me,string name);
object offensive_target(object me);
int modify_attack_description(object me,string name,string newAttackDescription);
int modify_background_description(object me,string name,string newBackgroundDescription);
int modify_expend(object me,string name,int newExpend);
int modify_dodge_description(object me,string name,string newDodgeDescription);
string set_color(string arg);

int main(object me, string arg)
{ 
    string name,option,newModification;
    if (!arg)
    {
        string msg = ZJOBLONG"��ѡ����Ҫ�鿴���⾳��\n";
        msg += ZJOBACTS2;
        
        if (!me->query("yijing"))
        {
            return notify_fail("��Ŀǰû�������κ��⾳��\n");
        }

        foreach (string yjName in keys(me->query("yijing")))
        {
            if (!is_chinese(yjName))
                continue;

            msg += yjName + yj_f_name[me->query("yijing/" + yjName + "/type")] + ":use_yj look " + yjName + ZJSEP;
        }

        msg += "ˢ��:use_yj\n";

        write(msg);
        return 1;

    }

    //�жϴ�һ���ַ���ƥ���ʽ������3���ַ�
    if (sscanf(arg, "%s %s %s", name, option, newModification) == 3)
    {
        //�ж��Ƿ�������⾳
        if (!me->query("yijing/" + name))
        {
            return notify_fail("��û����������⾳��\n");
        }


        //ͳһ����ɫ�趨�ӿ�
        newModification = set_color(newModification);

        //optionΪattackʱ�����޸��⾳���������ĺ�����Ϊdodgeʱ�����޸����������ĺ���,Ϊmsgʱ�����޸��⾳���������ĺ���
        if (option == "attack")
        {
            return modify_attack_description(me, name, newModification);
        }
        else if (option == "dodge")
        {
            return modify_dodge_description(me, name, newModification);
        }
        else if (option == "msg")
        {
            return modify_background_description(me, name, newModification);
        }
        else if (option == "expend")
        {
            return modify_expend(me, name, to_int(newModification));
        }
        else
        {
            return notify_fail("��Ҫ��ʲô��\n");
        }

    }

    if (sscanf(arg,"%s %s",option,name) == 2)
    {
        string msg;

        if (!me->query("yijing/" + name + "/msg"))
        return notify_fail("��û������⾳��\n");

        if (option == "look")
        {
            return pop_yj(me,name);
        }

        if (option == "use")
        {
            return use_yj(me,name);
        }

        //optionΪattack��dodge,msgʹ��INPUTTXT����������µ��޸�
        if (option == "attack")
        {
            msg = "���趨��Ĺ�������,����ʹ����ɫ�ַ������� $HIR$Ϊ��ɫ��$target_name$����з������֣�$my_name$�����Լ������֣�����Ǳ������͵��⾳,$weapon_name$�����Լ����������֡�,Ӣ��б��+n������";
            msg = INPUTTXT(msg, "use_yj " + name + " attack $txt#") + "\n";
            tell_object(me, msg);
            return 1;
        }

        if (option == "dodge")
        {
            msg = "���趨��Ķ�������,����ʹ����ɫ�ַ������� $HIR$Ϊ��ɫ��$target_name$����з������֣�$my_name$�����Լ������֡�,Ӣ��б��+n������";
            msg = INPUTTXT(msg, "use_yj " + name + " dodge $txt#") + "\n";
            tell_object(me, msg);
            return 1;
        }

        if (option == "msg")
        {
            msg = "���趨����⾳��������,����ʹ����ɫ�ַ������� $HIR$Ϊ��ɫ������������趨������Դ��������е���Ϣ��Ӣ��б��+n������";
            msg = INPUTTXT(msg, "use_yj " + name + " msg $txt#") + "\n";
            tell_object(me, msg);
            return 1;
        }

        if (option == "expend")
        {
            msg = "���趨������ĵȼ���6 - 18����Ӧ600-1800���������ģ�6-18���cd���⾳�����Զ������ģ�������cd�����Ÿ����Ĵ��۲�ͬ��������ɵ�Ч����ͬ����Ϊ�������ͣ����У�6 -18���������˺�����Ч�ȼ� *��6 - 18�� / 4�� ����ָ�����Ч�ȼ� * ��6 - 18�� / 8����Ѫ���ٻָ����ֵһ��ľ��񣬼� / 4���� ";
            msg = INPUTTXT(msg, "use_yj " + name + " expend $txt#") + "\n";
            tell_object(me, msg);
            return 1;
        }


    }
	return 1;
}

int use_yj(object me,string name)
{
   
string *weaponType = ({
    "sword",   //��������
    "blade",   //��������
    "staff",   //�����ɷ�
    "hammer",  //��������
    "club",	   //��������
    "whip",	   //�����޷�
});

    object weapon,target;
    string attackDesc,dodgeDesc,targetName;
    int mySkillLevel,targetSkillLevel;
    string skillType,yjSkillType,msg;
    int expend,cd;

    
    if (!me->is_fighting())
    {
        tell_object(me,"ֻ��ս���вſ���ʹ���⾳���ܡ�\n");
        return 1;
    }

    target = offensive_target(me);
    
    expend = me->query("yijing/" + name + "/expend");
    weapon = me->query_temp("weapon");

    skillType = me->query("yijing/" + name + "/type");
    yjSkillType = me->query("yijing/" + name + "/skill");

    mySkillLevel =  me->query_skill(skillType);
    targetSkillLevel = target->query_skill(skillType);

    attackDesc = me->query("yijing/" + name + "/attack_desc");
    dodgeDesc = me->query("yijing/" + name + "/dodge_desc");
    targetName = target->query("name");

    cd = me->query("yijing_use/cd/" + name) - time();


    if (member_array(name,weaponType) != -1 && !weapon)
    {
        if (weapon->query("skill_type") != me->query("yijing/" + name + "/type"))
        {
        tell_object(me,"��û���ֳֶ�Ӧ�ı������ʹ������⾳��\n");
        return 1;
        }
    }

    if (me->query("neili") < expend  * 150)
    {
        tell_object(me,"�����������" + (expend * 150) + ",�޷�ʹ���⾳���ܡ�\n");
        return 1;
    }

    if (cd > 0)
    {
        tell_object(me,sprintf("%s%s�ļ��ܻ���%d�����ȴʱ�䣬�������޷�ʹ�øü��ܡ�\n",name,yj_f_name[skillType],cd));
        return 1;
    }

    if (weapon)
    attackDesc = replace_string(attackDesc,"$weapon_name$",weapon->query("name"));

    attackDesc = replace_string(attackDesc,"$my_name$",me->query("name"));
    attackDesc = replace_string(attackDesc,"$target_name$",targetName);

    if (weapon)
    dodgeDesc = replace_string(dodgeDesc,"$weapon_name$",weapon->query("name"));

    dodgeDesc = replace_string(dodgeDesc,"$my_name$",me->query("name"));
    dodgeDesc = replace_string(dodgeDesc,"$target_name$",targetName);

    attackDesc = replace_string(attackDesc,ZJBR,"\n");
    dodgeDesc = replace_string(dodgeDesc,ZJBR,"\n");

    msg = HIC + me->query("name") + "ȫ���ھ�������ʹ����" + name + yj_f_name[skillType] + NOR"��\n";
    msg += attackDesc + "\n";


    msg += "�ҷ�����ϵ��:" + mySkillLevel + "--\n";
    msg += "�з�����ϵ��:" + targetSkillLevel + "--\n";
    
    if (mySkillLevel / 4 + random(mySkillLevel / 2) > targetSkillLevel / 2)
    {

        if (yjSkillType == "����")
        {
            for (int i = 0; i < expend; i++)
            {
                if (! me->is_fighting(target))
                    break;
                if (random(5) < 2 && ! target->is_busy())
                    target->start_busy(1);
                
                if (!weapon)
                COMBAT_D->do_attack(me, target, 0, 0);
                else
                COMBAT_D->do_attack(me, target, weapon, 0);

                message_vision(msg, me, target);
                return 1;
            }
        }
        else if (yjSkillType == "�����˺�")
        {
            target->receive_damage("qi", mySkillLevel * expend / 3,me);
            target->receive_wound("qi", mySkillLevel * expend / 3,me);
            msg += HIC + targetName + "�ܵ���"HIR + (mySkillLevel * expend / 3) + NOR"����Ѫ���˺���\n";
        }
        else if (yjSkillType == "���лָ�")
        {
            int qixue;
            qixue = mySkillLevel * expend / 4;
            me->receive_curing("qi",qixue);
            me->receive_curing("jing",qixue / 2);
            msg += HIC + me->query("name") + "�ָ���"HIG + (qixue) + NOR"����Ѫ��\n";
            msg += HIC + me->query("name") + "�ָ���"HIG + (qixue / 2) + NOR"�㾫��\n";
        }

    }
    else
    {
        msg += dodgeDesc;
    }

    msg += "\n";

    me->set("yijing_use/cd/" + name,time() + expend);
    me->add("neili",- expend * 150);

    if (environment(me)->query("short") != "��������")
    message_vision(msg, me, target);

    return 1;

}
int pop_yj(object me,string name)
{
    string msg = ZJOBLONG"�⾳����:" + name + "\n";

    msg += "�⾳��������:" + me->query("yijing/" + name + "/msg") + "\n";
    msg += "�⾳��������:" + me->query("yijing/" + name + "/attack_desc") + "\n";
    msg += "�⾳��������:" + me->query("yijing/" + name + "/dodge_desc") + "\n";
    msg += "�⾳���ĵȼ�:" + me->query("yijing/" + name + "/expend") + "\n";
    msg += "��������:" + me->query("yijing/" + name + "/skill") + "\n";
    msg += "�⾳����:" + yj_f_name[me->query("yijing/" + name + "/type")] + "\n";

    msg = replace_string(msg,"\n",ZJBR);
    msg += "--------------\n";
    msg += ZJOBACTS2;
    msg += "�޸ı�������:use_yj msg "+ name +ZJSEP;
    msg += "�޸Ĺ�������:use_yj attack "+ name +ZJSEP;
    msg += "�޸���������:use_yj dodge "+ name +ZJSEP;
    msg += "�޸����ĵȼ�:use_yj expend "+ name + ZJSEP;
    msg += "ʹ��:use_yj use " + name + "\n";

    tell_object(me,msg);
    return 1;
}

object offensive_target(object me)
{
  me->clean_up_enemy();
  return me->select_opponent();
}

//�޸��⾳��������
int modify_attack_description(object me,string name,string newAttackDescription)
{

    //�ж�����Ƿ�������⾳
    if (! me->query("yijing/" + name))
    {
        tell_object(me,"��û������⾳��\n");
        return 1;
    } 

    //�ж��µĹ���������Ҫ��1-200��֮��
    if ((strlen(newAttackDescription) < 2) || (strlen(newAttackDescription) > 400))
    {
        tell_object(me, "�Բ�������⾳������������̫����̫�̣�1-200�֣���\n");
        return 1;
    }

    //�ж��Ƿ�ӵ��200Ԫ��
    if (me->query("yuanbao") < 200)
    {
        tell_object(me,"���Ԫ�����㡣\n");
        return 1;
    }

    //�۳�200Ԫ��
    me->add("yuanbao",-200);


    //�趨�µĹ�������
    me->set("yijing/" + name + "/attack_desc",newAttackDescription);

    //��������޸����
    tell_object(me,"�޸���ɡ�\n");

    //��ʾ����⾳
    pop_yj(me,name);


    return 1;


}


//�޸��⾳��������
int modify_dodge_description(object me,string name,string newDodgeDescription)
{

    //�ж�����Ƿ�������⾳
    if (! me->query("yijing/" + name))
    {
        tell_object(me,"��û������⾳��\n");
        return 1;
    }

    //�ж��µ�����������Ҫ��1-200��֮��
    if ((strlen(newDodgeDescription) < 2) || (strlen(newDodgeDescription) > 400))
    {
        tell_object(me, "�Բ�������⾳������������̫����̫�̣�1-200�֣���\n");
        return 1;
    }

    //�ж��Ƿ�ӵ��200Ԫ��
    if (me->query("yuanbao") < 200)
    {
        tell_object(me,"���Ԫ�����㡣\n");
        return 1;
    }

    //�۳�200Ԫ��

    me->add("yuanbao",-200);

    //�趨�µ���������
    me->set("yijing/" + name + "/dodge_desc",newDodgeDescription);

    //��������޸����
    tell_object(me,"�޸���ɡ�\n");

    //��ʾ����⾳
    pop_yj(me,name);

    return 1;

}

//�޸��⾳��������
int modify_background_description(object me,string name,string newBackgroundDescription)
{

    //�ж�����Ƿ�������⾳
    if (! me->query("yijing/" + name))
    {
        tell_object(me,"��û������⾳��\n");
        return 1;
    }


    //�ж��µı���������Ҫ��1-300��֮��
    if ((strlen(newBackgroundDescription) < 2) || (strlen(newBackgroundDescription) > 600))
    {
        tell_object(me, "�Բ�������⾳������������̫����̫�̣�1-300�֣���\n");
        return 1;
    }

    //�ж��Ƿ�ӵ��200Ԫ��
    if (me->query("yuanbao") < 200)
    {
        tell_object(me,"���Ԫ�����㡣\n");
        return 1;
    }

    //�۳�200Ԫ��
    me->add("yuanbao",-200);

    //�趨�µı�������
    me->set("yijing/" + name + "/msg",newBackgroundDescription);

    //��������޸����
    tell_object(me,"�޸���ɡ�\n");
    
    //��ʾ����⾳
    pop_yj(me,name);

    return 1;

}

//�޸��⾳���ĵȼ�
int modify_expend(object me,string name,int newExpend)
{

    //�ж�����Ƿ�������⾳
    if (! me->query("yijing/" + name))
    {
        tell_object(me,"��û������⾳��\n");
        return 1;
    }

    //�ж��Ƿ�ӵ��200Ԫ��
    if (me->query("yuanbao") < 200)
    {
        tell_object(me,"���Ԫ�����㡣\n");
        return 1;
    }

    //�ж���ҵ��⾳���ĵȼ��Ƿ���6-18֮��
    if (newExpend < 6 || newExpend > 18)
    {
        tell_object(me,"�⾳���ĵȼ�������6-18֮�䡣\n");
        return 1;
    }

    //�۳�200Ԫ��
    me->add("yuanbao",-200);

    //�趨�µ����ĵȼ�
    me->set("yijing/" + name + "/expend",newExpend);

    //��������޸����
    tell_object(me,"�޸���ɡ�\n");

    //��ʾ����⾳
    pop_yj(me,name);

    return 1;

}

string set_color(string arg)
{
	arg = replace_string(arg, "$BLK$", BLK);
	arg = replace_string(arg, "$RED$", RED);
	arg = replace_string(arg, "$GRN$", GRN);
	arg = replace_string(arg, "$YEL$", YEL);
	arg = replace_string(arg, "$BLU$", BLU);
	arg = replace_string(arg, "$MAG$", MAG);
	arg = replace_string(arg, "$CYN$", CYN);
	arg = replace_string(arg, "$WHT$", WHT);
	arg = replace_string(arg, "$HIR$", HIR);
	arg = replace_string(arg, "$HIG$", HIG);
	arg = replace_string(arg, "$HIY$", HIY);
	arg = replace_string(arg, "$HIB$", HIB);
	arg = replace_string(arg, "$HIM$", HIM);
	arg = replace_string(arg, "$HIC$", HIC);
	arg = replace_string(arg, "$HIW$", HIW);
	arg = replace_string(arg, "$NOR$", NOR);

	return arg;
}