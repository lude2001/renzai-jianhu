/*duotreasure.c
by ����ҹ��(baiyi666) baiyi666
�������ϵͳ
˼·�������������ȡ��
*/
#include <ansi.h>

inherit F_DBASE;
#include <localtime.h>
//������������ͼ�б�
mapping room_place = ([
	"����ɽ"		: "/d/baituo/",
	"����"			: "/d/beijing/",
	"����" 			: "/d/changan/",
	"����"			: "/d/city/",
	"�ɶ�"			: "/d/city3/",
	"����"			: "/d/dali/",
	"����ɽ" 		: "/d/emei/",
	"��ɽ"			: "/d/foshan/",
	"ؤ��" 			: "/d/gaibang/",
	"����"			: "/d/fuzhou/",
	"����"			: "/d/guanwai/",
	"����ɽׯ"	: "/d/guiyun/",
	"��Ĺ" 			: "/d/gumu/",
	"����"			: "/d/hangzhou/",
	"��ľ��"		: "/d/heimuya/",
	"��ɽ" 			: "/d/hengshan/",
	"��ɽ"			: "/d/henshan/",
	"�ƺ�"			: "/d/huanghe/",
	"��ɽ��"		: "/d/huashan/",
	"���չ�"			: "/d/lingjiu/",
	"����"			: "/d/lingzhou/",
	"÷ׯ"			: "/d/meizhuang/",
	"����" 			: "/d/mingjiao/",
	"���ɽ"		: "/d/qingcheng/",
	"ȫ����" 		: "/d/quanzhen/",
	"Ȫ��" 			: "/d/quanzhou/",
	"������" 		: "/d/shaolin/",
	"������"		: "/d/shenlong/",
	"��ɽ"			: "/d/songshan/",
	"����"			: "/d/suzhou/",
	"̩ɽ"			: "/d/taishan/",
	"�һ���"		: "/d/taohua/",
	"������"		: "/d/tianlongsi/",
	"��ٹ�"		: "/d/wanjiegu/",
	"�䵱ɽ"		: "/d/wudang/",
	"���͵�"		: "/d/xiakedao/",
	"����"			: "/d/xiangyang/",
	"��ң��"		: "/d/xiaoyao/",
	"���޺�" 		: "/d/xingxiu/",
	"Ѫ����" 		: "/d/xuedao/",
	"ѩɽ" 			: "/d/xueshan/",
	"������" 		: "/d/yanziwu/",
]);
//����������Ʒ�б�
string *duobao=({
"/clone/vip/dan_qingxin",
"/clone/vip/dan_zhengqi",
"/clone/vip/jinsha",
"/clone/vip/lingzhi",
});
int ok = 0;
int ok1 = 0;
string path_where=0;
int check_hp(object me,int value);
int choose_player(object me);
int top_list(object ob1,object ob2);

string *allroom_file,room_file,*allplace_name,place_name;//ȫ�ֱ������Ա����
void create()
{
	seteuid(getuid());
	set("channel_id", "�������ϵͳ");
	CHANNEL_D->do_channel( this_object(), "sys", "�������ϵͳ�Ѿ�������"NOR);
	set_heart_beat(20);//Ԥ����
}

int clean_up()
{
	return 1;
}
void  load_room()
{
//��ȡ���еĴ��ͼ����
allplace_name=keys(room_place);
//�����ȡһ�����ͼ
place_name=allplace_name[random(sizeof(allplace_name))];
//��ȡһ�����ͼ��ȫ���ķ���
allroom_file=stat(room_place[place_name]);
//ֻ�������ͼĿ¼�ڵ�.c�ļ������䣩
foreach (room_file in allroom_file)
{
if (strsrch(room_file,".c")==-1)
allroom_file-=({room_file});
}
//�����ȡһ������ص�
room_file=room_place[place_name]+allroom_file[random(sizeof(allroom_file))];
}

void check_time()
{
	int GMT = time();
	string d, times;
	int h, s,value;
	object room, ob;
	times = ctime(GMT);
	//Sun(������) Mon(����һ)  Tue(���ڶ�)  Wed(������)  Thu(������)  Fri(������)  Sat(������)
	d = times[0..2];//����
	h = to_int(times[10..12]);//ʱ
	s = to_int(times[14..15]);//��
//	�����������������Ͼŵ㿪ʼ�����賿����
	if ((h>=21||h<=3)&&(s==30||s==0))
	{
	object npc,obj,*npcs;
	//��ΪҪ�����µ�������ԭ�����������Ӧ����� �Խ�ʡ�ڴ�
		npcs = children("/clone/worldboss/xinmo");
		foreach (npc in npcs)
		destruct(npc);
		//��������һ���������
	npc=new("/clone/worldboss/xinmo");
	//�����ȡһ��������Ʒ���������ı���
	obj=new(duobao[random(sizeof(duobao))]);

//value��ʲô��?��������һ����Ʒ�ļ�ֵ������������ʱֻͨ�������ֵ��
	if (obj->query("yuanbao"))
	value=obj->query("yuanbao")*10000;
	else
	if (obj->query("value"))
	value=obj->query("value")/2;
	else
	value=500000;	//��صͼ�ֵ50���ƽ�ûë����
	obj->move(npc);	
check_hp(npc,value);	
/*	
//��������������ϵͳ���ִ��󣬲���
if (!objectp(room_file))
	{
	tell_object(find_player("baiyi666"),"�������\n");
	}*/
	
	while (1)//��飬Ϊ�˱�����䵽����ս���ĵ�ͼ��
	{
	load_room();
		if (!room_file->query("no_fight"))	
		break;
	}
	npc->move(room_file);
	find_player("baiyi666")->move(room_file);
	tell_object(find_player("baiyi666"),HBRED+place_name+room_file->query("short")+"����\n"NOR);
	choose_player(npc);
	npc->force_me("chat ���ǣ��ߣ��޴��������ħ��"+place_name+"��"+room_file->query("short")+"��ս���¸��֣��ñ�ħ������������");
	}
	else
	return;
	//========================
	
}
//�������
protected void heart_beat()
{	
	check_time();
}
//�������ɵ���������״̬����
int check_hp(object me,int value)
{
int qi,neili;
 qi = me->query("max_qi")*20;
 neili = me->query("max_neili")*20;

me->set("max_qi",qi);
me->set("eff_qi",qi);
me->set("qi",qi);
me->set("max_neili",neili);
me->set("neili",neili);

return 1;
}
//���ѡ��ǰ��������ҽ��д���
int choose_player(object me)
{
   object *ob,*list,rand_player;
   
ob = filter_array(children(USER_OB),(: userp($1) && !wizardp($1) :));
        list = sort_array(ob, (: top_list :));
        
        if (sizeof(list)>3)//�����������Ҷ�û�У���ô��?����       
        list = ({list[0],list[1],list[2]});//��ȡǰ��λ
        
        rand_player = list[random(sizeof(list))];//�����ȡһλ���
        "/cmds/wiz/copyskill"->copy_skill(me,rand_player);//���ƶ�Ӧ��ҵļ���
        me->set_name(rand_player->name()+"����ħ", ({ getuid(rand_player)+" mo", "mo" }));
        me->set("name",rand_player->name()+"����ħ");//�ڶ��αȽϱ���
        return 1;
}

//ֱ�����Ѿ�д�õ����й���
int top_list(object ob1,object ob2)
{
    return "/cmds/usr/topten"->top_list(ob1,ob2);    
}