// �ƺ�demo by ����ҹ��(baiyi666/lude)
#pragma optimize
#pragma save_binary

#include <ansi.h>
//�ɼӳɻ�������ֵ
mapping titles = ([
"����":(["int":5,"per":5,"obtain":"���۹��״ﵽ30������Ů��","sm":"��Ů����֮��ü��"]),
"��ɧ":(["int":5,"per":5,"obtain":"���۹��״ﵽ30����������","sm":"���������δ��"]),
"��Ϧ��ʹ":(["int":5,"str":5,"obtain":"��Ϧ��ﵽ100","sm":"�������Ǿó�ʱ,�����ڳ���ĺĺ��"]),
"����֮��":(["int":7,"dex":3,"obtain":"�μ�����֮������","sm":"�������Ǿó�ʱ,�����ڳ���ĺĺ��"]),
"����֮��":(["str":5,"con":3,"max_qi":2000,"weiwang":300000,"obtain":"�������๦�ﵽ500��������300000����"]),
"ѩɽ�ɺ�":(["str":2,"int":2,"con":2,"dex":2,"max_qi":1000,"weiwang":300000,"obtain":"���ҵ����������񹦴ﵽ500��������300000����"]),
"�ն�����":(["str":1,"int":2,"con":3,"dex":1,"max_qi":3000,"weiwang":300000,"obtain":"�ط�������ﵽ500��������300000����","sm":"���᱾�������������̨��������һ��δ�Ⱦ������"]),
"��ħ":(["str":2,"int":2,"con":2,"dex":2,"max_qi":1000,"weiwang":300000,"obtain":"���¾Ž��ﵽ500��������300000����","sm":"�غ���Ⱥ�����ֳ�����������ƽ��һ���ֶ����ɵã��ϼ����ѿ�Ҳ��"]),
"�̺�����":(["str":3,"int":2,"con":3,"dex":2,"max_qi":2000,"weiwang":300000,"obtain":"�̲��񹦺����｣���ﵽ500�����̺��������ﵽ300��������300000����"]),
"��ڤ��":(["str":3,"int":2,"con":3,"dex":2,"max_qi":2000,"weiwang":400000,"obtain":"��ڤ�񹦺��貨΢���������ƴﵽ500��������400000����"]),
"̫��":(["str":3,"int":2,"con":3,"dex":2,"max_qi":2000,"weiwang":400000,"obtain":"̫���񹦺�̫��ȭ��̫�����ﵽ500��������400000����","sm":"��������Ԣ��磬����������������\nʥ����˲����棬̫�����������ԡ�\n��������ǧ��ˮ��������г�����ɡ�\n��תǬ���������ľ�������Ȼͨ��\n"]),
"��Ľ��":(["str":2,"int":2,"con":2,"dex":2,"max_qi":1000,"weiwang":300000,"obtain":"��ת���ƴﵽ500��������300000����"]),
"��ʥ":(["str":2,"int":3,"con":3,"dex":2,"max_qi":1000,"weiwang":300000,"obtain":"�����񹦺�Ǭ����Ų�ƴﵽ500��������300000����"]),
//"Ϊ�����":(["str":1,"int":1,"con":1,"dex":1,"obtain":"���Ź��״ﵽ1000"]),
"����֮��":(["str":2,"int":2,"con":2,"dex":2,"obtain":"��������һ�ٴΣ����Ҿ���һ����������","sm":"�������ҵĺ�԰��"]),
"��������":(["int":6,"obtain":"����ﵽ100��","sm":"����Ҫ���ѣ����Ѳ��Ƿ��������Ƿ��¡�"]),
//"��������":(["str":3,"int":3,"con":3,"dex":3,"weiwang":500000,"obtain":"����ﵽ���弶��������������50��������"]),
"����":(["str":1,"int":1,"con":1,"dex":1,"obtain":"�����ڹ��ﵽ200","sm":"���߼�ϰ��֮�ˣ�������־��������Ϣ�����伡�壬���侫�ꡣ"]),
"İ�Ͼ���":(["str":2,"int":2,"con":2,"dex":2,"obtain":"��ò��50����������300000�������","weiwang":300000,"sm":"��֮���������꣬�������������죬��������ٷ�ǰ��"]),
"ɱ��":(["str":5,"int":5,"con":5,"dex":5,"max_qi":8000,"max_neili":8000,"obtain":"ɱ��������100������1000000�������","weiwang":1000000,"sm":"��һ����������ۣ������ϰ��򣬷�Ϊ�����ۣ�"]),
"������":(["str":2,"int":2,"con":2,"dex":2,"max_qi":1000,"weiwang":300000,"obtain":"̫�����ﵽ500��������300000������","sm":"�Կ��Ϻ�ӧ���⹳˪ѩ��;\n�����հ�����������;\nʮ��ɱһ�ˣ�ǧ�ﲻ����;\n���˷���ȥ�����������;\n�й����������ѽ�ϥǰ��;\n������캥������Ȱ����;\n������Ȼŵ��������Ϊ��;\n�ۻ����Ⱥ�����������;\n���Իӽ�鳣���������;\nǧ���׳ʿ���@�մ�����;\n���������㣬��������Ӣ;\n˭������£�����̫������\n"]),
"�ݻ�����":(["str":3,"int":3,"con":3,"dex":3,"obtain":"vip�ȼ���5������200000�������","weiwang":200000]),
"������":(["str":2,"int":2,"con":2,"dex":2,"obtain":"��ò��50��Ů������300000�������","weiwang":300000,"sm":"�����м��ˡ�������������һ�����˳ǡ��ٹ����˹�������֪�����������������ٵá�"]),
"���ɵй�":(["str":3,"int":3,"con":3,"dex":3,"obtain":"Ԫ��������66666������300000�������","weiwang":300000]),
//"��������":(["str":5,"int":5,"con":5,"dex":5,"max_qi":5000,"max_neili":10000,"baoji":10,"yanjiuc":500,"obtain":"��������5��Բ��������1000000�������","weiwang":1000000,"sm":"���ߣ����б����£�ն����ƽ��ɱ��������ս��Ⱥ�ۣ�"]),
"��������":(["str":5,"int":5,"con":5,"dex":5,"max_qi":8000,"max_neili":3000,"baoji":5,"yanjiuc":500,"obtain":"��ѧ�����ͽ��������ﵽ500��������1000000�������","weiwang":1000000,"sm":"���·����,�Ƕ�������?\n�޵����е�, ��Ϊ������"]),
"��������":(["str":10,"int":10,"con":10,"dex":10,"max_qi":10000,"max_neili":10000,"baoji":20,"yanjiuc":1000,"xixue":20,"obtain":"����ȫ����100������5000000�������","weiwang":5000000,"sm":"����ɽ����������\nʱ���������š�\n��������κΣ�\n�������������Σ�"]),
//"����̫��":(["str":3,"int":2,"con":2,"dex":2,"max_qi":2000,"max_neili":2000,"weiwang":500000,"obtain":"��Ĺ��̫�������书�ﵽ500��������500000�������"]),
//"��ҹ����":(["str":3,"int":2,"con":2,"dex":2,"max_qi":2000,"max_neili":2000,"weiwang":500000,"obtain":"��ҹ���ȵ�ﵽ500��������500000�������"]),
//"���˺�һ":(["int":4,"con":4,"max_qi":2000,"max_neili":2000,"weiwang":500000,"obtain":"���������ﵽ500��������500000�������"]),
]);
//ת��Ϊ��������
mapping chinesename=([
"str":"����",
"int":"����",
"con":"����",
"age":"����",
"dex":"��",
"max_jing":"��������",
"max_jingli":"��������",
"max_qi":"��Ѫ����",
"max_neili":"��������",
"yanjiux":"�о�Ч��",
"yanjiuc":"�о�����",
"baoji":"������",
"baojixg":"����Ч��",
"xixue":"��Ѫ��",
"weiwang":"��Ҫ����",
"sm":"�ƺ�˵��",
"bodyreset":"���޴���",
"blevel":"����ȼ�",
"per":"��ò",
"zjvip/level":"vip�ȼ�",
"yuanbao":"Ԫ��",
"qiangdaotask":"���Ź���",
"gender":"�Ա�",
"combat/MKS":"ɱ����",
"combat/dietimes":"��������",
"obtain":HIR"��ȡ��ʽ"NOR,
"jieri/duanwu/pot":"���۹���",
"qixi_dian":"��Ϧ��",
"hsy_bs":"������������"
]);

//��Ҫ��������ֵ
mapping need_attribute=([
"��������":(["bodyreset":5]),
"����֮��":(["hsy_bs":1]),
"��������":(["str":100,"con":100,"int":100,"dex":100]),
"��������":(["blevel":5]),
"ɱ��":(["combat/MKS":1000000]),
"������":(["per":50,"gender":"Ů��"]),
"İ�Ͼ���":(["per":50,"gender":"����"]),
"�ݻ�����":(["cxpay/gongxian":5]),
"���ɵй�":(["yuanbao":66666]),
"��������":(["age":100]),
"����":(["jieri/duanwu/pot":30]),
"��ɧ":(["jieri/duanwu/pot":30]),
"��Ϧ��ʹ":(["qixi_dian":100]),
"����֮��":(["combat/dietimes":100,"bodyreset":1]),
"Ϊ�����":(["qiangdaotask":1000]),
]);

//��Ҫ���ļ���
mapping need_skill=([
"��ħ":(["lonely-sword":500]),
"�ն�����":(["huifeng-jian":500]),
"����":(["force":200]),
"��ʥ":(["jiuyang-shengong":500,"qiankun-danuoyi":500]),
"��������":(["martial-cognize":500,"sword-cognize":500]),
"�̺�����":(["bibo-shengong":500,"yuxiao-jian":500,"bihai-chaosheng":300]),
"��ڤ��":(["beiming-shengong":500,"lingbo-weibu":500,"liuyang-zhang":500]),
"��Ľ��":(["douzhuan-xingyi":500]),
"������":(["taixuan-gong":500]),
"̫��":(["taiji-shengong":500,"taiji-quan":500,"taiji-jian":500]),
"��ҹ����":(["anye-guimeidian":500]),
"����֮��":(["longxiang":500]),
"����̫��":(["taisu-force":500,"taisu-dodge":500,"taisu-moon":500,"taisu-jian":500]),
"ѩɽ�ɺ�":(["lengyue-shengong":500,"hujia-daofa":500]),
"���˺�һ":(["jiuyin-jiuyang":500]),
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
tell_object(me,HIR"������˳ƺţ�"HIC+title+NOR+"\n");
	return 1;
}


string query_title(object me,string title)
{
string msg,msgg;
mixed xg=titles[title];
    if (xg)
{
msg=chinesename["obtain"]+":"+xg["obtain"]+"\n";
msg+=HIC+NOR+ZJBR"==================�ƺżӳ�==================\n";
if (xg["sm"])
msg+=chinesename["sm"]+":\n"+xg["sm"]+"\n";
foreach (msgg in keys(xg))
if (intp(xg[msgg]))
msg+=HIY"("+chinesename[msgg]+")"NOR+HIW":"+xg[msgg]+NOR"\n";
/*if (xg=need_attribute[title])
{
msg+=HIC+NOR+ZJBR"���������������������ƺ����󡪡�������������������������"+ZJBR;
foreach (msgg in keys(xg))
if (xg[msgg])
msg+=HIY"("+chinesename[msgg]+")"NOR+HIW":"+xg[msgg]+NOR"\n";
}*/
       }
else
msg="�óƺ����κμӳ�\n";
	return msg;
}

mapping alltitles()
{
return titles;
}
//����ƺŴ���
int buy_title(object me,string title)
{
string att,*allatt;
mapping attribute;
//�ȼ��������Ƿ���
         if (me->query("titles/"+title))
        {
         tell_object(me,"���ѻ�øóƺš�\n");
         return 1;
         }
         
    if (need_attribute[title])
   {
   		allatt=keys(need_attribute[title]);
		attribute=need_attribute[title];
        foreach (att in allatt)
         if (me->query(att) < attribute[att])
         {
         tell_object(me,"���"+chinesename[att]+"δ��ꡣ\n");
         return 1;
         }
  
   }
//�ټ��㼼���Ƿ���
   if (need_skill[title])
   {
   allatt=keys(need_skill[title]);
attribute=need_skill[title];
       foreach (att in allatt)
         if (me->query_skill(att,1) < attribute[att])
         {
         tell_object(me,"���"+to_chinese(att)+"����"+chinese_number(attribute[att])+"����δ��ꡣ\n");
         return 1;
         }
       
   }
 //�����������Ƿ��㹻
 attribute=titles[title];
           if (me->query("weiwang")<attribute["weiwang"])
        {
         tell_object(me,"�������������\n");
         return 1;
         }
 me->add("potential",attribute["weiwang"]/10);
 if (attribute["weiwang"])
 //me->add("yuanbao",100);
 me->add("weiwang",-attribute["weiwang"]);
 me->set("titles/"+title,1);
 if (titles[title]["sm"])
 message("channel:chat",HBYEL+HIR"��"+title+"��"NOR"��"+me->query("name")+"��"+replace_string(titles[title]["sm"],"\n"," ")+"\n"NOR,users());
 tell_object(me,"��ϲ���óƺ�"+HIR+title+"\n"NOR);
 return 1;
}