// sky-sword 倚天剑
// Modifyied by rock

#include <weapon.h>
#include <ansi.h>
inherit SWORD;

// 函数：所属类别
int query_xy() { return 1 ; }

int do_perform(string arg);
int do_training(string arg);
int do_healing(string arg);
int do_weapjob(string arg);

void create()
{
        set_name(HIY HIM "倚天剑" NOR,({ "sky sword", "sky", "sword", "jian" }) );
        set_weight(10000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
		set("no_drop", "这样东西不能离开你。\n");
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
								set("dp",10);                //防御
								set("pp",10);                //追加防御
								set("ap",10);                //追加攻击
								set("cp",10);
//                set("long", "这是一柄四尺来长的古剑，剑鞘上金丝镶着两个字“倚天”。整个剑身隐隐发出一层青气，剑未出鞘，已可见其不凡。\n");
                set("wield_msg", HIY "$N“唰”的一声抽出$n" + HIY + "挽了个剑花，但见寒芒吞吐，电闪星飞。 ....$N不由得从心底升起一股凌云豪气。\n" NOR);
                set("unwield_msg", HIW "倚天剑"HIY"幻作一道白光，「唰」地飞入剑鞘。\n" NOR);
        }
        set("max_lasting",100);
        set("gender","男、女");    //限制性别
        init_sword(2000);
        setup();
}

int move(mixed dest)
{
        if(!objectp(dest) || !userp(dest))       return ::move(dest);
				if(objectp(dest) && userp(dest) && present("dragon blade",dest))
				{
					tell_object(dest,"你刚伸手去捡倚天剑，它却被屠龙刀震飞，甚是可惜。\n");
					::move("/d/city/guangchang");
					return 0;
				}
				if( ::move(dest)==0)    return 0;
//        message("channel:rumor",YEL"【谣言】"HIM"某人：倚天不出，谁与争锋。倚天剑被"+dest->query("name")+"抢到手了！\n"NOR,users());
        return 1;
}

string check_len(string str)
{
	int max_len = 33,len;
	
	len = (max_len+color_len(str)) - strlen(str);
	return sprintf("%"+len+"s","│\n");
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
			case 1  : equip_zl = YEL"中级"NOR; break;
			case 2  : equip_zl = MAG"高级"NOR; break;
			case 3  : equip_zl = HIG"卓越"NOR; break;
			default : equip_zl = HIB"初级"NOR; break;
		}
		
		chars = sprintf("[%s]",equip_zl);
		str = HIY"《地狱玩家服》"NOR"装备属性:";
		/*str += "\n┌──────────────┐\n";

		if(zj) temp_str = sprintf("│%7s+%d%s%s","",zj,name,chars);
		else temp_str = sprintf("│%7s%s%s","",name,chars);
		str += temp_str;
		str += check_len(temp_str);
		str += sprintf("│%28s│\n","");

		if(exp) { temp_str = sprintf("│%7s经验需求: %d","",exp); }
		else { temp_str = sprintf("│%7s经验需求: %s","","无需求"); }
		str += temp_str;
		str += check_len(temp_str);

		if(gender) temp_str = sprintf("│%7s性别需求: %s","",gender);
		else temp_str = sprintf("│%7s性别需求: %s","","无需求");
		str += temp_str;
		str += check_len(temp_str);

		if(level) temp_str = sprintf("│%7s等级需求: %d","",level);
		else temp_str = sprintf("│%7s等级需求: %s","","无需求");
		str += temp_str;
		str += check_len(temp_str);

		temp_str = sprintf("│%7s装备耐久: %d","",lasting);
		str += temp_str;
		str += check_len(temp_str);

		temp_str = sprintf("│%7s装备价值: 无价之宝","");
		str += temp_str;
		str += check_len(temp_str);

		temp_str = sprintf("│%7s装备攻击: %d","",damage);
		str += temp_str;
		str += check_len(temp_str);

		if(hp)
		{
			temp_str = sprintf("│%7s"HIC"气血加成: %d"NOR,"",hp);
			str += temp_str;
			str += check_len(temp_str);
		}
		if(mp)
		{
			temp_str = sprintf("│%7s"YEL"内力加成: %d"NOR,"",mp);
			str += temp_str;
			str += check_len(temp_str);
		}
		if(pp < 0)
		{
			temp_str = sprintf("│%7s减少防御: %d","",pp);
			str += temp_str;
			str += check_len(temp_str);
		}
		else if(pp)
		{
			temp_str = sprintf("│%7s"HIY"追加防御: %d"NOR,"",pp);
			str += temp_str;
			str += check_len(temp_str);
		}
		if(ap||cp)
		{
			temp_str = sprintf("│%7s"HIM"追加攻击: %d(%d)"NOR,"",ap,cp);
			str += temp_str;
			str += check_len(temp_str);
		}
		if(baoji)
		{
			baoji_str = sprintf("%d.%d%d",baoji/100,baoji%100,baoji%10)+"%";
			temp_str = sprintf("│%7s"HIR"装备爆击：%s"NOR,"",baoji_str);
			str += temp_str;
			str += check_len(temp_str);
		}
		if(strs)
		{
			temp_str = sprintf("│%7s"RED"臂力增加: %d"NOR,"",strs);
			str += temp_str;
			str += check_len(temp_str);
		}
		if(dex)
		{
			temp_str = sprintf("│%7s"MAG"身法增加: %d"NOR,"",dex);
			str += temp_str;
			str += check_len(temp_str);
		}
		if(ints)
		{
			temp_str = sprintf("│%7s"CYN"悟性增加: %d"NOR,"",ints);
			str += temp_str;
			str += check_len(temp_str);
		}
		if(cons)
		{
			temp_str = sprintf("│%7s"YEL"根骨增加: %d"NOR,"",cons);
			str += temp_str;
			str += check_len(temp_str);
		}
		if(con)
		{
			temp_str = sprintf("│%7s"HIW"装备数量: %d"NOR,"",con);
			str += temp_str;
			str += check_len(temp_str);
		}
		if(jing)
		{
			temp_str = sprintf("│%7s"HIG"精气加成: %d"NOR,"",jing);
			str += temp_str;
			str += check_len(temp_str);
		}
		if(jingli)
		{
			temp_str = sprintf("│%7s"HIR"精力加成: %d"NOR,"",jingli);
			str += temp_str;
			str += check_len(temp_str);
		}*/
		str += HIY"这是一柄四尺来长的古剑，剑鞘上金\n丝镶着两个字“倚天”。整个剑身隐\n隐发出一层青气，剑未出鞘，已可见\n其不凡。\n"
		"没有装备为武器，无法使用下列功能。\n"
		"[武器技能]半月斩: perform banyue\n"
		"[武器技能]江湖救济: healing id\n"
		"[武器功能]号令天下: xunlian\n"
		"[武器功能]发布武林至尊任务：hljob\n"
		NOR;

		ob->set("long",str);
	}

	if(userp(owner))
	{
				if(present("dragon blade",owner))
				{
					tell_object(owner,"倚天剑被屠龙刀震飞了，甚是可惜。\n");
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

	if(arg == "banyue") //半月崭
	{
		env = environment(me);
		player = all_inventory(env);
		size = sizeof(player);

		if(me->query("neili")<me->query_max_neili())
		{
			tell_object(me,"你内力不满。\n");
			return 1;
		}
		
		if(obj->query("max_lasting") < 10)
		{
			tell_object(me,"耐久度不足，倚天剑的锋利已大不如前。\n");
			return 1;
		}
		
		if(!objectp(env) || env->query("sleep_room") || env->query("no_fight"))
		{
			tell_object(me,"这里不准战斗。\n");
			return 1;
		}
	
		tell_room(env,sprintf(BLINK+HIW"%s使出半月斩，手中倚天剑，剑光暴涨。扫出一道煞白剑气，剑气所到之处"BLINK+HIR"谁与争锋"BLINK+HIW"。\n"NOR,me->name()) );

		for(i=0;i<size;i++)
		{
			if( !objectp(player[i]) || !userp(player[i]) || player[i]->is_npc() || player[i] == me) continue;

			if(blade = present("dragon blade",player[i]))
			{
				tell_room(env,sprintf(BLINK+HIY"%s的屠龙刀爆出一阵白光，将%s的剑气弹了回去，%s躲闪不急，硬是被自己的剑气击成重伤。\n"NOR,player[i]->name(),me->name(),me->name()) );
				index = 1+random(10);
				me->set("eff_qi",index);
				me->set("qi",index);
				me->start_busy(120);
				me->set("neili",0);
				obj->add("max_lasting",-1000);
				tell_object(me,HIR"你招式未尽，吐出一口鲜血，已无还手之力。\n"NOR);
				return 1;
			}
			else if(player[i]->query("age") < 18)
			{
				tell_room(env,sprintf(HIR"倚天剑气从%s头顶掠过，断了几根毫发，幸好没有大碍，还是赶紧离开为妙！\n"NOR,player[i]->name()) );
				continue;
			}
			else
			{
				switch(random(5))
				{
					case 0 : 
						tell_room(env,sprintf(HIR"倚天剑气击中%s胸膛，身体顿时击成碎肉四处飞溅。\n"NOR,player[i]->name()) );
						break;
					case 1 :
						tell_room(env,sprintf(HIR"倚天剑气击中%s头颅，血液随勃颈喷射而出，头颅早已落地。\n"NOR,player[i]->name()) );
						break;
					case 2 :
						tell_room(env,sprintf(HIR"倚天剑气击中%s臂膀，将其从左至右削成两段，煞是恐怖！\n"NOR,player[i]->name()) );
						break;
					case 3 :
						tell_room(env,sprintf(HIR"倚天剑气击中%s下身，整个人往当中断开，血液倾盆。\n"NOR,player[i]->name()) );
						break;
					case 4 :
						tell_room(env,sprintf(HIR"倚天剑气尽数击中%s，只剩一具骷髅站立，隐约可见少许内脏，煞是恐怖！\n"NOR,player[i]->name()) );
						break;
				}
				player[i]->set_temp("die_for","被倚天剑剑气震");
				player[i]->die();
			}
		}
		me->start_busy(60);
		me->set("neili",0);
		obj->add("max_lasting",-1000);
		tell_object(me,HIG"你将半月斩尽数打完，只觉一阵虚脱，暂时无法运功。\n"NOR);
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