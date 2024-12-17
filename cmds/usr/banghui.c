#include <ansi.h>;
inherit F_CLEAN_UP;
mapping lista = ([//1����
	"/clone/weapon/unarmed/jinbi" : 50,
	"/clone/weapon/unarmed/longya" : 60,
	"/clone/weapon/unarmed/moya" : 100,
	"/clone/weapon/sword/qingfeng" : 50,
	"/clone/weapon/sword/rouqing" : 80,
	"/clone/weapon/sword/leihen" : 100,
	"/clone/weapon/blade/zijin" : 50,
	"/clone/weapon/blade/wenrou" : 100,
	"/clone/weapon/blade/wuqing" : 120,
	"/clone/armor/qingtian" : 50,
	"/clone/cloth/changpao" : 50,
	"/clone/armor/suozi" : 80,
	"/clone/armor/jinbeixin" : 100,
]);
mapping listb = ([//2����
	"/clone/weapon/unarmed/shihun" : 300,
	"/clone/weapon/sword/youlong" : 300,
	"/clone/weapon/blade/qisha" : 300,
	"/clone/armor/yuxue" : 300,
]);
mapping listc = ([//3����
	"/clone/weapon/unarmed/longshuang" : 800,
	"/clone/weapon/sword/chengying" : 800,
	"/clone/weapon/blade/canshang" : 800,
	"/clone/cloth/wucan" : 800,
]);
mapping listd = ([//4����
	"/clone/vip/njshi" : 1000,
	"/clone/vip/hufajuan" : 2000,
	"/clone/vip/xunrenjuan" : 200,
]);
int main(object me, string arg)
{
	int all,page,i,j,max, index;
	object *t,obj,env,newroom;
	string str,short,text,*list,*list2,*mb,*mb1,add,*zhudi,*items;
	mapping bhinfo,user,max_list=([]);

	env = environment(me);

	if (me->is_busy())
		return notify_fail(ZJOBLONG"��������æ���ء�\n");

	if( !arg )
	{
		if(!(short=me->query("banghui/name")))
		{
			str = ZJOBLONG"��Ŀǰ��û�а�ᣡ����Լ��������Ӵ���һ��������ѡ�����һ�����˴����İ�ᡣ\n";
			page = 1;
			list2 = BANGHUI_D->query_names();
			list = ({});
			if(!sizeof(list2))
			{
				write(ZJOBLONG"Ŀǰ��Ϸ�����ް����֯��\n");
				return 1;
			}
			for(i=0;i<sizeof(list2);i++)
			{
		
				list += ({ list2[i]+":banghui cha "+list2[i] });
			}
			str += ZJOBACTS2+ZJMENUF(2,2,9,30);
			all = sizeof(list)/10;
			if(sizeof(list)%10) all += 1;
			if(page<1) page = 1;
			if(page>all) page = all;
			j = (page-1)*10;
			i = page*10;
			if (i >= sizeof(list)) i = sizeof(list);
			i--;
			if(all>1)
				str += "��һҳ:banghui ls "+(page-1)+ZJSEP"��һҳ:banghui ls "+(page+1)+ZJSEP;
			str += implode(list[j..i], ZJSEP);
			write(str+"\n");
		}
		else
		{
			text = ZJOBLONG"���ƣ�"+short+"������";
			text += "������"+TOP_D->get_name(BANGHUI_D->query_banghui(short+"/bangzhu"));
			text += ZJBR"һһһһһһһһһһһһһһһһһһһһһһһ";
			text += ZJBR"�ȼ���"+BANGHUI_D->query_banghui(short+"/level")+
					"��"+BANGHUI_D->query_banghui(short+"/exp")+"/"+BANGHUI_D->query_banghui(short+"/level")*BANGHUI_D->query_banghui(short+"/level")*BANGHUI_D->query_banghui(short+"/level")*10000+"��";
			text += "����������"+BANGHUI_D->query_banghui(short+"/chubei");
			if(zhudi=BANGHUI_D->query_banghui(short+"/zhudi"))
				text += ZJBR"פ�أ�"+implode(zhudi,",");
			else
				text += ZJBR"פ�أ���";
			text += ZJBR"һһһһһһһһһһһһһһһһһһһһһһһ"ZJBR"���棺";
			if(BANGHUI_D->query_banghui(short+"/txt"))
				text += BANGHUI_D->query_banghui(short+"/txt");
			else
				text += "���޹��棡";
			text += ZJBR"һһһһһһһһһһһһһһһһһһһһһһһ";
			text += ZJBR"��������";
			if(zhudi=BANGHUI_D->query_banghui(short+"/fubang"))
			{
				for(i=0;i<sizeof(zhudi);i++)
				text += TOP_D->get_name(zhudi[i])+"��";
			}
			else
				text += "��";
			text += ZJBR"��Ա����"+CHINESE_D->chinese_number(sizeof(BANGHUI_D->query_banghui(short+"/member")))+"λ";
			text += "\n"ZJOBACTS2+ZJMENUF(3,3,10,30);
			text += "����б�:banghui ls 1";
			text += ZJSEP"��Ա�б�:banghui mb 1";
			text += ZJSEP"�˳����:banghui quit";
			text += ZJSEP"��פ��:banghui zhudi";
			if(me->query("banghui/zhiwei")=="����")
			{
				text += ZJSEP"�༭����:banghui txt";
				text += ZJSEP"�����ؼ���:banghui mijige";
				text += ZJSEP"�鿴����:banghui add 1";
				text += ZJSEP"��ɢ���:banghui jiesan";
			text += ZJSEP"�������:banghui lvup";
			}
			else if(me->query("banghui/zhiwei")=="������")
			{
				text += ZJSEP"�鿴����:banghui add 1";
				text += ZJSEP"�༭����:banghui txt";
			}
			if (playerp(me)) 
			{
			text += ZJSEP"�����ƽ�:banghui gx";
			text += ZJSEP"����ʦ�Ź���:banghui smgx";
//		text += ZJSEP"�һ���Ʒ:banghui dhlist";
			}
			write(text+"\n");
/*		 if (!BANGHUI_D->query_banghui(short+"/gongxian/"+me->query("id"))&&BANGHUI_D->query_banghui(short+"/gongxian/"+me->query("name")))
		 {		 	
		BANGHUI_D->set_banghui(short+"/gongxian/"+me->query("id"), BANGHUI_D->query_banghui(short+"/gongxian/"+me->query("name")));			
		BANGHUI_D->set_banghui(short+"/gongxian/"+me->query("name"), 0);
		write("��⵽���İ�ṱ��δ���ת����ϵͳΪ���Զ�ת����\n");	
		 }*/
		}
	} 
	else if (arg=="zhudi")
	{
	if(!(short=me->query("banghui/name")))
			return notify_fail(ZJOBLONG"��û�а����ô��פ�أ�\n");
	me->move(BANGHUI_D->query_banghui(short+"/zhudi_room"));
	tell_object(me,"�������Ṧһ�������ӱޣ���ಣ���ص��˰���פ��\n���۵Ļ������������㺰������tm�ۣ�\n");
	me->start_busy(5);
	}
	else if (arg=="mijige")
	{	
		if(!(short=me->query("banghui/name")))
		return notify_fail(ZJOBLONG"��û�а����ô�����ؼ���\n");

		if (me->query("yuanbao") < 1000)
		return notify_fail("�����ؼ�����Ҫ1000Ԫ����\n");

		if(BANGHUI_D->query_banghui(short+"/mijige"))
		return notify_fail(ZJOBLONG"����Ѿ������ؼ�����!\n");

		me->add("yuanbao",-1000);
		BANGHUI_D->set_banghui(short+"/mijige",1);
		return 1;
	}
	else if( sscanf(arg,"attack %s",text)==1 )
	{
		if(!(short=me->query("banghui/name")))
			return notify_fail(ZJOBLONG"��û�а����ô������ս��\n");
		if(me->query("banghui/zhiwei")!="����"&&me->query("banghui/zhiwei")!="������")
			return notify_fail(ZJOBLONG"��û�з�����ս��Ȩ�ޣ�\n");
		if(!BANGHUI_D->query_banghui(text))
			return notify_fail(ZJOBLONG"û�������ᣡ\n");
		if(!BANGHUI_D->query_banghui(text+"/zhudi"))
			return notify_fail(ZJOBLONG"�Է���פ�ض�û����Ҫ������ɶ��\n");
		if(BANGHUI_D->query_banghui(short+"/chubei")<10000)
			return notify_fail(ZJOBLONG"��ᴢ������10000�������㹻ʵ���ٷ�����ս��\n");
		if(!BANGHUI_D->query_banghui(short+"/attackby"))
			BANGHUI_D->set_banghui(text+"/attackby",({short}));
		else
			BANGHUI_D->set_banghui(text+"/attackby",BANGHUI_D->query_banghui(short+"/attackby")+({short}));
	}
	else if( sscanf(arg,"txt %s",text)==1 )
	{
		if(!(short=me->query("banghui/name")))
			return notify_fail(ZJOBLONG"��û�а�ᷢʲô���棡\n");
		if(me->query("banghui/zhiwei")!="����"&&me->query("banghui/zhiwei")!="������")
			return notify_fail(ZJOBLONG"��û�з������Ȩ�ޣ�\n");
		BANGHUI_D->set_banghui(short+"/txt",text);
		write(ZJFORCECMD("banghui"));
	}
	else if( sscanf(arg,"ls %d",page)==1 )
	{
		str = ZJOBLONG"Ŀǰ��Ϸ�������°�᣺\n";
		list2 = BANGHUI_D->query_names();
		list = ({});
		if(!sizeof(list2))
		{
			write(ZJOBLONG"Ŀǰ��Ϸ�����ް����֯��\n");
			return 1;
		}
		for(i=0;i<sizeof(list2);i++)
		{
			list += ({ list2[i]+"��"+BANGHUI_D->query_banghui(list2[i]+"/level")+"����:banghui cha "+list2[i] });
		}
		str += ZJOBACTS2+ZJMENUF(2,2,9,30);
		all = sizeof(list)/10;
		if(sizeof(list)%10) all += 1;
		if(page<1) page = 1;
		if(page>all) page = all;
		j = (page-1)*10;
		i = page*10;
		if (i >= sizeof(list)) i = sizeof(list);
		i--;
		if(all>1)
			str += "��һҳ:banghui ls "+(page-1)+ZJSEP"��һҳ:banghui ls "+(page+1)+ZJSEP;
		str += implode(list[j..i], ZJSEP);
		write(str+"\n");
	}
	else if( sscanf(arg,"add %d",page)==1 )
	{
		if(!(short=me->query("banghui/name")))
			return notify_fail(ZJOBLONG"�㻹û�а���أ�\n");
		mb = BANGHUI_D->query_banghui(short+"/shenqing");
		if(!pointerp(mb)||mb==({}))
		{
			return notify_fail(ZJOBLONG"û����������\n");
		}
		list = ({});
		mb1 = ({});
		for(i=0;i<sizeof(mb);i++)
		{
			user = TOP_D->query_user(mb[i]);
			if (!user)
				continue;
			if(find_player(mb[i]))
				list += ({sprintf(HIG"%s��������"NOR":banghui look2 %s",user["name"],mb[i])});
			else
				mb1 += ({sprintf(HIG"%s��������"NOR":banghui look2 %s",user["name"],mb[i])});
		}
		list += mb1;
		str = ZJOBLONG+short+"�����������б���\n";
		str += ZJOBACTS2+ZJMENUF(2,2,9,30);
		all = sizeof(list)/10;
		if(sizeof(list)%10) all += 1;
		if(page<1) page = 1;
		if(page>all) page = all;
		j = (page-1)*10;
		i = page*10;
		if (i >= sizeof(list)) i = sizeof(list);
		i--;
		if(all>1)
			str += "��һҳ:banghui add "+(page-1)+ZJSEP"��һҳ:banghui add "+(page+1)+ZJSEP;
		str += implode(list[j..i], ZJSEP);
		write(str+"\n");
	}
	else if( sscanf(arg,"addyes %s",add)==1 )
	{
		if(!(short=me->query("banghui/name")))
			return notify_fail(ZJOBLONG"�㻹û�а���أ�\n");
		mb1 = BANGHUI_D->query_banghui(short+"/fubang");
		if(!mb1) mb1 = ({});
		if((BANGHUI_D->query_banghui(short+"/bangzhu")!=me->query("id"))&&(member_array(me->query("id"),mb1)==-1))
			return notify_fail(ZJOBLONG"��û�����˵�Ȩ����\n");
		list = BANGHUI_D->query_banghui(short+"/shenqing");
		mb = BANGHUI_D->query_banghui(short+"/member");

		if(sizeof(mb)>=(BANGHUI_D->query_banghui(short+"/level")*5+10))
			return notify_fail(ZJOBLONG"��������Ѵﵽ�ȼ����ޣ�\n");
		if(!pointerp(list)||(member_array(add,list)==-1))
			return notify_fail(ZJOBLONG"����û��������\n");
		if(member_array(add,mb)!=-1)
			return notify_fail(ZJOBLONG"�������ڰ���ˣ�\n");
		user = TOP_D->query_user(add);
		if(!user)
			return notify_fail(ZJOBLONG"û������ˣ�\n");
		if(!(obj=UPDATE_D->global_find_player(add)))
			return notify_fail(ZJOBLONG"û������ˣ�\n");

		if(obj->query("banghui"))
		{
			BANGHUI_D->set_banghui(short+"/shenqing",list-({add}));
			return notify_fail(ZJOBLONG"����ʧ�ܣ������Ѿ��а����ˣ�\n");
		}
		obj->set("banghui/name",short);
		obj->set("banghui/zhiwei","����");
		obj->save();
		CHANNEL_D->do_channel( me,"party",sprintf("%s���뱾��ᣬ��һ�ӭ��", obj->query("name")) );

		list -= ({add});
		BANGHUI_D->set_banghui(short+"/shenqing",list);
		BANGHUI_D->set_banghui(short+"/member",mb+({add}));

		if(list!=({}))
			write(ZJFORCECMD("banghui add 1"));
		else
			write(ZJFORCECMD("banghui mb 1"));
	}
	else if( sscanf(arg,"addno %s",add)==1 )
	{
		if(!(short=me->query("banghui/name")))
			return notify_fail(ZJOBLONG"�㻹û�а���أ�\n");
		list = BANGHUI_D->query_banghui(short+"/shenqing");
		if(!pointerp(list)||(member_array(add,list)==-1))
			return notify_fail(ZJOBLONG"����û��������\n");
		mb1 = BANGHUI_D->query_banghui(short+"/fubang");
		if(!mb1) mb1 = ({});
		if((BANGHUI_D->query_banghui(short+"/bangzhu")!=me->query("id"))&&(member_array(me->query("id"),mb1)==-1))
			return notify_fail(ZJOBLONG"��û�оܾ��˵�Ȩ����\n");
		list -= ({add});
		BANGHUI_D->set_banghui(short+"/shenqing",list);
		if(list!=({}))
			write(ZJFORCECMD("banghui add 1"));
		else
			write(ZJFORCECMD("banghui mb 1"));
	}
	else if( sscanf(arg,"cha %s",short)==1 )
	{
		if(!BANGHUI_D->query_banghui(short))
		return notify_fail(ZJOBLONG"�޴˰�ᣡ\n");

		text = ZJOBLONG"���ƣ�"+short+"������";
		text += "������"+TOP_D->get_name(BANGHUI_D->query_banghui(short+"/bangzhu"));
			text += ZJBR"һһһһһһһһһһһһһһһһһһһһһһһ";
		text += ZJBR"�ȼ���"+BANGHUI_D->query_banghui(short+"/level")+"��"+BANGHUI_D->query_banghui(short+"/exp")+"/"+BANGHUI_D->query_banghui (short+"/level")*BANGHUI_D->query_banghui(short+"/level")*BANGHUI_D->query_banghui(short+"/level")*10000+"��";
		if(zhudi=BANGHUI_D->query_banghui(short+"/zhudi"))
			text += ZJBR"פ�أ�"+implode(zhudi,",");
		else
			text += ZJBR"פ�أ���";
		text += ZJBR"һһһһһһһһһһһһһһһһһһһһһһһ"ZJBR"���棺";
		if(BANGHUI_D->query_banghui(short+"/txt"))
			text += BANGHUI_D->query_banghui(short+"/txt");
		else
			text += "���޹��棡";
		text += ZJBR"һһһһһһһһһһһһһһһһһһһһһһһ";
		text += ZJBR"��������";
		if(zhudi=BANGHUI_D->query_banghui(short+"/fubang"))
		{
			for(i=0;i<sizeof(zhudi);i++)
			text += TOP_D->get_name(zhudi[i])+"��";
		}
		else
			text += "��";
		text += ZJBR"��Ա����"+CHINESE_D->chinese_number(sizeof(BANGHUI_D->query_banghui(short+"/member")))+"λ";
		text += "\n"ZJOBACTS2+ZJMENUF(3,3,10,30);
		text += "�������:banghui join "+short;
		text += ZJSEP"�����б�:banghui ls 1";
		write(text+"\n");
	}
	else if( sscanf(arg,"smgx %d",page)== 1 )
	{
		if(!(short=me->query("banghui/name")))
			return notify_fail(ZJOBLONG"�㻹û�а���أ�\n");
		
		if (page < 10)
			return notify_fail(ZJOBLONG"����10ʦ�Ź�����裡\n");
		if (page > 10000)
			return notify_fail(ZJOBLONG"���10000ʦ�Ź��ף�\n");
		
		if (me->query("gongxian") < page)
			return notify_fail(ZJOBLONG"ʦ�Ź��ײ���"+page+"��\n");
		
		BANGHUI_D->set_banghui(short+"/gongxian/"+me->query("id"), BANGHUI_D->query_banghui(short+"/gongxian/"+me->query("id"))+page);
		BANGHUI_D->set_banghui(short+"/exp", BANGHUI_D->query_banghui(short+"/exp")+page);
		me->add("gongxian", -page);
		write("��Ϊ���ɾ�����"+page+NOR"ʦ�Ź��ס�\n");
	}
	else if( sscanf(arg,"gx %d",page)== 1 )
	{
		if(!(short=me->query("banghui/name")))
			return notify_fail(ZJOBLONG"�㻹û�а���أ�\n");
		
		if (page < 10)
			return notify_fail(ZJOBLONG"����10���ƽ���裡\n");
		if (page > 10000)
			return notify_fail(ZJOBLONG"���10000���ƽ�\n");
		
		if (me->query("balance") < page * 10000)
			return notify_fail(ZJOBLONG"Ǯׯ����"+MONEY_D->money_str(page*10000)+"��\n");
		
		BANGHUI_D->set_banghui(short+"/gongxian/"+me->query("id"), BANGHUI_D->query_banghui(short+"/gongxian/"+me->query("id"))+page);
		BANGHUI_D->set_banghui(short+"/exp", BANGHUI_D->query_banghui(short+"/exp")+page);
		me->add("balance", -(page * 10000));
		write("��Ϊ���ɾ�����"+MONEY_D->money_str(page*10000)+NOR"��\n");
	}
	else if( sscanf(arg,"dhlist %s", add)==1 ) 
	{
		if(!(short=me->query("banghui/name")))
			return notify_fail(ZJOBLONG"�㻹û�а���أ�\n");
		
		max_list += lista;
		if (BANGHUI_D->query_banghui(short+"/level") > 1)
			max_list += listb;
		if (BANGHUI_D->query_banghui(short+"/level") > 2)
			max_list += listc;
		if (BANGHUI_D->query_banghui(short+"/level") > 3)
			max_list += listd;
		
		if (!max_list[add])
			return notify_fail(ZJOBLONG"���޷��һ�����Ʒ��\n");
		
		if(!BANGHUI_D->query_banghui (short+"/gongxian/"+me->query("id"))
			||BANGHUI_D->query_banghui (short+"/gongxian/"+me->query("id")) < max_list[add])
			return notify_fail(ZJOBLONG"��Ĺ��׶Ȳ��㣡\n");

		obj = new(add);
		if (obj->move(me)) {
			BANGHUI_D->set_banghui(short+"/gongxian/"+me->query("id"), BANGHUI_D->query_banghui (short+"/gongxian/"+me->query("id"))-max_list[add]);
			return notify_fail("����"+max_list[add]+"�㹱�׶ȶһ���һ"+obj->query("unit")+obj->query("name")+"��\n");
		} else
			return notify_fail("�һ�ʧ�ܣ���������ռ䡣\n");
	}
	else
	if (arg == "dhlist")
	{
		if(!(short=me->query("banghui/name")))
			return notify_fail(ZJOBLONG"�㻹û�а���أ�\n");
		
		str = ZJOBLONG"��Ŀǰ���õĹ��׻���"+
						BANGHUI_D->query_banghui (short+"/gongxian/"+me->query("id"))
										+"�㣬��ѡ��һ���Ʒ��\n"ZJOBACTS2+ZJMENUF(2,2,9,30);
		max_list = lista;
		if (BANGHUI_D->query_banghui(short+"/level") > 1)
			max_list += listb;
		
		items = keys(max_list);
		
		for(i=0;i<sizeof(items);i++)
		{
			str += items[i]->query("name")+ZJBR"���׶ȣ�"+max_list[items[i]]+":banghui dhlist "+items[i]+ZJSEP;
		}
		tell_object(me, str+"\n");
	} else
	if (arg == "lvup")
	{
		if(!(short=me->query("banghui/name")))
			return notify_fail(ZJOBLONG"�㻹û�а���أ�\n");

		if(me->query("banghui/zhiwei")!="����")
			return notify_fail(ZJOBLONG"ֻ�а��������������ĵȼ���\n");
		
		if (BANGHUI_D->query_banghui(short+"/level") >= 10)
			return notify_fail(ZJOBLONG"Ŀǰ���ȼ����ֻ������ʮ����\n");
		
		if (BANGHUI_D->query_banghui(short+"/exp") < BANGHUI_D->query_banghui(short+"/level")*BANGHUI_D->query_banghui(short+"/level")*BANGHUI_D->query_banghui(short+"/level")*10000)
			return notify_fail(ZJOBLONG"��ṱ�׶Ȳ�����\n");
		
		if(!objectp(obj = present("kuojian ling", me)))
			return notify_fail(ZJOBLONG"������û�������\n");
		
		index = BANGHUI_D->query_banghui(short+"/level") * 2;
		
		if (BANGHUI_D->query_banghui(short+"/level")>=5)
		index = BANGHUI_D->query_banghui(short+"/level")*4;
		
		if (obj->query_amount() < index)
			return notify_fail(ZJOBLONG"�����ϵ��������"+index+"�飡\n");
		
		obj->add_amount(-index);
		BANGHUI_D->set_banghui(short+"/level", BANGHUI_D->query_banghui(short+"/level") + 1);
		CHANNEL_D->do_channel( me,"party",sprintf("%s�ѱ����ȼ�������һ����", me->name()) );
	}

	else if( arg=="quityes" )
	{
		if(!(short=me->query("banghui/name")))
			return notify_fail(ZJOBLONG"��û�а�᲻�����룡\n");
		if(me->query("banghui/zhiwei")=="����")
			return notify_fail(ZJOBLONG"�������������ᣡ\n");
		mb = BANGHUI_D->query_banghui(short+"/member");
		BANGHUI_D->set_banghui(short+"/member",mb-({me->query("id")}));
		me->delete("banghui");
		write(ZJOBLONG"�������˰�� "+short+"��\n");
	}
    else if (arg == "smgx")
	{
		if(!(short=me->query("banghui/name")))
			return notify_fail(ZJOBLONG"��û�а�ᣡ\n");
		return notify_fail(INPUTTXT("������Ҫ���׵�ʦ������("HIY"1��1�һ�"NOR")��","banghui smgx $txt#")+"\n");
	}
	
	else if (arg == "gx")
	{
		if(!(short=me->query("banghui/name")))
			return notify_fail(ZJOBLONG"��û�а�ᣡ\n");
		return notify_fail(INPUTTXT("������Ҫ���׵Ļƽ�����("HIY"�ƽ�/��"NOR")��","banghui gx $txt#")+"\n");
	}

	else if( arg=="quit" )
	{
		if(!(short=me->query("banghui/name")))
			return notify_fail(ZJOBLONG"��û�а�᲻�����룡\n");
		if(me->query("banghui/zhiwei")=="����")
			return notify_fail(ZJOBLONG"�������������ᣡ\n");
		write(ZJOBLONG"��ȷ��Ҫ��������\n"ZJOBACTS2+ZJMENUF(3,3,10,30)+"ȷ��:banghui quityes\n");
	}
	else if( arg=="jiesan" )
	{
		if(!(short=me->query("banghui/name")))
			return notify_fail(ZJOBLONG"��û�а���ɢʲô��\n");
		if(me->query("banghui/zhiwei")!="����")
			return notify_fail(ZJOBLONG"ֻ�а������ܽ�ɢ��ᣡ\n");
		write(ZJOBLONG"��ȷ��Ҫ��ɢ�����\n"ZJOBACTS2+ZJMENUF(3,3,10,30)+"ȷ��:banghui jiesanyes\n");
	}
	else if( arg=="jiesanyes" )
	{
		if(!(short=me->query("banghui/name")))
			return notify_fail(ZJOBLONG"��û�а���ɢʲô��\n");
		if(me->query("banghui/zhiwei")!="����")
			return notify_fail(ZJOBLONG"ֻ�а������ܽ�ɢ��ᣡ\n");
		mb = BANGHUI_D->query_banghui(short+"/member");
		if(sizeof(mb)>1)
			return notify_fail(ZJOBLONG"��������г�Ա�ڣ����ܽ�ɢ��ᣡ\n");
		BANGHUI_D->delete_banghui(short);
		me->delete("banghui");
		CHANNEL_D->do_channel(me,"chat","�������ֵܽ���ϴ�ֹ���ɽ�֣���ɢ��"+short+"����");
		write(ZJOBLONG"���ɢ�˰�� "+short+"��\n");
	}
	else if( sscanf(arg,"join %s",short)==1 )
	{
		if(!BANGHUI_D->query_banghui(short))
			return notify_fail(ZJOBLONG"�޴˰�ᣡ\n");
		if(me->query("banghui"))
			return notify_fail(ZJOBLONG"���Ѿ��а���ˣ�\n");
		list = BANGHUI_D->query_banghui(short+"/shenqing");
		mb = BANGHUI_D->query_banghui(short+"/member");
		if(member_array(me->query("id"),mb)!=-1)
			return notify_fail(ZJOBLONG"�����Ǵ˰������ˣ�\n");
		if(pointerp(list)&&(member_array(me->query("id"),list)!=-1))
			return notify_fail(ZJOBLONG"���Ѿ����������˰���ˣ�����ϵ������Ա�ȴ���Ӧ��\n");
		if(!pointerp(list))
			BANGHUI_D->set_banghui(short+"/shenqing",({me->query("id")}));
		else
			BANGHUI_D->set_banghui(short+"/shenqing",list+({me->query("id")}));
		write(ZJOBLONG"�ѷ���������룬��ȴ�����Ա��ˣ�\n");
	}
	else if( sscanf(arg,"look1 %s",add)==1 )
	{
		if(!(short=me->query("banghui/name")))
			return notify_fail(ZJOBLONG"�㻹û�а���أ�\n");
		list = BANGHUI_D->query_banghui(short+"/member");
		if(!pointerp(list)) list = ({});
		if(member_array(add,list)==-1)
			return notify_fail(ZJOBLONG"��İ���Ա��û�д��ˣ�\n");
		user = TOP_D->query_user(add);
		if(!user)
			return notify_fail(ZJOBLONG"û������ˣ�\n");
		str = ZJOBLONG+user["name"]+ZJBR;
		str += "һһһһһһһһһһһһһһһһһһһһһһһ"ZJBR;
		str += "��Ϊ��"+user["combat_exp"];
		str += "    ɱ����"+user["PKS"];
		str += "\n"ZJOBACTS2+ZJMENUF(3,3,10,30);
		str += "�����б�:banghui mb 1";
		if(me->query("banghui/zhiwei")=="����")
		{
			str += ZJSEP"�������:banghui renming "+add;
			str += ZJSEP"�߳����:banghui tiren "+add;
		}
		write(str+"\n");
	}
	else if( sscanf(arg,"look2 %s",add)==1 )
	{
		if(!(short=me->query("banghui/name")))
			return notify_fail(ZJOBLONG"�㻹û�а���أ�\n");
		list2 = BANGHUI_D->query_banghui(short+"/shenqing");
		if(!pointerp(list2)) list2 = ({});
		if(member_array(add,list2)==-1)
			return notify_fail(ZJOBLONG"��İ�������б���û�д��ˣ�\n");
		user = TOP_D->query_user(add);
		if(!user)
			return notify_fail(ZJOBLONG"û������ˣ�\n");
		str = ZJOBLONG+user["name"]+ZJBR;
		str += "һһһһһһһһһһһһһһһһһһһһһһһ"ZJBR;
		str += "��Ϊ��"+user["combat_exp"];
		str += "    ɱ����"+user["PKS"];
		str += "\n"ZJOBACTS2+ZJMENUF(3,3,10,30);
		str += "�����б�:banghui add 1";
		if(me->query("banghui/zhiwei")=="����"||me->query("banghui/zhiwei")=="������")
		{
			str += ZJSEP"ͬ������:banghui addyes "+add;
			str += ZJSEP"�ܾ�����:banghui addno "+add;
		}
		write(str+"\n");
	}
	else if( sscanf(arg,"tiren %s",add)==1 )
	{
		if(!(short=me->query("banghui/name")))
			return notify_fail(ZJOBLONG"�㻹û�а���أ�\n");
		list = BANGHUI_D->query_banghui(short+"/member");
		if(!pointerp(list)||(member_array(add,list)==-1))
			return notify_fail(ZJOBLONG"��İ��û�д��ˣ�\n");
		if(BANGHUI_D->query_banghui(short+"/bangzhu")!=me->query("id"))
			return notify_fail(ZJOBLONG"��û�����˵�Ȩ����\n");
		if(me->query("id")==add)
			return notify_fail(ZJOBLONG"��Ҫ���Լ���ƨ�ɣ�\n");
		user = TOP_D->query_user(add);
		if(!user)
			return notify_fail(ZJOBLONG"û������ˣ�\n");
		if(!(obj=UPDATE_D->global_find_player(add)))
			return notify_fail(ZJOBLONG"û������ˣ�\n");
		obj->delete("banghui");
		obj->save();
		CHANNEL_D->do_channel( me,"party",sprintf("%s��������ᣡ", obj->query("name")) );

		if(!obj->query_temp("temp_loaded"))
			tell_object(obj,ZJOBLONG"�㱻��������ˣ�\n");

		BANGHUI_D->set_banghui(short+"/member",list-({add}));
		if((mb=BANGHUI_D->query_banghui(short+"/fubang"))&&member_array(add,mb)!=-1)
			BANGHUI_D->set_banghui(short+"/fubang",mb-({add}));
		write(ZJFORCECMD("banghui mb 1"));
	}
	else if( sscanf(arg,"renming %s",add)==1 )
	{
		if(!(short=me->query("banghui/name")))
			return notify_fail(ZJOBLONG"�㻹û�а���أ�\n");

		if( sscanf(add,"%s %s",add,text)!=2 )
		{
			return notify_fail(INPUTTXT("��Ҫ����"+TOP_D->get_name(add)+"Ϊʲô��","banghui "+arg+" $txt#")+"\n");
		}
		list = BANGHUI_D->query_banghui(short+"/member");
		if(!mb = BANGHUI_D->query_banghui(short+"/fubang")) mb = ({});
		if(!pointerp(list)||(member_array(add,list)==-1))
			return notify_fail(ZJOBLONG"��İ��û�д��ˣ�\n");
		if(BANGHUI_D->query_banghui(short+"/bangzhu")!=me->query("id"))
			return notify_fail(ZJOBLONG"��û��������Ȩ����\n");
		if(me->query("id")==add)
			return notify_fail(ZJOBLONG"��Ҫ�����Լ���\n");
		if(pointerp(mb)&&(member_array(add,mb)!=-1)) mb -= ({add});
		if(text=="����")
		{
			me->set("banghui/zhiwei","����");
			BANGHUI_D->set_banghui(short+"/bangzhu",add);
		}
		else if(text=="������")
		{
			if(mb&&sizeof(mb)>=2)
				return notify_fail(ZJOBLONG"����������������\n");
			else
			{
				mb += ({add});
			}
		}
		BANGHUI_D->set_banghui(short+"/fubang",mb);
		user = TOP_D->query_user(add);
		if(!user)
			return notify_fail(ZJOBLONG"û������ˣ�\n");
		if(!(obj=UPDATE_D->global_find_player(add)))
			return notify_fail(ZJOBLONG"û������ˣ�\n");
		obj->set("banghui/zhiwei",text);
		obj->save();
		CHANNEL_D->do_channel( me,"party",sprintf("%s������Ϊ��%s����", obj->query("name"),text) );

		tell_object(me,ZJOBLONG"�����ɹ���\n");
	}
	else if( sscanf(arg,"mb %d",page)==1 )
	{
		if(!(short=me->query("banghui/name")))
		{
			tell_object(me,ZJOBLONG"��Ŀǰ��û�а�ᣡ����Լ��������Ӵ���һ��������ѡ�����һ�����˴����İ�ᡣ\n");
			page = 1;
			list = BANGHUI_D->query_names();
			str = ZJOBLONG+"ָ��ᱦ����б���\n";
			str += ZJOBACTS2+ZJMENUF(2,2,9,30);
			all = sizeof(list)/10;
			if(sizeof(list)%10) all += 1;
			if(page<1) page = 1;
			if(page>all) page = all;
			j = (page-1)*10;
			i = page*10;
			if (i >= sizeof(list)) i = sizeof(list);
			i--;
			if(all>1)
				str += "��һҳ:banghui mb "+(page-1)+ZJSEP"��һҳ:banghui mb "+(page+1)+ZJSEP;
			str += implode(list[j..i], ZJSEP);
			write(str+"\n");
		}
		else
		{
		   int last_on;
			mb = BANGHUI_D->query_banghui(short+"/member");
			list = ({});
			mb1 = ({});
			for(i=0;i<sizeof(mb);i++)
			{
				user = TOP_D->query_user(mb[i]);

				if (!user)
					continue;
				if(find_player(mb[i]))
					list += ({sprintf(HIG"%s��������"NOR+ZJBR+HIY"���ף�%d"NOR":banghui look1 %s",user["name"],BANGHUI_D->query_banghui (short+"/gongxian/"+mb[i]),mb[i])});
				else
				{
				   last_on = FINGER_D->get_last_on(mb[i]);
					mb1 += ({sprintf(HIG"%s��������"NOR+ZJBR+HIY"���ף�%d"ZJBR"�ϴε�¼��%s"NOR":banghui look1 %s",user["name"],BANGHUI_D->query_banghui(short+"/gongxian/"+mb[i]),CHINESE_D->chinese_date(last_on,2),mb[i])});
			    }
			}

			list += mb1;
			str = ZJOBLONG+short+"����Ա��\n";
			str += ZJOBACTS2+ZJMENUF(2,2,6,35);
			all = sizeof(list)/10;
			if(sizeof(list)%10) all += 1;
			if(page<1) page = 1;
			if(page>all) page = all;
			j = (page-1)*10;
			i = page*10;
			if (i >= sizeof(list)) i = sizeof(list);
			i--;
			if(all>1)
				str += "��һҳ:banghui mb "+(page-1)+ZJSEP"��һҳ:banghui mb "+(page+1)+ZJSEP;
			str += implode(list[j..i], ZJSEP);
			write(str+"\n");
		}
	}
	else if( arg == "txt" )
	{
		if(!(short=me->query("banghui/name")))
			return notify_fail(ZJOBLONG"�㻹û�а���أ�\n");
		return notify_fail(INPUTTXT("�������ṫ�棺","banghui txt $txt#")+"\n");
	}
	else if( arg == "create" )
	{
		if(base_name(env)!="/d/city/banghui")
			return notify_fail(ZJOBLONG"�뵽�������������ᣡ\n");
		return notify_fail(INPUTTXT("������������("HIY"���������Ҫ200Ԫ��"NOR")��","banghui create $txt#")+"\n");
	}
	else if( sscanf(arg,"create %s",short)==1 )
	{
	string *zhudi_allroom,zhudi_room;
	zhudi_allroom=list_dirs("/d/bangpai/map/");
		if(base_name(env)!="/d/city/banghui")
			return notify_fail(ZJOBLONG"�뵽�������������ᣡ\n");

		if(me->query("banghui"))
			return notify_fail(ZJOBLONG"�����������ڵİ�ᣡ\n");
		if( !pointerp(t = me->query_team()) || sizeof(t)<2)
			return notify_fail(ZJOBLONG"����������1���������һ����ܴ�����ᣡ\n");
		if(BANGHUI_D->query_banghui(short))
			return notify_fail(ZJOBLONG"��������Ѵ��ڣ�\n");
		for(i=0;i<sizeof(t);i++)
		{
			if (environment(t[i]) != env)
				return notify_fail(ZJOBLONG"��������������˻�û�е����ء�\n");	
			if(t[i]->query("banghui"))
				return notify_fail(ZJOBLONG"��ȷ�϶���Ŀǰ��û�вμӰ�ᣡ\n");
		}
		if( !me->is_team_leader() )
			return notify_fail(ZJOBLONG"�ӳ�����ȷ�ϴ�����ᣡ\n");
		if(!LOGIN_D->check_legal_name(short,10))
			return notify_fail("������ֲ�����Ҫ�󣬽���ʧ�ܣ�\n");

		if( me->query("yuanbao")<200 )
			return notify_fail(ZJOBLONG"���������Ҫ"HIY"200Ԫ��"NOR"��\n");
		
// if (!mkdir("/data/bangpai/"+short+"/map"))   
// return notify_fail("���פ�ش���ʧ�ܣ�����ʧ�ܣ�\n"); 
 
 			
		
		bhinfo = ([]);		
		bhinfo["level"] = 1;
		//Ŀ¼ʹ�ý����˵�id��Ϊʲô��lpc��gbk��֧��uf8�����ļ���������
		bhinfo["zhudi_room"] = "/data/bangpai/"+getuid(me)+"/map/guangchang";
		bhinfo["id"] = me->query("id")+"-"+sprintf("%d",time());
		bhinfo["member"] = t->query("id");
		//����פ���ļ�
		foreach(zhudi_room in zhudi_allroom)
		{
		//�Ƚ���
		assure_file("/data/bangpai/"+getuid(me)+"/map/"+zhudi_room);
		//�����е�ٵ�
		 if (!write_file("/data/bangpai/"+getuid(me)+"/map/"+zhudi_room,read_file("/d/bangpai/map/"+zhudi_room),1))
			return notify_fail(file_size("/d/bangpai/map/"+zhudi_room)+"�Ű��פ�ش�������������ʧ�ܣ�����ϵ����Ա��\n"); 
			else
			tell_object(me,zhudi_room+"�ɹ�����...\n");
			}
		t->set("banghui/name",short);		
		t->set("banghui/zhiwei","Ԫ��");
		me->set("banghui/zhiwei","����");
		me->add("yuanbao",-200);		
		bhinfo["bangzhu"] = me->query("id");
		BANGHUI_D->add_banghui(short,bhinfo);
		CHANNEL_D->do_channel(me,"chat","�������ֵ��ѪΪ�ˣ�������"+short+"����");
		tell_object(me,ZJOBLONG"��ϲ����Ὠ���ɹ���\n");
		me->save();
	}
	return 1;
}