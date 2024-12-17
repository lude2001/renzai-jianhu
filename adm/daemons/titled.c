// 称号demo by 潇湘夜雨(baiyi666/lude)
#pragma optimize
#pragma save_binary

#include <ansi.h>
//可加成基本属性值
mapping titles = ([
"天问":(["int":5,"per":5,"obtain":"龙舟贡献达到30，需求女性","sm":"众女嫉余之蛾眉兮"]),
"离骚":(["int":5,"per":5,"obtain":"龙舟贡献达到30，需求男性","sm":"虽九死其犹未悔"]),
"七夕大使":(["int":5,"str":5,"obtain":"七夕点达到100","sm":"两情若是久长时,又岂在朝朝暮暮。"]),
"天籁之音":(["int":7,"dex":3,"obtain":"参加天籁之音比赛","sm":"两情若是久长时,又岂在朝朝暮暮。"]),
"龙象之力":(["str":5,"con":3,"max_qi":2000,"weiwang":300000,"obtain":"龙般若相功达到500级，消耗300000威望"]),
"雪山飞狐":(["str":2,"int":2,"con":2,"dex":2,"max_qi":1000,"weiwang":300000,"obtain":"胡家刀法和冷月神功达到500级，消耗300000威望"]),
"普度众生":(["str":1,"int":2,"con":3,"dex":1,"max_qi":3000,"weiwang":300000,"obtain":"回风拂柳剑达到500级，消耗300000威望","sm":"菩提本无树，明镜亦非台，本来无一物，何处染尘埃。"]),
"剑魔":(["str":2,"int":2,"con":2,"dex":2,"max_qi":1000,"weiwang":300000,"obtain":"独孤九剑达到500级，消耗300000威望","sm":"呜呼！群雄束手长剑空利，生平求一敌手而不可得，诚寂寥难堪也。"]),
"碧海潮生":(["str":3,"int":2,"con":3,"dex":2,"max_qi":2000,"weiwang":300000,"obtain":"碧波神功和玉箫剑法达到500级，碧海潮生曲达到300级，消耗300000威望"]),
"北冥潇":(["str":3,"int":2,"con":3,"dex":2,"max_qi":2000,"weiwang":400000,"obtain":"北冥神功和凌波微步和六阳掌达到500级，消耗400000威望"]),
"太极":(["str":3,"int":2,"con":3,"dex":2,"max_qi":2000,"weiwang":400000,"obtain":"太极神功和太极拳和太极剑达到500级，消耗400000威望","sm":"两仪四象寓天风，八卦三阶引量功。\n圣祖伏羲察宇宙，太极陈氏演神衷。\n连绵力载千江水，起落音谐万壑松。\n宛转乾坤随易理，心经道法自然通。\n"]),
"南慕容":(["str":2,"int":2,"con":2,"dex":2,"max_qi":1000,"weiwang":300000,"obtain":"斗转星移达到500级，消耗300000威望"]),
"阳圣":(["str":2,"int":3,"con":3,"dex":2,"max_qi":1000,"weiwang":300000,"obtain":"九阳神功和乾坤大挪移达到500级，消耗300000威望"]),
//"为民除害":(["str":1,"int":1,"con":1,"dex":1,"obtain":"衙门贡献达到1000"]),
"地狱之客":(["str":2,"int":2,"con":2,"dex":2,"obtain":"死亡次数一百次，并且经过一次肉身重修","sm":"地狱是我的后花园！"]),
"百岁老人":(["int":6,"obtain":"年龄达到100岁","sm":"老来要洒脱，洒脱不是放弃，而是放下。"]),
//"琉璃金身":(["str":3,"int":3,"con":3,"dex":3,"weiwang":500000,"obtain":"肉身达到第五级：不死不灭，消耗50万威望。"]),
"武者":(["str":1,"int":1,"con":1,"dex":1,"obtain":"基本内功达到200","sm":"武者即习武之人，修其心志，养其气息，练其肌体，升其精魂。"]),
"陌上君子":(["str":2,"int":2,"con":2,"dex":2,"obtain":"容貌＞50，男性消耗300000威望获得","weiwang":300000,"sm":"宗之潇洒美少年，举觞白眼望青天，皎如玉树临风前。"]),
"杀神":(["str":5,"int":5,"con":5,"dex":5,"max_qi":8000,"max_neili":8000,"obtain":"杀人数超过100万，消耗1000000威望获得","weiwang":1000000,"sm":"屠一是罪，屠万是雄，屠得上百万，方为雄中雄！"]),
"侠客行":(["str":2,"int":2,"con":2,"dex":2,"max_qi":1000,"weiwang":300000,"obtain":"太玄功达到500级，消耗300000威望。","sm":"赵客缦胡缨，吴钩霜雪明;\n银鞍照白马，飒沓如流星;\n十步杀一人，千里不留行;\n事了拂衣去，深藏身与名;\n闲过信陵饮，脱剑膝前横;\n将炙啖朱亥，持觞劝侯嬴;\n三杯吐然诺，五岳倒为轻;\n眼花耳热后，意气素霓生;\n救赵挥金槌，邯郸先震惊;\n千秋二壮士，烜赫大梁城;\n纵死侠骨香，不惭世上英;\n谁能书阁下，白首太玄经。\n"]),
"奢华贵族":(["str":3,"int":3,"con":3,"dex":3,"obtain":"vip等级＞5，消耗200000威望获得","weiwang":200000]),
"倾城倾国":(["str":2,"int":2,"con":2,"dex":2,"obtain":"容貌＞50，女性消耗300000威望获得","weiwang":300000,"sm":"北方有佳人。绝世而独立。一顾倾人城。再顾倾人国。宁不知倾城与倾国。佳人难再得。"]),
"富可敌国":(["str":3,"int":3,"con":3,"dex":3,"obtain":"元宝数大于66666，消耗300000威望获得","weiwang":300000]),
//"侠行天下":(["str":5,"int":5,"con":5,"dex":5,"max_qi":5000,"max_neili":10000,"baoji":10,"yanjiuc":500,"obtain":"肉身重修5次圆满，消耗1000000威望获得","weiwang":1000000,"sm":"侠者，当行遍天下，斩尽不平，杀尽不公，战尽群雄！"]),
"独步江湖":(["str":5,"int":5,"con":5,"dex":5,"max_qi":8000,"max_neili":3000,"baoji":5,"yanjiuc":500,"obtain":"武学修养和剑道修养达到500级，消耗1000000威望获得","weiwang":1000000,"sm":"武道路漫漫,登顶何其难?\n修得武中道, 方为天下尊。"]),
"盖世齐天":(["str":10,"int":10,"con":10,"dex":10,"max_qi":10000,"max_neili":10000,"baoji":20,"yanjiuc":1000,"xixue":20,"obtain":"先天全属性100，消耗5000000威望获得","weiwang":5000000,"sm":"力拔山兮气盖世。\n时不利兮骓不逝。\n骓不逝兮可奈何！\n虞兮虞兮奈若何！"]),
//"古月太素":(["str":3,"int":2,"con":2,"dex":2,"max_qi":2000,"max_neili":2000,"weiwang":500000,"obtain":"古墓派太素四套武功达到500级，消耗500000威望获得"]),
//"暗夜鬼魅":(["str":3,"int":2,"con":2,"dex":2,"max_qi":2000,"max_neili":2000,"weiwang":500000,"obtain":"暗夜鬼魅典达到500级，消耗500000威望获得"]),
//"天人合一":(["int":4,"con":4,"max_qi":2000,"max_neili":2000,"weiwang":500000,"obtain":"九阴九阳达到500级，消耗500000威望获得"]),
]);
//转换为中文名称
mapping chinesename=([
"str":"臂力",
"int":"悟性",
"con":"根骨",
"age":"年龄",
"dex":"身法",
"max_jing":"精神上限",
"max_jingli":"精力上限",
"max_qi":"气血上限",
"max_neili":"内力上限",
"yanjiux":"研究效率",
"yanjiuc":"研究次数",
"baoji":"暴击率",
"baojixg":"暴击效果",
"xixue":"吸血率",
"weiwang":"需要威望",
"sm":"称号说明",
"bodyreset":"重修次数",
"blevel":"肉身等级",
"per":"容貌",
"zjvip/level":"vip等级",
"yuanbao":"元宝",
"qiangdaotask":"衙门贡献",
"gender":"性别",
"combat/MKS":"杀人数",
"combat/dietimes":"死亡次数",
"obtain":HIR"获取方式"NOR,
"jieri/duanwu/pot":"龙舟贡献",
"qixi_dian":"七夕点",
"hsy_bs":"好声音参赛者"
]);

//需要达标的属性值
mapping need_attribute=([
"侠行天下":(["bodyreset":5]),
"天籁之音":(["hsy_bs":1]),
"盖世齐天":(["str":100,"con":100,"int":100,"dex":100]),
"琉璃金身":(["blevel":5]),
"杀神":(["combat/MKS":1000000]),
"倾城倾国":(["per":50,"gender":"女性"]),
"陌上君子":(["per":50,"gender":"男性"]),
"奢华贵族":(["cxpay/gongxian":5]),
"富可敌国":(["yuanbao":66666]),
"百岁老人":(["age":100]),
"天问":(["jieri/duanwu/pot":30]),
"离骚":(["jieri/duanwu/pot":30]),
"七夕大使":(["qixi_dian":100]),
"地狱之客":(["combat/dietimes":100,"bodyreset":1]),
"为民除害":(["qiangdaotask":1000]),
]);

//需要达标的技能
mapping need_skill=([
"剑魔":(["lonely-sword":500]),
"普渡众生":(["huifeng-jian":500]),
"武者":(["force":200]),
"阳圣":(["jiuyang-shengong":500,"qiankun-danuoyi":500]),
"独步江湖":(["martial-cognize":500,"sword-cognize":500]),
"碧海潮生":(["bibo-shengong":500,"yuxiao-jian":500,"bihai-chaosheng":300]),
"北冥潇":(["beiming-shengong":500,"lingbo-weibu":500,"liuyang-zhang":500]),
"南慕容":(["douzhuan-xingyi":500]),
"侠客行":(["taixuan-gong":500]),
"太极":(["taiji-shengong":500,"taiji-quan":500,"taiji-jian":500]),
"暗夜鬼魅":(["anye-guimeidian":500]),
"龙象之力":(["longxiang":500]),
"古月太素":(["taisu-force":500,"taisu-dodge":500,"taisu-moon":500,"taisu-jian":500]),
"雪山飞狐":(["lengyue-shengong":500,"hujia-daofa":500]),
"天人合一":(["jiuyin-jiuyang":500]),
]);
void create() { seteuid(getuid()); }

int use_title(object me,string title)
{
mixed xg=titles[title];
string *att,at;
att=keys(xg);
me->delete("titlea");
   foreach (at in att)
   {
     if (intp(xg[at]))
     me->set("titlea/"+at,xg[at]);
  }
me->set("chenghao",title);
tell_object(me,HIR"你佩戴了称号："HIC+title+NOR+"\n");
	return 1;
}


string query_title(object me,string title)
{
string msg,msgg;
mixed xg=titles[title];
    if (xg)
{
msg=chinesename["obtain"]+":"+xg["obtain"]+"\n";
msg+=HIC+NOR+ZJBR"==================称号加成==================\n";
if (xg["sm"])
msg+=chinesename["sm"]+":\n"+xg["sm"]+"\n";
foreach (msgg in keys(xg))
if (intp(xg[msgg]))
msg+=HIY"("+chinesename[msgg]+")"NOR+HIW":"+xg[msgg]+NOR"\n";
/*if (xg=need_attribute[title])
{
msg+=HIC+NOR+ZJBR"——————————称号需求——————————————"+ZJBR;
foreach (msgg in keys(xg))
if (xg[msgg])
msg+=HIY"("+chinesename[msgg]+")"NOR+HIW":"+xg[msgg]+NOR"\n";
}*/
       }
else
msg="该称号无任何加成\n";
	return msg;
}

mapping alltitles()
{
return titles;
}
//购买称号处理
int buy_title(object me,string title)
{
string att,*allatt;
mapping attribute;
//先计算属性是否达标
         if (me->query("titles/"+title))
        {
         tell_object(me,"你已获得该称号。\n");
         return 1;
         }
         
    if (need_attribute[title])
   {
   		allatt=keys(need_attribute[title]);
		attribute=need_attribute[title];
        foreach (att in allatt)
         if (me->query(att) < attribute[att])
         {
         tell_object(me,"你的"+chinesename[att]+"未达标。\n");
         return 1;
         }
  
   }
//再计算技能是否达标
   if (need_skill[title])
   {
   allatt=keys(need_skill[title]);
attribute=need_skill[title];
       foreach (att in allatt)
         if (me->query_skill(att,1) < attribute[att])
         {
         tell_object(me,"你的"+to_chinese(att)+"低于"+chinese_number(attribute[att])+"级，未达标。\n");
         return 1;
         }
       
   }
 //最后计算威望是否足够
 attribute=titles[title];
           if (me->query("weiwang")<attribute["weiwang"])
        {
         tell_object(me,"你的威望不够。\n");
         return 1;
         }
 me->add("potential",attribute["weiwang"]/10);
 if (attribute["weiwang"])
 //me->add("yuanbao",100);
 me->add("weiwang",-attribute["weiwang"]);
 me->set("titles/"+title,1);
 if (titles[title]["sm"])
 message("channel:chat",HBYEL+HIR"［"+title+"］"NOR"："+me->query("name")+"："+replace_string(titles[title]["sm"],"\n"," ")+"\n"NOR,users());
 tell_object(me,"恭喜你获得称号"+HIR+title+"\n"NOR);
 return 1;
}