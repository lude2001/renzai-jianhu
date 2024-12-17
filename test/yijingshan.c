// Room: /city/beidajie2.c

#define YIJING_D "/adm/daemons/yijingd"

inherit ROOM;
int start_set(string arg);
string set_color(string arg);
int yijing_number(object me);
int same_yijing_number(object me, string type);
int yijing_expend(object me, string yijingName, int self);
int judge_requirement(object me, string type, string yijingName);
int set_yijing_desc(object me, string yijingName, string attackDesc, string dodgeDesc, string msg);
int set_yijing_skill_expend(object me, string yijingName, string type, int expend, string skillType);
int guizhen();
int inform_all(object me);

mapping yj_f_name = (["unarmed":"真意", //基本拳脚
						 "cuff":"拳意", //基本拳法
					   "strike":"掌势", //基本掌法
					   "finger":"指诀", //基本指法
						 "hand":"手诀", //基本手法
						 "claw":"爪势", //基本爪法
						"sword":"剑意", //基本剑法
						"blade":"刀意", //基本刀法
						"staff":"杖诀", //基本杖法
					   "hammer":"锤势", //基本锤法
						 "club":"棍意", //基本棍法
						 "whip":"索意", //基本鞭法
					 "throwing":"暗诀"	//基本暗器
]);

int inform_all(object me)
{
	string msg;
	int number;
	string *colorList = ({ HIR,HIG,HIY, HIB,HIM,HIC, HIW});

	this_object()->add("yj_lw/number", 1);
	number = this_object()->query("yj_lw/number");

	msg =  colorList[random(sizeof(colorList))] + "【意境之巅】--- ";

	if (me->query("family/family_name"))
	{
		switch (number)
		{
		case 1:
			msg += "绵绵岁月悠悠而过.......";
			break;
		case 2:
			msg += CHINESE_D->chinese_date(time(), 1);
			break;
		case 3:
			msg += me->query("family/family_name") + "的祖堂紫气升腾，各大闭关室的弟子猛然运功而起，齐聚祖堂。";
			break;
		case 4:
			msg += me->query("family/master_name") + "居于祖堂正中座，领着众弟子，缓缓退出中堂，于正门出抬头遥望意境之巅处。";
			break;
		case 5:
			msg += "于此同时，江湖众侠无不见五岳之巅紫雷滚滚，齐响雷吟九声。";
			break;
		case 6:
			msg += "天下之最高峰处，一道身影在不断演练武道绝学，细细观之，赫然是天下间威名震古铄今的" + me->query("name") + "，许久过后，其长啸三声，吟之:吾" + me->query("name") + "，今日以" + me->query("age") + "之龄，于意境之巅自悟" + me->query_temp("yj_set/name") + yj_f_name[me->query_temp("yj_set/type")] + ",于此山巅石碑留此意境，岁月漫长，与天下同道共勉之。";
			break;
		case 7:
			msg += me->query("family/family_name") + "境内，逍遥派各弟子齐振奋高呼:贺" + me->query("name") + "师兄得武道真意，威震天下！";
			break;
		case 8:
			msg += me->query("family/master_name") + "言:吾徒......" + me->query("name") + "，你于" + CHINESE_D->chinese_date(me->query("family/enter_time"), 1) + "之时入我" + me->query("family/family_name") + "门下！想不到在我有生之年竟能见你入得武道真意，吾心慰以。";
			break;
		case 9:
			msg += "独孤求败：阁下，今日悟此真意，已然超脱世外，如同鱼入大海，再也不受羁绊了！";
			break;
		case 10:
			msg += "达摩真身：" + me->query("name") + ",我昔日听闻这位小友之名如雷惯耳，今日一见，我真是大感惊叹，当真是为武而生！";
			break;
		case 11:
			msg += "神秘人:数十年不出这等人物了，几近天下无双..........";
			break;
		default:
			this_object()->delete("yj_lw");
			if (!this_object()->query("yj_lw/number"))
			{
		
			message("channel:chat", sprintf(HIY"【意境之巅】%s以%d岁之龄，于%s在意境之巅领悟了%s%s，
			在与漫长的岁月中争斗中，又一位惊世之才领悟了武道一途的真意，五岳之巅齐响雷吟九声，
			彷佛也在惊叹这不可思议的一刻"NOR"。",me->query("name"),me->query("age"),CHINESE_D->chinese_date(time(),1),me->query_temp("yj_set/name"),yj_f_name[me->query_temp("yj_set/type")]),users());
			remove_call_out("inform_all");
			}
			return 1;
		}
	}

	message("story", msg + NOR "\n", users());
	call_out("inform_all",5,me);
	return 1;
}

void create()
{
	set("short", "意境之巅");
	set("long", "这里是意境之巅，自古以来无数走上武道之巅无敌天才都在此处留下属于自己的传说。");
	set("outdoors", "city");
	set("item_desc", (["【石碑】":"这是一座石碑，蕴含了武道意境的奥秘。\n" ZJOBACTS2 "查看:setyj"ZJSEP"归真:gz\n",
	]));
	// set("exits", (["south":__DIR__ "enter",
	// ]));
	// set("out_room", "/d/city/wumiao");
	setup();
}


void init()
{
	add_action("start_set", "setyj");
	add_action("start_wu", "startwu");
	add_action("guizhen", "gz");
}

// 设定意境名称 攻击描述 闪避描述 意境技能消耗 意境类型
int start_set(string arg)
{
	object me = this_player();

	mixed setType, setMsg;
	if (!arg)
	{
		string msg;
		msg = ZJOBLONG "请设定你意境信息\n";
		msg += "意境名称:" + (me->query_temp("yj_set/name") ? me->query_temp("yj_set/name") : "无") + "\n";
		msg += "意境背景描述:" + (me->query_temp("yj_set/msg") ? me->query_temp("yj_set/msg") : "无") + "\n";
		msg += "意境攻击描述:" + (me->query_temp("yj_set/attack_desc") ? me->query_temp("yj_set/attack_desc") : "无") + "\n";
		msg += "意境闪避描述:" + (me->query_temp("yj_set/dodge_desc") ? me->query_temp("yj_set/dodge_desc") : "无") + "\n";
		msg += "意境消耗等级:" + (me->query_temp("yj_set/expend") ? me->query_temp("yj_set/expend") : "无") + "\n";
		msg += "技能类型:" + (me->query_temp("yj_set/skill") ? me->query_temp("yj_set/skill") : "无") + "\n";
		msg += "意境类型:" + (me->query_temp("yj_set/type") ? yj_f_name[me->query_temp("yj_set/type")] : "无") + "\n";

		msg = replace_string(msg, "\n", ZJBR);
		msg += "\n" ZJOBACTS2;
		msg += "设定名称:setyj set name" ZJSEP;
		msg += "设定攻击描述:setyj set attack_desc" ZJSEP;
		msg += "设定闪避描述:setyj set dodge_desc" ZJSEP;
		msg += "设定背景描述:setyj set msg" ZJSEP;
		msg += "设定消耗:setyj set expend" ZJSEP;
		msg += "设定技能类型:setyj set skill" ZJSEP;
		msg += "设定意境类型:setyj set type" ZJSEP;
		msg += "开始领悟意境:startwu\n";
		tell_object(me, msg);
		return 1;
	}

	if (sscanf(arg, "%s %s", setType, setMsg) == 2)
	{
		string msg;
		string *s1 = ({
			"unarmed", //基本拳脚
			"cuff",	   //基本拳法
			"strike",  //基本掌法
			"finger",  //基本指法
			"hand",	   //基本手法
			"claw",	   //基本爪法
			"sword",   //基本剑法
			"blade",   //基本刀法
			"staff",   //基本丈法
			"hammer",  //基本锤法
			"club",	   //基本棍法
			"whip",	   //基本鞭法
		});

		setMsg = replace_string(setMsg, " ", "");
		setMsg = replace_string(setMsg, "\"", "`");
		setMsg = replace_string(setMsg, "\\n", ZJBR);
		setMsg = replace_string(setMsg, "\n", ZJBR);
		setMsg = replace_string(setMsg, "$n", "");

		if (setType == "set")
		{
			if (setMsg == "name")
			{
				msg = "请设定你的意境名称，例如设定名称为苍天，类型为剑，最终就是苍天剑意。";
				msg = INPUTTXT(msg, "setyj name $txt#") + "\n";
				tell_object(me, msg);
				return 1;
			}

			if (setMsg == "attack_desc")
			{
				msg = "请设定你的攻击描述,可以使用颜色字符，例如 $HIR$为红色。$target_name$代表敌方的名字，$my_name$代表自己的名字，如果是兵器类型的意境,$weapon_name$代表自己兵器的名字。,英文斜杠+n代表换行";
				msg = INPUTTXT(msg, "setyj attack_desc $txt#") + "\n";
				tell_object(me, msg);
				return 1;
			}

			if (setMsg == "dodge_desc")
			{
				msg = "请设定你的躲闪描述,可以使用颜色字符，例如 $HIR$为红色。$target_name$代表敌方的名字，$my_name$代表自己的名字。,英文斜杠+n代表换行";
				msg = INPUTTXT(msg, "setyj dodge_desc $txt#") + "\n";
				tell_object(me, msg);
				return 1;
			}

			if (setMsg == "msg")
			{
				msg = "请设定你的意境背景描述,可以使用颜色字符，例如 $HIR$为红色。背景你可以设定包括来源，创建灵感等信息，英文斜杠+n代表换行";
				msg = INPUTTXT(msg, "setyj msg $txt#") + "\n";
				tell_object(me, msg);
				return 1;
			}

			if (setMsg == "expend")
			{
				msg = "请设定你的消耗等级（6 - 18）对应600-1800的内力消耗，6-18秒的cd。意境可以自定义消耗，内力和cd，随着付出的代价不同，可以造成的效果不同。分为四种类型，连招（6 -18），单招伤害（有效等级 *（6 - 18） / 4， 单体恢复（有效等级 * （6 - 18） / 8的气血，再恢复这个值一半的精神，即 / 4。） ";
				msg = INPUTTXT(msg, "setyj expend $txt#") + "\n";
				tell_object(me, msg);
				return 1;
			}

			if (setMsg == "type")
			{

				msg = ZJOBLONG "请设定你的意境类型。\n" ZJOBACTS2;

				foreach (string skill_id in s1)
				{
					msg += replace_string(to_chinese(skill_id), "基本", "") + ":setyj type " + skill_id + ZJSEP;
				}

				msg += "返回:setyj\n";

				tell_object(me, msg);
				return 1;
			}

			if (setMsg == "skill")
			{

				msg = ZJOBLONG "请设定你的技能类型。请注意，意境单招均是真伤，所以pvp比较强势，连招则比较均衡，使用意境单招用来打pve评估意境单招强度是一个非常愚蠢的行为，所以请理性选择意境技能。\n" ZJOBACTS2;

				msg += "连招:setyj skill 连招" ZJSEP;
				msg += "单招伤害:setyj skill 单招伤害" ZJSEP;
				msg += "单招恢复:setyj skill 单招恢复" ZJSEP;

				msg += "返回:setyj\n";

				tell_object(me, msg);
				return 1;
			}

			return 1;
		}

		if (setType == "name")
		{
			if ((strlen(setMsg) < 2) || (strlen(setMsg) > 4))
			{
				tell_object(me, "对不起，你的意境名称不能太长或太短。\n");
				return 1;
			}

			if (!is_chinese(setMsg))
			{
				tell_object(me, "对不起，请你用「中文」取意境名称。\n");
				return 1;
			}

			if (!me->query_temp("yj_set/type"))
			{
				tell_object(me, "你需要先选定意境类型才能设定意境名称。\n");
				return 1;
			}

			if (YIJING_D->check_yj_name_is_repetition(setMsg, me->query_temp("yj_set/type")))
			{
				tell_object(me, "对不起，意境之巅已经有这个意境名称了（相同类型，相同名称不能重复，但是不同类型，相同名称可以设定 ，例如苍天剑意和苍天刀意就是不同的类型相同名称，可以设定），你不能使用和别人一样的意境名称。\n");
				return 1;
			}

			me->set_temp("yj_set/name", setMsg);
			tell_object(me, sprintf("你设定%s为你的意境名称。\n", setMsg));

			return 1;
		}

		if (setType == "attack_desc")
		{
			if ((strlen(setMsg) < 2) || (strlen(setMsg) > 400))
			{
				tell_object(me, "对不起，你的意境描述不能太长或太短（1-200字）。\n");
				return 1;
			}

			setMsg = set_color(setMsg);

			me->set_temp("yj_set/attack_desc", setMsg);
			tell_object(me, sprintf("你设定：%s为你的意境攻击描述。\n", setMsg));
			return 1;
		}

		if (setType == "dodge_desc")
		{
			if ((strlen(setMsg) < 2) || (strlen(setMsg) > 400))
			{
				tell_object(me, "对不起，你的意境描述不能太长或太短（1-200字）。\n");
				return 1;
			}

			setMsg = set_color(setMsg);

			me->set_temp("yj_set/dodge_desc", setMsg);
			tell_object(me, sprintf("你设定：%s为你的意境躲闪描述。\n", setMsg));
			return 1;
		}

		if (setType == "msg")
		{
			if ((strlen(setMsg) < 2) || (strlen(setMsg) > 600))
			{
				tell_object(me, "对不起，你的意境描述不能太长或太短（1-300字）。\n");
				return 1;
			}

			setMsg = set_color(setMsg);

			me->set_temp("yj_set/msg", setMsg);
			tell_object(me, sprintf("你设定：%s为你的意境背景描述。\n", setMsg));
			return 1;
		}

		if (setType == "type")
		{

			if (member_array(setMsg, s1) == -1)
			{
				tell_object(me, "没有这种类型的武艺可以用来领悟意境。\n");
				return 1;
			}

			me->set_temp("yj_set/type", setMsg);
			tell_object(me, sprintf("你决定以%s为扩展的所有该类型的武学来领悟意境。", to_chinese(setMsg)));
			return 1;
		}

		if (setType == "skill")
		{
			string *skillTypeList = ({"连招", "单招伤害", "单招恢复"});

			if (member_array(setMsg, skillTypeList) == -1)
			{
				tell_object(me, "没有这种类型的意境技能可以用来领悟意境。\n");
				return 1;
			}

			me->set_temp("yj_set/skill", setMsg);
			tell_object(me, sprintf("你决定以%s为该意境的技能类型。", to_chinese(setMsg)));
			return 1;
		}

		if (setType == "expend")
		{

			setMsg = to_int(setMsg);

			if (setMsg < 6 || setMsg > 18)
			{
				tell_object(me, "意境消耗等级的范围为6-18，请不要超出消耗等级的范围。\n");
				return 1;
			}

			me->set_temp("yj_set/expend", setMsg);

			tell_object(me, sprintf("你设定的意境消耗等级为%d。\n", setMsg));
			return 1;
		}
	}
	else
	{
		tell_object(me, "格式不正确你无法使用这种格式。\n");
		return 1;
	}

	return 1;
}

int start_wu()
{
	object me = this_player();

	if (this_object()->query("yj_lw"))
		return notify_fail("有武道之友正在山巅演练领悟意境，你还是再等等吧！\n");

	if (!me->query_temp("yj_set/name") || !me->query_temp("yj_set/attack_desc") || !me->query_temp("yj_set/msg") || !me->query_temp("yj_set/dodge_desc") || !me->query_temp("yj_set/type") || !me->query_temp("yj_set/expend") || !me->query_temp("yj_set/skill"))
		return notify_fail("你的意境信息不完整，包括名称，背景描述,攻击描述，躲闪描述，意境类型，意境消耗,技能类型。\n");

	if (!judge_requirement(me, me->query_temp("yj_set/type"), me->query_temp("yj_set/name")))
		return 1;

	if (!yijing_expend(me, me->query_temp("yj_set/name"), 1))
		return 1;

	set_yijing_desc(me, me->query_temp("yj_set/name"), me->query_temp("yj_set/attack_desc"), me->query_temp("yj_set/dodge_desc"), me->query_temp("yj_set/msg"));
	set_yijing_skill_expend(me, me->query_temp("yj_set/name"), me->query_temp("yj_set/type"), me->query_temp("yj_set/expend"), me->query_temp("yj_set/skill"));

	me->set("yijing/" + me->query_temp("yj_set/name") + "/time", time());
	me->set("yijing/" + me->query_temp("yj_set/name") + "/family", me->query("family"));
	me->set("yijing/" + me->query_temp("yj_set/name") + "/age", me->query("age"));

	//每次领悟都需要记录一下加成的等级
	me->add("yijing/skill_add/" + me->query_temp("yj_set/type"), 100);
	YIJING_D->set_data(me);
	inform_all(me);

	log_file("guizhen", ctime(time()) + sprintf("%s领悟了%s%s,一共有%d种意境。",me->query("name"),me->query_temp("yj_set/name"),yj_f_name[me->query_temp("yj_set/type")],yijing_number(me)));
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

//用于计算所有意境的数量
int yijing_number(object me)
{
	if (!me->query("yijing_list"))
		return 0;

	return sizeof(keys(me->query("yijing_list")));
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

// 用于计算意境的消耗
// 传入的参数：self参数代表是自我领悟还是领悟他人的，1代表自我领悟
// 2代表领悟他人，显然的，领悟他人的意境消耗是减半的，显然所有的计算公式应该在方法的内部进行处理，一个方法处理一个事情。
// 返回值为1成功，返回为0则代表失败，调用此方法的时候需要判断返回值。
int yijing_expend(object me, string yijingName, int self)
{
	int expendPotential, expendNeili;
	int level, possessPotential;

	level = yijing_number(me);
	expendNeili = 3000 * (level + 1) * (level + 1);

	expendPotential = 4000000 * (level + 1) * (level + 1);
	possessPotential = me->query("potential") - me->query("learned_points");

	//领悟他人的意境消耗减半
	if (self == 2)
	{
		expendNeili /= 2;
		expendPotential /= 2;
	}

	if (me->query("max_neili") < expendNeili)
	{
		tell_object(me, "你的最大内力不足" + expendNeili + ",请向先补充最大内力。\n");
		return 0;
	}

	if (possessPotential < expendPotential)
	{
		tell_object(me, "你的潜能不足" + expendPotential + ",请先补充潜能。\n");
		return 0;
	}

	me->add("potential", -expendPotential);
	me->add("max_neili", -expendNeili);

	if (self == 2)
		me->set("yijing/" + yijingName + "/self", 1); //代表着这个意境是自己领悟的

	return 1;
}

// 返回值为1满足需求，返回值为0不满足需求
int judge_requirement(object me, string type, string yijingName)
{
	int basicForce, baisicDodge, basicParry, basicType;
	int specialForce, specialDodge, specialParry, specialType;
	int level, needLevel;

	basicForce = me->query_skill("force", 1);
	baisicDodge = me->query_skill("dodge", 1);
	basicParry = me->query_skill("parry", 1);
	basicType = me->query_skill(type, 1);

	specialForce = me->query_skill(me->query_skill_mapped("force"), 1);
	specialDodge = me->query_skill(me->query_skill_mapped("dodge"), 1);
	specialParry = me->query_skill(me->query_skill_mapped("parry"), 1);
	specialType = me->query_skill(me->query_skill_mapped(type), 1);

	level = yijing_number(me);

	needLevel = 650 + level * level * 100;

	if (!specialForce || !specialDodge || !specialParry || !specialType)
	{
		tell_object(me, "请先将你需要特殊技能激发再进行领悟意境。\n");
		return 0;
	}

	if (me->query("myspecial/b" + type + "level") + 1 < same_yijing_number(me, type))
	{
		tell_object(me, "你的天赋等级不够，不足以领悟如此之多的意境。\n");
		return 0;
	}

	if (me->query_skill("martial-cognize") < 500)
	{
		tell_object(me, "你的武学修养等级不够，不能领悟意境。\n");
		return 0;
	}

	if (basicForce < needLevel)
	{
		tell_object(me, sprintf("%s修为(需求%d)不够,不可强行领悟意境。\n", to_chinese("force"), needLevel));
		return 0;
	}

	if (baisicDodge < needLevel)
	{
		tell_object(me, sprintf("%s修为(需求%d)不够,不可强行领悟意境。\n", to_chinese("dodge"), needLevel));
		return 0;
	}

	if (basicParry < needLevel)
	{
		tell_object(me, sprintf("%s修为(需求%d)不够,不可强行领悟意境。\n", to_chinese("parry"), needLevel));
		return 0;
	}

	if (basicType < needLevel)
	{
		tell_object(me, sprintf("%s修为(需求%d)不够,不可强行领悟意境。\n", to_chinese(type), needLevel));
		return 0;
	}

	if (specialForce < needLevel)
	{
		tell_object(me, sprintf("%s修为(需求%d)不够,不可强行领悟意境。\n", to_chinese(me->query_skill_mapped("force")), needLevel));
		return 0;
	}

	if (specialDodge < needLevel)
	{
		tell_object(me, sprintf("%s修为(需求%d)不够,不可强行领悟意境。\n", to_chinese(me->query_skill_mapped("dodge")), needLevel));
		return 0;
	}

	if (specialParry < needLevel)
	{
		tell_object(me, sprintf("%s修为(需求%d)不够,不可强行领悟意境。\n", to_chinese(me->query_skill_mapped("parry")), needLevel));
		return 0;
	}

	if (specialType < needLevel)
	{
		tell_object(me, sprintf("%s修为(需求%d)不够,不可强行领悟意境。\n", to_chinese(me->query_skill_mapped(type)), needLevel));
		return 0;
	}

	return 1;
}

// 用于设定一个意境的攻击描述以及躲闪描述。
int set_yijing_desc(object me, string yijingName, string attackDesc, string dodgeDesc, string msg)
{
	me->set("yijing_list/" + yijingName, 1); //加入意境列表当中
	me->set("yijing/" + yijingName + "/attack_desc", attackDesc);
	me->set("yijing/" + yijingName + "/dodge_desc", dodgeDesc);
	me->set("yijing/" + yijingName + "/msg", msg);
	return 1;
}

// type 即可以选择的意境类型，expend为 6- 18. 对应cd:(6 -18) /2 秒，内力消耗 150 * （6 - 18）
int set_yijing_skill_expend(object me, string yijingName, string type, int expend, string skillType)
{
	me->set("yijing/" + yijingName + "/type", type);
	me->set("yijing/" + yijingName + "/expend", expend);
	me->set("yijing/" + yijingName + "/skill", skillType);
	return 1;
}

int guizhen()
{
	object me = this_player();

	int guizhenNumber;

	guizhenNumber = me->query("guizhen/number");

	if (guizhenNumber >= yijing_number(me))
	{
		tell_object(me, sprintf("一个意境对应一次归真，你目前有%d个意境，进行了%d次归真。\n", yijing_number(me), guizhenNumber));
		return 0;
	}

	me->add("guizhen/number", 1);
	me->set("guizhen/" + me->query("guizhen/number") + "/time", time()); //记录每一次归真的时间戳。
	me->add("yijing/other_add/qi", 10000 * me->query("guizhen/number")); //每次额外增加玩家1w * 归真次数点气血。
	me->add("tianfu_point",10);

	CHAR_D->setup_char(me);
	if (me->query("family/master_name"))
	message("channel:chat", HIG"【"+ me->query("family/family_name") + "】:"+ me->query("family/master_name") + "：吾徒" +  me->query("name") + "，今日你既已归真，我即送鱼入海，免受羁绊。\n",users());
	message("channel:chat", HIG"【意境之巅】:" + me->query("name") + "完成了第" + me->query("guizhen/number") + "次意境归真。\n",users());
	tell_object(me,sprintf("你进行了第%d次归真,增加10000的血量，获得了10点可分配天赋点,并清空门派信息，可以重新选择一个门派拜师。\n",me->query("guizhen/number")));
	me->delete("family");
	log_file("guizhen", ctime(time()) + sprintf("---%s(%s)进行了第%d次归真。\n", me->query("name"), me->query("id"), me->query("guizhen/number")));
	return 1;
}