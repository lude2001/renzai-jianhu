inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;

	string expend,weaponId;

	mapping tzList = ([
		"金":({ 
			"sword",   //基本剑法
			"blade",   //基本刀法
			"staff",   //基本丈法
			"hammer",  //基本锤法
			"club",	   //基本棍法
			"whip",	   //基本鞭法
		 }),
		"水":({ 
			"force"
		}),
		"木":({ 
			"unarmed", //基本拳脚
			"cuff",	   //基本拳法
			"strike",  //基本掌法
			"finger",  //基本指法
			"hand",	   //基本手法
			"claw",	   //基本爪法
		}),
		"火":({
			"dodge",
		}),
		"土":({
			"parry",
		})
	]);

	
	if (objectp(present(arg,me)))
	{
		string msg;

		if (!objectp(ob = present(arg, me)))
		return notify_fail("你身上没有这样道具啊。\n");

		if (ob->is_weapon() || ob->is_unarmed_weapon())
		return notify_fail("你只能对防具进行祭炼。\n");

		msg = ZJOBLONG"你可以对" + ob->name() + "进行祭炼,元宝祭炼花费180元宝，通宝祭炼花费240通宝。\n";
		msg += ZJOBACTS2"元宝祭炼:item_tz yuanbao " + ob->query("id") + ZJSEP;
		msg += "通宝祭炼:item_tz yuan_bao " + ob->query("id") + "\n";
		write(msg);
		return 1;
		
	}

	if (!arg || sscanf(arg,"%s %s",expend,weaponId) != 2)
		return notify_fail("参数类型不对。\n");

	if (!objectp(ob = present(weaponId, me)))
		return notify_fail("你身上没有这样道具啊。\n");

	if (ob->is_weapon() || ob->is_unarmed_weapon())
		return notify_fail("你只能对防具进行祭炼。\n");

	
	if (expend != "yuanbao" && expend != "yuan_bao")
	return notify_fail("你的参数类型不对。\n");
	
	if (expend == "yuanbao")
	{
		if (me->query(expend) < 180)
		return notify_fail("你的元宝数量不足180,无法完成祭炼。\n");

		me->add(expend,-180);

	}

	if (expend == "yuan_bao")
	{
		if (me->query(expend) < 240)
		return notify_fail("你的通宝数量不足240,无法完成祭炼。\n");

		me->add(expend,-240);
	}



	write(sprintf("你开始运用全身内力以及气血，开始祭炼%s，意图使其威力进一步提升。\n",ob->name()));

	if (random(60) == 1 || me->query("item_tz/uplv") >= 60)
	{
		string type,skill,*types;

		types = keys(tzList);

		type = types[random(sizeof(types))];
		skill = tzList[type][random(sizeof(tzList[type]))];

		ob->set("magic/tz_type/skill",skill);
		ob->set("magic/tz_type/attribute",type);
		ob->delete("item_tz/uplv");
		ob->save();

		write(sprintf("你的%s经过祭炼成功的获得了%s属性-%s。\n",ob->name(),type,to_chinese(skill)));
		return 1;
	}
	else
	{
		me->add("item_tz/uplv",1);
		write(sprintf("很遗憾，%s祭炼失败，前功尽弃了！请再接再厉!\n",ob->name()));
		write(sprintf("当前已经祭炼了%d次。\n",me->query("item_tz/uplv")));
	}

	return 1;
}