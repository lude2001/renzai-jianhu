// sky-sword ���콣
// Modifyied by rock

#include <weapon.h>
#include <ansi.h>
inherit SWORD;

// �������������
int query_xy() { return 1 ; }

int do_perform(string arg);
int do_training(string arg);
int do_healing(string arg);
int do_weapjob(string arg);

void create()
{
        set_name(HIY HIM "���콣" NOR,({ "sky sword", "sky", "sword", "jian" }) );
        set_weight(10000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
		set("no_drop", "�������������뿪�㡣\n");
		set("no_put",1);
		set("no_sell",1);
		set("no_save",1);
		set("no_give",1);
		set("nopaimai",1);
		set("zhiliang",3);
		set("level",1);
		set("exp",5000);
		set("weapon_prop/baoji",10000);
                set("material", "steel");
                set("_level",20);
                set("jing",100);
                set("jingli",50);
                set("weapon_prop/strength",5);
                set("weapon_prop/dexerity",5);
                set("weapon_prop/intelligence",5);
                set("weapon_prop/constitution",5);
								set("dp",10);                //����
								set("pp",10);                //׷�ӷ���
								set("ap",10);                //׷�ӹ���
								set("cp",10);
//                set("long", "����һ���ĳ������ĹŽ��������Ͻ�˿���������֡����족������������������һ����������δ���ʣ��ѿɼ��䲻����\n");
                set("wield_msg", HIY "$N��ৡ���һ�����$n" + HIY + "���˸�������������â���£������Ƿɡ� ....$N���ɵô��ĵ�����һ�����ƺ�����\n" NOR);
                set("unwield_msg", HIW "���콣"HIY"����һ���׹⣬��ৡ��ط��뽣�ʡ�\n" NOR);
        }
        set("max_lasting",100);
        set("gender","�С�Ů");    //�����Ա�
        init_sword(2000);
        setup();
}

int move(mixed dest)
{
        if(!objectp(dest) || !userp(dest))       return ::move(dest);
				if(objectp(dest) && userp(dest) && present("dragon blade",dest))
				{
					tell_object(dest,"�������ȥ�����콣����ȴ����������ɣ����ǿ�ϧ��\n");
					::move("/d/city/guangchang");
					return 0;
				}
				if( ::move(dest)==0)    return 0;
//        message("channel:rumor",YEL"��ҥ�ԡ�"HIM"ĳ�ˣ����첻����˭�����档���콣��"+dest->query("name")+"�������ˣ�\n"NOR,users());
        return 1;
}

string check_len(string str)
{
	int max_len = 33,len;
	
	len = (max_len+color_len(str)) - strlen(str);
	return sprintf("%"+len+"s","��\n");
}

void init()
{
	object ob = this_object();
	object owner = environment(ob);
	string name,gender,str,temp_str,equip_zl,chars,baoji_str;
	int weight,level,value,ap,dp,pp,hp,mp,exp,lasting,cp,damage,baoji,zj,zl,con,strs,dex,ints,cons,jing,jingli;

	if(!ob->query("long"))
	{
		name = ob->query("name");
		gender = ob->query("gender");
		weight = ob->query_weight();
		level = ob->query("level");
		value = ob->query("value");
		damage = ob->query("weapon_prop/damage");
		baoji = ob->query("weapon_prop/baoji");

		pp = ob->query("pp");
		hp = ob->query("hp");
		mp = ob->query("mp");
		exp = ob->query("exp");
                cp = ob->query("cp");
		ap = ob->query("ap");
		dp = ob->query("dp");
		zl = ob->query("zhiliang");
		lasting = ob->query("max_lasting");
		zj = ob->query("_level");
		con = ob->query_amount();
		strs = ob->query("weapon_prop/strength");
		dex = ob->query("weapon_prop/dexerity");
		ints = ob->query("weapon_prop/intelligence");
		cons = ob->query("weapon_prop/constitution");
		jing = ob->query("jing");
		jingli = ob->query("jingli");

		switch(zl)
		{
			case 1  : equip_zl = YEL"�м�"NOR; break;
			case 2  : equip_zl = MAG"�߼�"NOR; break;
			case 3  : equip_zl = HIG"׿Խ"NOR; break;
			default : equip_zl = HIB"����"NOR; break;
		}
		
		chars = sprintf("[%s]",equip_zl);
		str = HIY"��������ҷ���"NOR"װ������:";
		/*str += "\n��������������������������������\n";

		if(zj) temp_str = sprintf("��%7s+%d%s%s","",zj,name,chars);
		else temp_str = sprintf("��%7s%s%s","",name,chars);
		str += temp_str;
		str += check_len(temp_str);
		str += sprintf("��%28s��\n","");

		if(exp) { temp_str = sprintf("��%7s��������: %d","",exp); }
		else { temp_str = sprintf("��%7s��������: %s","","������"); }
		str += temp_str;
		str += check_len(temp_str);

		if(gender) temp_str = sprintf("��%7s�Ա�����: %s","",gender);
		else temp_str = sprintf("��%7s�Ա�����: %s","","������");
		str += temp_str;
		str += check_len(temp_str);

		if(level) temp_str = sprintf("��%7s�ȼ�����: %d","",level);
		else temp_str = sprintf("��%7s�ȼ�����: %s","","������");
		str += temp_str;
		str += check_len(temp_str);

		temp_str = sprintf("��%7sװ���;�: %d","",lasting);
		str += temp_str;
		str += check_len(temp_str);

		temp_str = sprintf("��%7sװ����ֵ: �޼�֮��","");
		str += temp_str;
		str += check_len(temp_str);

		temp_str = sprintf("��%7sװ������: %d","",damage);
		str += temp_str;
		str += check_len(temp_str);

		if(hp)
		{
			temp_str = sprintf("��%7s"HIC"��Ѫ�ӳ�: %d"NOR,"",hp);
			str += temp_str;
			str += check_len(temp_str);
		}
		if(mp)
		{
			temp_str = sprintf("��%7s"YEL"�����ӳ�: %d"NOR,"",mp);
			str += temp_str;
			str += check_len(temp_str);
		}
		if(pp < 0)
		{
			temp_str = sprintf("��%7s���ٷ���: %d","",pp);
			str += temp_str;
			str += check_len(temp_str);
		}
		else if(pp)
		{
			temp_str = sprintf("��%7s"HIY"׷�ӷ���: %d"NOR,"",pp);
			str += temp_str;
			str += check_len(temp_str);
		}
		if(ap||cp)
		{
			temp_str = sprintf("��%7s"HIM"׷�ӹ���: %d(%d)"NOR,"",ap,cp);
			str += temp_str;
			str += check_len(temp_str);
		}
		if(baoji)
		{
			baoji_str = sprintf("%d.%d%d",baoji/100,baoji%100,baoji%10)+"%";
			temp_str = sprintf("��%7s"HIR"װ��������%s"NOR,"",baoji_str);
			str += temp_str;
			str += check_len(temp_str);
		}
		if(strs)
		{
			temp_str = sprintf("��%7s"RED"��������: %d"NOR,"",strs);
			str += temp_str;
			str += check_len(temp_str);
		}
		if(dex)
		{
			temp_str = sprintf("��%7s"MAG"������: %d"NOR,"",dex);
			str += temp_str;
			str += check_len(temp_str);
		}
		if(ints)
		{
			temp_str = sprintf("��%7s"CYN"��������: %d"NOR,"",ints);
			str += temp_str;
			str += check_len(temp_str);
		}
		if(cons)
		{
			temp_str = sprintf("��%7s"YEL"��������: %d"NOR,"",cons);
			str += temp_str;
			str += check_len(temp_str);
		}
		if(con)
		{
			temp_str = sprintf("��%7s"HIW"װ������: %d"NOR,"",con);
			str += temp_str;
			str += check_len(temp_str);
		}
		if(jing)
		{
			temp_str = sprintf("��%7s"HIG"�����ӳ�: %d"NOR,"",jing);
			str += temp_str;
			str += check_len(temp_str);
		}
		if(jingli)
		{
			temp_str = sprintf("��%7s"HIR"�����ӳ�: %d"NOR,"",jingli);
			str += temp_str;
			str += check_len(temp_str);
		}*/
		str += HIY"����һ���ĳ������ĹŽ��������Ͻ�\n˿���������֡����족������������\n������һ����������δ���ʣ��ѿɼ�\n�䲻����\n"
		"û��װ��Ϊ�������޷�ʹ�����й��ܡ�\n"
		"[��������]����ն: perform banyue\n"
		"[��������]�����ȼ�: healing id\n"
		"[��������]��������: xunlian\n"
		"[��������]����������������hljob\n"
		NOR;

		ob->set("long",str);
	}

	if(userp(owner))
	{
				if(present("dragon blade",owner))
				{
					tell_object(owner,"���콣������������ˣ����ǿ�ϧ��\n");
					ob->move("/d/city/guangchang");
					return;
				}
		add_action("do_perform", "perform");
		add_action("do_training", "xunlian");
		add_action("do_healing","healing");
		add_action("do_weapjob","hljob");
  }
}

int do_perform(string arg)
{
	object me = this_player();
	object env,obj=this_object(),*player;
	object blade;
	int size,i,index;
	
	if(!arg || me->query_temp("weapon") != obj) return 0;

	if(arg == "banyue") //����ո
	{
		env = environment(me);
		player = all_inventory(env);
		size = sizeof(player);

		if(me->query("neili")<me->query_max_neili())
		{
			tell_object(me,"������������\n");
			return 1;
		}
		
		if(obj->query("max_lasting") < 10)
		{
			tell_object(me,"�;öȲ��㣬���콣�ķ����Ѵ���ǰ��\n");
			return 1;
		}
		
		if(!objectp(env) || env->query("sleep_room") || env->query("no_fight"))
		{
			tell_object(me,"���ﲻ׼ս����\n");
			return 1;
		}
	
		tell_room(env,sprintf(BLINK+HIW"%sʹ������ն���������콣�����Ⱪ�ǡ�ɨ��һ��ɷ�׽�������������֮��"BLINK+HIR"˭������"BLINK+HIW"��\n"NOR,me->name()) );

		for(i=0;i<size;i++)
		{
			if( !objectp(player[i]) || !userp(player[i]) || player[i]->is_npc() || player[i] == me) continue;

			if(blade = present("dragon blade",player[i]))
			{
				tell_room(env,sprintf(BLINK+HIY"%s������������һ��׹⣬��%s�Ľ������˻�ȥ��%s����������Ӳ�Ǳ��Լ��Ľ����������ˡ�\n"NOR,player[i]->name(),me->name(),me->name()) );
				index = 1+random(10);
				me->set("eff_qi",index);
				me->set("qi",index);
				me->start_busy(120);
				me->set("neili",0);
				obj->add("max_lasting",-1000);
				tell_object(me,HIR"����ʽδ�����³�һ����Ѫ�����޻���֮����\n"NOR);
				return 1;
			}
			else if(player[i]->query("age") < 18)
			{
				tell_room(env,sprintf(HIR"���콣����%sͷ���ӹ������˼����������Һ�û�д󰭣����ǸϽ��뿪Ϊ�\n"NOR,player[i]->name()) );
				continue;
			}
			else
			{
				switch(random(5))
				{
					case 0 : 
						tell_room(env,sprintf(HIR"���콣������%s���ţ������ʱ���������Ĵ��ɽ���\n"NOR,player[i]->name()) );
						break;
					case 1 :
						tell_room(env,sprintf(HIR"���콣������%sͷ­��ѪҺ�沪�����������ͷ­������ء�\n"NOR,player[i]->name()) );
						break;
					case 2 :
						tell_room(env,sprintf(HIR"���콣������%s�۰򣬽�����������������Σ�ɷ�ǿֲ���\n"NOR,player[i]->name()) );
						break;
					case 3 :
						tell_room(env,sprintf(HIR"���콣������%s���������������жϿ���ѪҺ���衣\n"NOR,player[i]->name()) );
						break;
					case 4 :
						tell_room(env,sprintf(HIR"���콣����������%s��ֻʣһ������վ������Լ�ɼ��������࣬ɷ�ǿֲ���\n"NOR,player[i]->name()) );
						break;
				}
				player[i]->set_temp("die_for","�����콣������");
				player[i]->die();
			}
		}
		me->start_busy(60);
		me->set("neili",0);
		obj->add("max_lasting",-1000);
		tell_object(me,HIG"�㽫����ն�������ֻ꣬��һ�����ѣ���ʱ�޷��˹���\n"NOR);
		return 1;
	}
	return 0;
}

int do_training(string arg)
{
	object me= this_player();

	if(me->query_temp("weapon") != this_object()) return 0;

	return "/adm/daemons/makeweapon"->call_do_training(me,arg);
}

int do_healing(string arg)
{
	object me = this_player();
	
	if(me->query_temp("weapon") != this_object()) return 0;
	
	return "/adm/daemons/makeweapon"->heal(me,arg);
}

int do_weapjob(string arg)
{
	object me = this_player();
	
	if(me->query_temp("weapon") != this_object()) return 0;
	
	return "/adm/daemons/makeweapon"->job_info(me,arg);
}