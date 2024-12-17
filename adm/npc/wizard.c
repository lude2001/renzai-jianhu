
inherit NPC;
#include <ansi.h>

string ask_baibao();
string ask_zhaohui();
int ask_character(string arg);
int ask_fanli();
int ask_xiandan();
int ask_illness();
int ask_kuilei();
int ask_mengzi();
int ask_buchang();
int ask_buchang1();
int ask_gift();


string *lq_data = ({ });
void create()
{
        set_name("��ʦ",({  "wizard", "wushi" }) );
        set("gender", "����" );
        set("age", 30);
        set("long", "����һ�������������µ���ʦ��\n");

        set("str", 17);
        set("dex", 16);
        set("con", 15);
        set("int", 17);
        set("shen_type", 1);
        set("combat_exp", 100);
        set("attitude", "peaceful");

        setup();

        set("inquiry", ([
              "���������": (: ask_buchang1 :),
              "��������": (: ask_buchang :),
              "�����": (: ask_baibao :),
              "�һش����" : (: ask_zhaohui :),
              "���ӹ���": (: ask_fanli :),
              "�ɵ�": (: ask_xiandan :),
              "����": (: ask_mengzi :),
              "�������": (: ask_kuilei :),
        ]) );

        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
	add_action("ask_character","washme");
}

int ask_gift()
{
    object ob = this_player();
    object gift;

    if (ob->query("zjvip/gift/2016christmas")) {
        command("say ���Ѿ���ȡ��ʥ�������ˣ�");
        return 1;
    }

    command("nod "+ob->query("id"));
    command("say ����ͷ����㡣");
    ob->set("zjvip/gift/2016christmas",1);
    gift = new("/clone/gift/gift_christmas");
    gift->move(ob);
    tell_object(ob,HIM"������һ����ƻ����"NOR"\n");  

	log_file("buchang", sprintf("%s��%s(%s)��ȡ��ʥ�����\n",ctime(time()),ob->query("name"),ob->query("id")));
    return 1;
        
}

int ask_buchang()
{
    object ob = this_player();
    object card,putao;


    if (ob->query("zjvip/weiwen")==10 || member_array(ob->query("id"),lq_data) != -1) {
        command("say ���Ѿ���ȡ����������ˣ�");
        return 1;
    }

    putao = new_bind("/clone/vip/putao1");
    putao->set_amount(10);
    card = new_bind("/clone/baiyi/tencard");
    card->set_amount(1);

    putao->move(ob);
    card->move(ob);

    
    command("nod "+ob->query("id"));
    command("say ����ͷ����㡣");
    ob->set("zjvip/weiwen",10);
   // ob->add("potential",50000);
   lq_data += ({ ob->query("id") });

    tell_object(ob,HIC"�����˹�������,10����������,1��ʮ���鿨Ƭ,��ף����Ϸ���֣�"NOR"\n");  

	log_file("buchang", sprintf("%s��%s(%s)��ȡ��(anbei)2022.10.4���������\n",ctime(time()),ob->query("name"),ob->query("id")));
    return 1;
        
}

int ask_buchang1()
{
    object ob = this_player();
    object card,putao;
    string *md = ({
        "xyma1834",
        "mm777",
        "ashen090",
        "qq481427150",
        "z2454119",
        "mimizhiyin",
        "foam",
        "yst2110003",
        "ashen090",
        "x2437279718",
        "mirfc",
        "qq835777574",
        "yyt123456",
        "mojurly",
        "h13189005531",
        "love678",
        "yu192721769",
        "www109740",
        "qw18675630",
        "sjl16924",
        "yke9111",
        "qxyyx2580",
        "htaicq123",
        "xujintao",
        "qwe550021",
        "xujintao",
        "yj01817918",
        "shisijun14",
        "a3302047165",
        "s025825",
        "tx151134",
        "wjmmh812514",
        "snow",
        "ljf123",
        "codmz",
        "zkhy66",
    });
    string *md2 = ({
        "d259060658",
        "snk255",
        "apps",
        "a176129",
        "x2437279718",
        "qq667788999",
        "wuxihao1",
        "wy2310548515",
        "juejie2020",
        "wszldg66",
        "z2454119",
    });
    if (ob->query("weihu/hsy")>0) {
        command("say ���Ѿ���ȡ����Ӧ������ˣ�");
        return 1;
    }
    
    if (member_array(ob->query("id"),md) == -1 && member_array(ob->query("id"),md2) == -1)
    {
        command("say ��û�вμӺ������������޷���������");
        return 1; 
    }

    putao = new_bind("/clone/vip/putao1");
    putao->set_amount(4);
    card = new_bind("/clone/vip/dan_chongmai4");
    card->set_amount(50);
    
    
    if (member_array(ob->query("id"),md2) != -1)
    {
        putao->set_amount(10);
        card->set_amount(100);
        
        
    tell_object(ob,HIC"�����˺��������,10���������ѣ�100����Ʒ����������ף����Ϸ���֣�"NOR"\n");  
        
    }
    else
    {
        
    tell_object(ob,HIC"�����˺��������,4���������ѣ�50����Ʒ����������ף����Ϸ���֣�"NOR"\n");  
    }
    
    putao->move(ob);
    card->move(ob);
    
    
    
    command("nod "+ob->query("id"));
    command("say ����ͷ����㡣");
    ob->add("weihu/hsy",1);
    ob->add("hsy_bs",1);
    //ob->delete("last_day_sign");


	log_file("buchang", sprintf("%s��%s(%s)��ȡ�˺����������\n",ctime(time()),ob->query("name"),ob->query("id")));
    return 1;
        
}


int ask_character(string arg)
{
	object me = this_player();
	string msg, type, cs;

	if (! wizardp(me) )
		return notify_fail("��ʱ�رմ˹��ܡ�\n");
		
	if (!arg || arg == 0) {
		msg = ZJOBLONG+
		      "�ĺ���������ʦ�ķ�-�����񹦣���߹���"ZJBR
			"�������䣬��ʦ�ķ�-�Ϻ����������ӷ���"ZJBR
			"�����䣬��ʦ�ķ�-�����񹦣��������"ZJBR
			"���ռ�թ����ʦ�ķ�-����ħ������������"ZJBR
			"��ѡ������Ը�\n";
		
		msg += ZJOBACTS2+ZJMENUF(2,2,9,30);
		msg += "��������:washme ��������";
		msg += ZJSEP"������:washme ������";
		msg += ZJSEP"���ռ�թ:washme ���ռ�թ";
		msg += ZJSEP"�ĺ�����:washme �ĺ�����";
		
		write(msg + "\n");
		
	} else {
		if(sscanf(arg,"%s %s", type, cs) == 2)
		{
			if (me->query("character") == type) {
				tell_object(me, "�㱾�����������Ը�\n");
				return 1;
			}

			if (cs == "yes") {
				if (type == "��������" && me->query("character") == "�ĺ�����") {
					me->set("character", type);
					tell_object(me, "��ɹ����Ը�ı�Ϊ"+type+"��\n");
				} else if (type == "�ĺ�����" && me->query("character") == "��������") {
					me->set("character", type);
					tell_object(me, "��ɹ����Ը�ı�Ϊ"+type+"��\n");
				} else if (type == "��������" || type == "�ĺ�����" || type == "������" || type == "���ռ�թ") {
					tell_object(me, "�Բ����㲻���ϸı��Ը��������\n");
                              return 1;
				} else {
					tell_object(me, "û�������Ը�������ѡ��\n");
					return 1;
				}
			} 
		} else {
			msg = ZJOBLONG+"��ȷ��ѡ���Ը�Ϊ"+HIG+arg+NOR"��\n";			
			msg += ZJOBACTS2+ZJMENUF(2,2,9,30);
			msg += "ȷ��:washme "+arg + " yes";
			msg += ZJSEP"ȡ��: ";
			
			write(msg + "\n");
		}
	}
	
	return 1;
}



int ask_fanli()
{
        int i;
        object ob = this_player();
        i=ob->query("zjvip/dizi_pay");
     
        if(ob->query("zjvip/dizi_pay")<1){
                command("say ��Ŀǰ�ĵ��ӹ���̫�ͣ��޷���ȡ������");
                message_vision("$N���ۼƻ����"+ob->query("zjvip/dizi_fanli")+"��Ԫ���Ľ�����\n",ob,  this_object());
                return 1;
        }
        else {
                command("nod "+ob->query("id"));
                command("say ���ѷ�����ȡ���ӹ��׽���������");
	        ob->add("yuanbao",i);
                ob->add("zjvip/dizi_pay",-i);
                ob->add("zjvip/dizi_fanli",i);
                message_vision("$N�����"+i+"��Ԫ���Ľ�����\n",ob,  this_object());
                message_vision("$N���ۼƻ����"+ob->query("zjvip/dizi_fanli")+"��Ԫ���Ľ�����\n",ob,  this_object());
                return 1;
        }
}

int ask_xiandan()
{
    int a,b,c,d;
    object ob = this_player();

	a=ob->query("gift/xiandan");
	b=ob->query("gift/unknowdan");
	c=ob->query("gift/shenliwan");
	d=ob->query("gift/xisuidan");
     
	if (ob->query("zjvip/times") <1) {
        command("say �Բ�����ֻ���������˵����飡");
        return 1;
    }
    else {
    command("nod "+ob->query("id"));
    command("say ���������һ�¼�¼��");
    command("say ��λ" + RANK_D->query_respect(ob) +"�����Ѿ����ˣ�"+chinese_number(a)+"��"HIY"�����ɵ�"NOR"��"+chinese_number(b)+"��"HIR"����ɵ�"NOR"��"+chinese_number(c)+"��"HIG"������"NOR"��"+chinese_number(d)+"��"YEL"ϴ�赤"NOR"��");
	return 1;
    }
}

int ask_illness()
{
        int a,b,c,d;
        object ob = this_player();

	a=ob->query("gift/xiandan_fail");
	b=ob->query("gift/unknowdan_fail");
	c=ob->query("gift/shenliwan_fail");
	d=ob->query("gift/xisuidan_fail");
     
	if (ob->query("zjvip/times") <1) {
                command("say �Բ�����ֻ���������˵����飡");
                return 1;
        }
        else {
                command("nod "+ob->query("id"));
                command("say ���������һ�¼�¼��");
                command("say ��λ" + RANK_D->query_respect(ob) +"�������"HIY "�����ɵ�" NOR"��"+chinese_number(a)+"������������"HIR "����ɵ�" NOR"��"+chinese_number(b)+"������������"HIG "������" NOR"��"+chinese_number(c)+"������������"YEL "ϴ�赤" NOR"��"+chinese_number(d)+"��������");
                return 1;
        }
}

string ask_baibao()
{
        object ob;
        mapping myfam;
        object nang;

        ob = this_player();
        myfam = (mapping)ob->query("family");
        
        //if(!myfam) return "�㻹���ȼ������ɰɣ�";

	if (ob->query("combat_exp") < 10000)
		return "��Ȼ��������ֻǬ������������ս��������ô�������������ô�죿\n";

	if (ob->query("chuwudai"))
		return "��֮ǰ�Ѿ����������ˡ�\n";
        
	if ( present("chuwu dai", ob))
		return "���Ѿ�����һ�����������̰�����ᣡ\n";

	nang=new("/clone/misc/baibao");
	nang->set("owner_id", ob->query("id"));
	nang->move(ob);
	ob->set("chuwudai", 1);
	write("��õ�һ�������!\n");
	return "����Ǹ��������ú��������ɡ�";
}

string ask_zhaohui()
{
	object nang, ob = this_player();
	
	if (!ob->query("chuwudai"))
		return "�㻹û����ȡ�������\n";
	
	if (present("chuwu dai", ob))
		return "���Ѿ�����һ�����������̰�����ᣡ\n";
	
	nang=new("/clone/misc/baibao");
	nang->set("owner_id", ob->query("id"));
	nang->move(ob);
	return "���һ�����Ĵ������\n";
}

int ask_kuilei()
{
    object ob = this_player();
    object yao;
	int m = localtime(time())[4]+1,m1,m2,m3;
	m1= m-1;
	m2= m1-1;
	m3= m2-1;
     
	if (ob->query("zjvip/times") <1) {
        command("say �Բ�����ֻ���������˵����飡");
        return 1;
    }
	if ((ob->query("zjvip/all_pay")+ob->query("gongxians"))<1000) {
        command("say �Բ�����Ĺ��ײ�������������ȡ������ܵ�������");
        return 1;
    }
	if (ob->query("zjvip/kuilei"+m)>=((ob->query("zjvip/all_pay")+ob->query("gongxians"))/1000)) {
        command("say ����Ŀǰ�Ĺ���ֻ����"+chinese_number((ob->query("zjvip/all_pay")+ob->query("gongxians"))/1000)+"��������ܣ�");
        return 1;
    }

	command("nod "+ob->query("id"));
    command("say ����͸��㡣");
    yao = new("/clone/shizhe/kuilei");
    yao->move(ob);
    ob->add("zjvip/kuilei"+m,1);
    ob->delete("zjvip/kuilei"+m1);
    ob->delete("zjvip/kuilei"+m2);
    ob->delete("zjvip/kuilei"+m3);
    message_vision("$N����$nһ��" + yao->query("name") + "��\n",this_object(),ob);
	log_file("gift", sprintf(ob->query("id")+"��%s����ȡ��һ��������ܡ�\n",ctime(time())));
    return 1;
        
}

int ask_mengzi()
{
        object ob = this_player();
        object yao;

     
	if (ob->query("zjvip/times") <1) {
                command("say �Բ�����ֻ���������˵����飡");
                return 1;
        }
	if (ob->query("zjvip/all_pay")+ob->query("gongxians")<1000) {
                command("say �Բ�����Ĺ��ײ�������������ȡ�����ӡ���������");
                return 1;
        }

	if ( present("mengzi book", ob)) {
                command("say ���Ѿ�����һ�������ӡ��ˣ���̰�����ᣡ");
                return 1;
        }

                command("nod "+ob->query("id"));
                command("say ����͸��㡣");
        yao = new("/clone/shizhe/mengzi");
        yao->move(ob);
        message_vision("$N����$nһ����" + yao->query("name") + "����\n",this_object(),ob);
                return 1;
        
}
