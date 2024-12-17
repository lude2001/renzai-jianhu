// made by lks;


inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }


int valid_learn(object me)
{
    mapping skl;
    string *sname;
    int i;
    int lvl = (int)me->query_skill("hx-jing", 1);
    if ( me->query("gender") == "无性" && lvl > 49)
        return notify_fail("你无根无性，阴阳不调，难以领会高深的欢喜转轮经。\n");

	 if ( me->query("class") == "bonze" )
        return notify_fail("欢喜转轮经讲究杀气御敌，有违佛家之意，"+RANK_D->query_respect(me)+"欲修此功，已是罪过。\n");

	 if( (int)me->query_skill("hx-jing", 1) > 30 )
		return notify_fail("欢喜转轮经只能通过领悟来提高。\n");

	if (me->query_skill("force",1)<=lvl)
        return notify_fail("你的基本内功火候还不够，无法领会欢喜转轮经。\n");
    
	skl = me->query_skills();
    
	sname  = keys(skl);
    
// 	for (i=0;i<sizeof(skl);i++){
// 		if (sname[i]=="huaxue-dafa") continue;
// 		if (sname[i]=="yiqiguan-riyue") continue;
// 		if (sname[i]=="hx-jing") continue;
// 		if( SKILL_D(sname[i])->valid_enable("force") )
//         return notify_fail("你不先散了别派内功，怎能学欢喜转轮经？\n");
//     }

    return 1;
}


int practice_skill(object me)
{
        return notify_fail("欢喜转轮经不能通过练习来增加熟练度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"hx-jing/" + func;
}

