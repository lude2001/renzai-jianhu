
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
        set_name("巫师",({  "wizard", "wushi" }) );
        set("gender", "男性" );
        set("age", 30);
        set("long", "这是一个成天无所事事的巫师。\n");

        set("str", 17);
        set("dex", 16);
        set("con", 15);
        set("int", 17);
        set("shen_type", 1);
        set("combat_exp", 100);
        set("attitude", "peaceful");

        setup();

        set("inquiry", ([
              "好声音礼包": (: ask_buchang1 :),
              "国庆节礼包": (: ask_buchang :),
              "储物袋": (: ask_baibao :),
              "找回储物袋" : (: ask_zhaohui :),
              "弟子贡献": (: ask_fanli :),
              "仙丹": (: ask_xiandan :),
              "孟子": (: ask_mengzi :),
              "替身傀儡": (: ask_kuilei :),
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
        command("say 你已经领取过圣诞礼物了！");
        return 1;
    }

    command("nod "+ob->query("id"));
    command("say 我这就发给你。");
    ob->set("zjvip/gift/2016christmas",1);
    gift = new("/clone/gift/gift_christmas");
    gift->move(ob);
    tell_object(ob,HIM"你获得了一个红苹果。"NOR"\n");  

	log_file("buchang", sprintf("%s：%s(%s)领取了圣诞礼物。\n",ctime(time()),ob->query("name"),ob->query("id")));
    return 1;
        
}

int ask_buchang()
{
    object ob = this_player();
    object card,putao;


    if (ob->query("zjvip/weiwen")==10 || member_array(ob->query("id"),lq_data) != -1) {
        command("say 你已经领取过中秋礼包了！");
        return 1;
    }

    putao = new_bind("/clone/vip/putao1");
    putao->set_amount(10);
    card = new_bind("/clone/baiyi/tencard");
    card->set_amount(1);

    putao->move(ob);
    card->move(ob);

    
    command("nod "+ob->query("id"));
    command("say 我这就发给你。");
    ob->set("zjvip/weiwen",10);
   // ob->add("potential",50000);
   lq_data += ({ ob->query("id") });

    tell_object(ob,HIC"你获得了国庆节礼包,10串神奇葡萄,1张十连抽卡片,并祝你游戏快乐！"NOR"\n");  

	log_file("buchang", sprintf("%s：%s(%s)领取了(anbei)2022.10.4奖励礼包。\n",ctime(time()),ob->query("name"),ob->query("id")));
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
        command("say 你已经领取过相应的礼包了！");
        return 1;
    }
    
    if (member_array(ob->query("id"),md) == -1 && member_array(ob->query("id"),md2) == -1)
    {
        command("say 你没有参加好声音比赛，无法获得礼包！");
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
        
        
    tell_object(ob,HIC"你获得了好声音礼包,10个神奇葡萄，100个极品冲脉丹，并祝你游戏快乐！"NOR"\n");  
        
    }
    else
    {
        
    tell_object(ob,HIC"你获得了好声音礼包,4个神奇葡萄，50个极品冲脉丹，并祝你游戏快乐！"NOR"\n");  
    }
    
    putao->move(ob);
    card->move(ob);
    
    
    
    command("nod "+ob->query("id"));
    command("say 我这就发给你。");
    ob->add("weihu/hsy",1);
    ob->add("hsy_bs",1);
    //ob->delete("last_day_sign");


	log_file("buchang", sprintf("%s：%s(%s)领取了好声音礼包。\n",ctime(time()),ob->query("name"),ob->query("id")));
    return 1;
        
}


int ask_character(string arg)
{
	object me = this_player();
	string msg, type, cs;

	if (! wizardp(me) )
		return notify_fail("暂时关闭此功能。\n");
		
	if (!arg || arg == 0) {
		msg = ZJOBLONG+
		      "心狠手辣，宗师心法-九阴神功，提高攻击"ZJBR
			"光明磊落，宗师心法-南海玄功，增加防御"ZJBR
			"狡黠多变，宗师心法-不败神功，提高命中"ZJBR
			"阴险奸诈，宗师心法-葵花魔功，增加闪避"ZJBR
			"请选择你的性格：\n";
		
		msg += ZJOBACTS2+ZJMENUF(2,2,9,30);
		msg += "光明磊落:washme 光明磊落";
		msg += ZJSEP"狡黠多变:washme 狡黠多变";
		msg += ZJSEP"阴险奸诈:washme 阴险奸诈";
		msg += ZJSEP"心狠手辣:washme 心狠手辣";
		
		write(msg + "\n");
		
	} else {
		if(sscanf(arg,"%s %s", type, cs) == 2)
		{
			if (me->query("character") == type) {
				tell_object(me, "你本来就是这种性格。\n");
				return 1;
			}

			if (cs == "yes") {
				if (type == "光明磊落" && me->query("character") == "心狠手辣") {
					me->set("character", type);
					tell_object(me, "你成功将性格改变为"+type+"。\n");
				} else if (type == "心狠手辣" && me->query("character") == "光明磊落") {
					me->set("character", type);
					tell_object(me, "你成功将性格改变为"+type+"。\n");
				} else if (type == "光明磊落" || type == "心狠手辣" || type == "狡黠多变" || type == "阴险奸诈") {
					tell_object(me, "对不起，你不符合改变性格的条件。\n");
                              return 1;
				} else {
					tell_object(me, "没有这种性格，请认真选择。\n");
					return 1;
				}
			} 
		} else {
			msg = ZJOBLONG+"你确定选择性格为"+HIG+arg+NOR"吗？\n";			
			msg += ZJOBACTS2+ZJMENUF(2,2,9,30);
			msg += "确定:washme "+arg + " yes";
			msg += ZJSEP"取消: ";
			
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
                command("say 你目前的弟子贡献太低，无法领取奖励。");
                message_vision("$N已累计获得了"+ob->query("zjvip/dizi_fanli")+"个元宝的奖励。\n",ob,  this_object());
                return 1;
        }
        else {
                command("nod "+ob->query("id"));
                command("say 你已符合领取弟子贡献奖励条件。");
	        ob->add("yuanbao",i);
                ob->add("zjvip/dizi_pay",-i);
                ob->add("zjvip/dizi_fanli",i);
                message_vision("$N获得了"+i+"个元宝的奖励。\n",ob,  this_object());
                message_vision("$N已累计获得了"+ob->query("zjvip/dizi_fanli")+"个元宝的奖励。\n",ob,  this_object());
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
        command("say 对不起，我只处理东方族人的事情！");
        return 1;
    }
    else {
    command("nod "+ob->query("id"));
    command("say 我来帮你查一下记录。");
    command("say 这位" + RANK_D->query_respect(ob) +"，你已经吃了："+chinese_number(a)+"颗"HIY"醍醐仙丹"NOR"，"+chinese_number(b)+"颗"HIR"火红仙丹"NOR"，"+chinese_number(c)+"颗"HIG"神力丸"NOR"，"+chinese_number(d)+"颗"YEL"洗髓丹"NOR"。");
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
                command("say 对不起，我只处理东方族人的事情！");
                return 1;
        }
        else {
                command("nod "+ob->query("id"));
                command("say 我来帮你查一下记录。");
                command("say 这位" + RANK_D->query_respect(ob) +"，你吃了"HIY "醍醐仙丹" NOR"有"+chinese_number(a)+"处暗疾，吃了"HIR "火红仙丹" NOR"有"+chinese_number(b)+"处暗疾，吃了"HIG "神力丸" NOR"有"+chinese_number(c)+"处暗疾，吃了"YEL "洗髓丹" NOR"有"+chinese_number(d)+"处暗疾。");
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
        
        //if(!myfam) return "你还是先加入门派吧？";

	if (ob->query("combat_exp") < 10000)
		return "虽然我这里有只乾坤袋，可是你战斗经验这么差，被人抢走了怎么办？\n";

	if (ob->query("chuwudai"))
		return "你之前已经领过储物袋了。\n";
        
	if ( present("chuwu dai", ob))
		return "你已经有了一个储物袋，别贪得无厌！\n";

	nang=new("/clone/misc/baibao");
	nang->set("owner_id", ob->query("id"));
	nang->move(ob);
	ob->set("chuwudai", 1);
	write("你得到一个储物袋!\n");
	return "这可是个宝贝，好好利用它吧。";
}

string ask_zhaohui()
{
	object nang, ob = this_player();
	
	if (!ob->query("chuwudai"))
		return "你还没有领取储物袋。\n";
	
	if (present("chuwu dai", ob))
		return "你已经有了一个储物袋，别贪得无厌！\n";
	
	nang=new("/clone/misc/baibao");
	nang->set("owner_id", ob->query("id"));
	nang->move(ob);
	return "你找回了你的储物袋。\n";
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
        command("say 对不起，我只处理东方族人的事情！");
        return 1;
    }
	if ((ob->query("zjvip/all_pay")+ob->query("gongxians"))<1000) {
        command("say 对不起，你的贡献不够，不符合领取替身傀儡的条件！");
        return 1;
    }
	if (ob->query("zjvip/kuilei"+m)>=((ob->query("zjvip/all_pay")+ob->query("gongxians"))/1000)) {
        command("say 以你目前的贡献只能领"+chinese_number((ob->query("zjvip/all_pay")+ob->query("gongxians"))/1000)+"个替身傀儡！");
        return 1;
    }

	command("nod "+ob->query("id"));
    command("say 我这就给你。");
    yao = new("/clone/shizhe/kuilei");
    yao->move(ob);
    ob->add("zjvip/kuilei"+m,1);
    ob->delete("zjvip/kuilei"+m1);
    ob->delete("zjvip/kuilei"+m2);
    ob->delete("zjvip/kuilei"+m3);
    message_vision("$N给了$n一个" + yao->query("name") + "。\n",this_object(),ob);
	log_file("gift", sprintf(ob->query("id")+"在%s：领取了一个替身傀儡。\n",ctime(time())));
    return 1;
        
}

int ask_mengzi()
{
        object ob = this_player();
        object yao;

     
	if (ob->query("zjvip/times") <1) {
                command("say 对不起，我只处理东方族人的事情！");
                return 1;
        }
	if (ob->query("zjvip/all_pay")+ob->query("gongxians")<1000) {
                command("say 对不起，你的贡献不够，不符合领取《孟子》的条件！");
                return 1;
        }

	if ( present("mengzi book", ob)) {
                command("say 你已经有了一本《孟子》了，别贪得无厌！");
                return 1;
        }

                command("nod "+ob->query("id"));
                command("say 我这就给你。");
        yao = new("/clone/shizhe/mengzi");
        yao->move(ob);
        message_vision("$N给了$n一本《" + yao->query("name") + "》。\n",this_object(),ob);
                return 1;
        
}
