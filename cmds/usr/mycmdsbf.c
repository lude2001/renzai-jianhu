// time.c

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	int i,bt;
	string str,cmd;

	if(!arg)
	{
		write(ZJBTSET"b12:"HIG"����"NOR":mycmds ofen"ZJSEP"b13:"HIY"����"NOR":mycmds skill"ZJSEP"b14:"HIR"ս��"NOR":mycmds fight"ZJSEP
			"b15:"HIM"����"NOR":mycmds quest"ZJSEP"b16:"HIW"��Ϸ"NOR":mycmds help"ZJSEP"b17:"HIC"����"NOR":mycmds liaotian"+"\n");
//		write(ZJTTMENU" ���� :help mapb"ZJSEP" ���� :map view\n");
	}
	else if(arg=="liaotian")
	"/cmds/usr/liaotian"->main(me);
	else if(arg=="ofen")
		write(ZJBTSET"b1:�鿴"ZJBR"����:i"ZJSEP"b2:����"ZJBR"��ҳ:score"ZJSEP"b3:����"ZJBR"״̬:hp"
			ZJSEP"b4:�鿴"ZJBR"װ��:arm"ZJSEP"b5:����"ZJBR"�趨:look"ZJSEP"b6:����"ZJBR"�趨:look"ZJSEP"b8:���"ZJBR"���:banghui"
			ZJSEP"b7:����"ZJBR"��Ϣ"NOR":team"ZJSEP"b9:"YEL"�۲�"ZJBR"����"NOR":look"ZJSEP"b10:�ɾ�"ZJBR"ϵͳ:querytitles"ZJSEP"b11:����"ZJBR"�趨:look"+"\n");
	else if(arg=="skill")
		write(ZJBTSET"b1:�鿴"ZJBR"����:skills"ZJSEP"b2:�ճ�"ZJBR"����:help liangong"ZJSEP"b3:����"ZJBR"��Ѫ:exert recover"
			ZJSEP"b4:����"ZJBR"�ؾ�:exert regenerate"ZJSEP"b5:����"ZJBR"����:exert heal"ZJSEP"b6:����"ZJBR"����:exert inspire"
			ZJSEP"b7:����"ZJBR"�Ƽ�:exert dispel"ZJSEP"b8:�ڹ�"ZJBR"����:enforce"ZJSEP"b9:ս��"ZJBR"��Ϣ:set combatd"ZJSEP"b10:�츳"ZJBR"����:special"ZJSEP"b11:����"ZJBR"�趨:look"+"\n");
	else if(arg=="fight")
	{
		str = ZJBTSET;
		for(i=1;i<11;i++)
		{
			if(cmd=me->query("mycmds/fight/b"+i))
				str += "b"+i+":"+cmd;
			else
				str += "b"+i+":���"ZJBR"ѡ��"+i+":mycmds reset "+i;
			str += ZJSEP;
		}
		str += "b11:����"ZJBR"����:mycmds reset";
		write(str+"\n");
	}
	else if(arg=="quest")
	write("��δ���š�\n");
	else if(arg=="help")
		write("��δ���š�\n");
	else if(arg=="reset")
	{
		str = ZJBTSET;
		for(i=1;i<11;i++)
		{
			str += "b"+i+":���"ZJBR"ѡ��"+i+":mycmds reset "+i;
			str += ZJSEP;
		}
		str += "b11:����:mycmds fight";
		write(str+"\n");
		write(ZJTMPSAY"��������Ҫ����İ�ťѡ���¹��ܡ�\n");
	}
	else if(sscanf(arg,"reset %d %s",bt,cmd)==2)
	{
		string a,b;

		if(bt<1||bt>10)
			return notify_fail(ZJOBLONG"û�������ť������\n");
		if(cmd == "�Զ���")
		{
			write(INPUTTXT("�������Զ����ִ�������:����(�鿴:look)","mycmds reset "+bt+" $txt#")+"\n");
			return 1;
		}
		cmd = replace_string(cmd,"��",":");
		cmd = replace_string(cmd,"#E",ESA);
		cmd = replace_string(cmd,"/",ZJBR);
		cmd = replace_string(cmd,"\n",ZJBR);
		if(sscanf(cmd,"%s:%s",a,b)!=2)
			return notify_fail(HIR"��ʽ���������¶��壡"NOR"\n");
		me->set("mycmds/fight/b"+bt,cmd);
		write(ZJBTSET"b"+bt+":"+cmd+"\n");
	}
	else if(sscanf(arg,"reset %d",bt)==1)
	{
		mapping smap, pmap, pfms,skips;
		string force_ski,weapon_ski,*pfm,ski_type,uski_type;
		int k,flag;
		string msg,*valid_types,*skis,*cmdd;
		object weapon;

		if(bt<1||bt>10)
			return notify_fail(ZJOBLONG"û�������ť������\n");

		valid_types = ({"finger","hand","cuff","claw","strike","unarmed","fufa", "thorwing"});
		skips = ([]);
		if(!smap = me->query_skill_map()) smap=([]);
		if(!pmap = me->query_skill_prepare()) pmap=([]);
		msg = "";

		if(objectp(weapon = me->query_temp("weapon")))
			ski_type = weapon->query("skill_type");

		if(force_ski=smap["force"])
		{
			pfms = SKILL_D(force_ski)->query_pfm("force");
			if(mapp(pfms)&&pfms!=([]))
			{
				pfm = sort_array(keys(pfms), (: strcmp :) );
				for(i=0;i<sizeof(pfm);i++)
				{
					cmdd = explode(pfms[pfm[i]],":");
					msg += cmdd[0] + ":mycmds reset "+ bt+" " +replace_string(cmdd[0],ESA,"#E")+"��"+ cmdd[1]+" force."+pfm[i]+ZJSEP;
					skips[force_ski+pfm[i]]=1;
				}
			}
		}

		if(force_ski=smap["xinfa"])
		{
			pfms = SKILL_D(force_ski)->query_pfm("xinfa");
			if(mapp(pfms)&&pfms!=([]))
			{
				pfm = sort_array(keys(pfms), (: strcmp :) );
				for(i=0;i<sizeof(pfm);i++)
				{
					if(skips[force_ski+pfm[i]]) continue;
					cmdd = explode(pfms[pfm[i]],":");
					msg += cmdd[0] + ":mycmds reset "+ bt+" " +replace_string(cmdd[0],ESA,"#E")+"��"+ cmdd[1]+" xinfa."+pfm[i]+ZJSEP;
					skips[force_ski+pfm[i]]=1;
				}
			}
		}

		if(force_ski=smap["parry"])
		{
			pfms = SKILL_D(force_ski)->query_pfm("parry");
			if(mapp(pfms)&&pfms!=([]))
			{
				pfm = sort_array(keys(pfms), (: strcmp :) );
				for(i=0;i<sizeof(pfm);i++)
				{
					if(skips[force_ski+pfm[i]]) continue;
					cmdd = explode(pfms[pfm[i]],":");
					msg += cmdd[0] + ":mycmds reset "+ bt+" " +replace_string(cmdd[0],ESA,"#E")+"��"+ cmdd[1]+" parry."+pfm[i]+ZJSEP;
					skips[force_ski+pfm[i]]=1;
				}
			}
		}

		if(force_ski=smap["dodge"])
		{
			pfms = SKILL_D(force_ski)->query_pfm("dodge");
			if(mapp(pfms)&&pfms!=([]))
			{
				pfm = sort_array(keys(pfms), (: strcmp :) );
				for(i=0;i<sizeof(pfm);i++)
				{
					if(skips[force_ski+pfm[i]]) continue;
					cmdd = explode(pfms[pfm[i]],":");
					msg += cmdd[0] + ":mycmds reset "+ bt+" " +replace_string(cmdd[0],ESA,"#E")+"��"+ cmdd[1]+" dodge."+pfm[i]+ZJSEP;
					skips[force_ski+pfm[i]]=1;
				}
			}
		}

		if(objectp(weapon))
		{
			if(stringp(weapon_ski=smap[ski_type]))
			{
				pfms = SKILL_D(weapon_ski)->query_pfm(ski_type);
				if(mapp(pfms)&&pfms!=([]))
				{
					pfm = sort_array(keys(pfms), (: strcmp :) );
					for(i=0;i<sizeof(pfm);i++)
					{
						if(skips[weapon_ski+pfm[i]]) continue;
						cmdd = explode(pfms[pfm[i]],":");
						msg += cmdd[0] + ":mycmds reset "+ bt+" " +replace_string(cmdd[0],ESA,"#E")+"��"+ cmdd[1]+" "+ski_type+"."+pfm[i]+ZJSEP;
						skips[weapon_ski+pfm[i]] = 1;
					}
				}
			}
		}
		else if(!objectp(weapon))
		{
			if(mapp(pmap)&&pmap!=([]))
			{//��������׼������
				skis = sort_array(keys(pmap), (: strcmp :) );
				for(k=0;k<sizeof(skis);k++)
				{
					if(skips[pmap[skis[k]]]) continue;
					pfms = SKILL_D(pmap[skis[k]])->query_pfm(skis[k]);
					if(mapp(pfms)&&pfms!=([]))
					{
						pfm = sort_array(keys(pfms), (: strcmp :) );
						for(i=0;i<sizeof(pfm);i++)
						{
							if(skips[pmap[skis[k]]+pfm[i]]) continue;
							cmdd = explode(pfms[pfm[i]],":");
							msg += cmdd[0] + ":mycmds reset "+ bt+" " +replace_string(cmdd[0],ESA,"#E")+"��"+ cmdd[1]+" "+skis[k]+"."+pfm[i]+ZJSEP;
							skips[pmap[skis[k]]+pfm[i]] = 1;
						}
					}
				}
			}

			skis = sort_array(keys(smap), (: strcmp :) );
			for(k=0;k<sizeof(skis);k++)
			{
				flag = 1;
				for(i=0;i<sizeof(valid_types);i++)
				{
					if(SKILL_D(smap[skis[k]])->valid_enable(valid_types[i]))
					{
						uski_type = valid_types[i];
						flag = 2;
					}
				}
				if(!skips[smap[skis[k]]]&&flag==2)
				{
					pfms = SKILL_D(smap[skis[k]])->query_pfm(uski_type);
					if(mapp(pfms)&&pfms!=([]))
					{
						pfm = sort_array(keys(pfms), (: strcmp :) );
						for(i=0;i<sizeof(pfm);i++)
						{
							if(skips[smap[skis[k]]+pfm[i]]) continue;
							cmdd = explode(pfms[pfm[i]],":");
							msg += cmdd[0] + ":mycmds reset "+ bt+" " +replace_string(cmdd[0],ESA,"#E")+"��"+ cmdd[1]+" "+skis[k]+"."+pfm[i]+ZJSEP;
							skips[smap[skis[k]]+pfm[i]] = 1;
						}
					}
				}
			}
		}
		write(ZJOBLONG"�����趨��ť"HIG+chinese_number(bt)+NOR"Ϊʲô���ܣ�\n"ZJOBACTS2+ZJMENUF(5,5,8,30)
			+msg
			+"����"ZJBR"���:mycmds reset "+bt+" ����"ZJBR"�����shot"ZJSEP
			+"����"ZJBR"����:mycmds reset "+bt+" ����"ZJBR"������exert recover"ZJSEP
			+"����"ZJBR"�ؾ�:mycmds reset "+bt+" ����"ZJBR"�ؾ���exert regenerate"ZJSEP
		      +"����"ZJBR"����:mycmds reset "+bt+" ����"ZJBR"���ˣ�exert heal"ZJSEP
			+"����"ZJBR"�Ƽ�:mycmds reset "+bt+" ����"ZJBR"�Ƽ���exert dispel"ZJSEP
			+"�ͷ�"ZJBR"ŭ��:mycmds reset "+bt+" �ͷ�"ZJBR"ŭ����burning"ZJSEP
			+"�Ի�"ZJBR"�ĵ�:mycmds reset "+bt+" �Ի�"ZJBR"�ĵ���use huxin dan"ZJSEP
			+"����"ZJBR"һ:mycmds reset "+bt+" ����"ZJBR"һ��aa"ZJSEP
			+"����"ZJBR"��:mycmds reset "+bt+" ����"ZJBR"����bb"ZJSEP
			+"����"ZJBR"��:mycmds reset "+bt+" ����"ZJBR"����cc"ZJSEP
			+"\n");
	}
	return 1;
}

int help(object me)
{
     write(@HELP

���ָ�����趨��ϷĬ�ϵ��Զ��尴ť��

HELP
    );
    return 1;
}