// logind.c

#include <ansi.h>
#include <command.h>
#include <login.h>
#include <config.h>
#include <getconfig.h>

#define MUDLIST_CMD     "/cmds/usr/mudlist"
#define REBOOT_CMD      "/cmds/arch/reboot"

inherit F_DBASE;

static int wiz_lock_level = 0;

static string *movie;

string *banned_name = ({
    "��", "��", "��", "��", "��", "��","����",
    "��", "ү", "��", "��","����","����","�ٲ�","fuck","����","����","�ڽ�","�Խ�","����","����",
    "ʺ", "��", "��","����","����","��ү","����","����","����",
"�Լ�","ɱ��","����","ѩ��","��ң","����","����","����","����","���","ĳ��","ʬ��",
"����","�ܹ�","����","����","��ʦ","�ſ�","���","��","�齣","���ִ���","����ͨ","����",
"������","�̿�","����","��ʦ","���","ͷ­","ɱ�˷�",
// Mud ������������
"��ɽ","��ɽ","��ɽ","��ɽ","̩ɽ","ѩɽ","��ɽ","��ɽ","����","�置","����","��ԭ",
"�Ͻ�","����","�ƺ�","�й�","�л�","����ɽ","����ɽ","����ɽ","�䵱ɽ","����ɽ",
"����","�һ���","��ľ��",
"����","ؤ��","����","����","��Ĺ","ȫ��","����","����","����","�һ�","����",
"������","������","�嶾��","����","а��","��������","�������","�ٸ�","����",
"������","�䵱��","���ư�","��ͨ����","������","����Ľ��","��Ĺ��","��ɽ��","��ɽ��",
"����","������","������",
// ��Ҫ��������
"��ӹ","��Сƽ","������","ë��","���Ż�","�ʵ�", "����","����", "��ϯ", "ϰ��ƽ", "���ǿ",
 "����Ա", "��ʦ", "�ɲ�",
// С˵����
"������","���޼�","����","���","�����","���","���˷�","ΤС��","Ԭ��־","��һ��",
"�¼���","����","����","�Ƿ�","����","��������","ŷ����","���߹�","��ҩʦ","�λ�ү",
"һ�ƴ�ʦ","������","�ܲ�ͨ","����","������","�������",
// �໰
"ͳһ","����","�����о�","���ִ�","����","�����","ȥ���","������","������","����",
"�쵰","����","ɱ��","����","ǿ��","��Ů","̨��","�쵼","����","ƨ��","ƨ��","����",
"��ƨ","����","����","���","��Ѿ","����","����","����","ɵ��","����","����","�Ҳ�",
"̫��","�¹�","�˸�","����","��", "����", "����", "�ּ�", "��", "����", "����",
//��������
"��Ů","����",

});
//�����أ���һЩ������Ҫʹ��mapping����
mapping born_place = ([
	"ŷ������" : ([ "born"      : "��������",
			"surname"   : "ŷ��",
			"startroom" : "/d/baituo/dating",
		     ]),
	"�������" : ([ "born"      : "��������",
			"surname"   : "��",
			"startroom" : "/d/guanwai/xiaowu",
		     ]),
	"���ϻ���" : ([ "born"      : "��������",
			"surname"   : "��",
			"startroom" : "/d/dali/wangfugate",
		     ]),
	"Ľ������" : ([ "born"      : "��������",
			"surname"   : "Ľ��",
			"startroom" : "/d/yanziwu/cuixia",
		     ]),
]);

// �ڲ����õĺ���
private void get_user(string arg, object ob);
private void get_char(string arg, object ob);
void jiance(string arg,object ob,string str);
private void init_new_player(object user);

// ���Ա��ⲿ���õĺ���
object  make_body(object ob);
varargs void enter_world(object ob, object user, int silent);
varargs void reconnect(object ob, object user, int silent);
object find_body(string name);
int check_legal_id(string arg);
int check_legal_name(string arg, int maxlen);

void create() 
{
	seteuid(ROOT_UID);
	set("channel_id", "����");
}

void logon(object ob)
{
	string str;
	if (BAN_D->is_banned(query_ip_name(ob)) == 1) {
		write(ZJTMPSAY"��ĵ�ַ�ڱ� MUD ���ܻ�ӭ��\n");
		destruct(ob);
		return;
	}
	write("\n");
	str = ZJKEY;
	write("ver1.0,"+str+"\n");
	input_to("jiance",ob,str);
}

void jiance(string arg,object ob,string str)
{
	if(!arg)
	{
		input_to("jiance",ob,str);
		return;
	}
	if(arg=="zjmDMaIpOvxdb") ob->set_temp("web_log",1);
	write("�汾��֤�ɹ�\n");
	input_to("get_user", ob);
}

private void get_user(string arg, object ob)
{
	/*arg,demouser||ads123||�������||��||��������||20,13,30,24||trick||����
	*/
	object old_link,user;
	string *myinfo,ip,email;
    string *fengjin = ({
        //"snk255",
        "m1102020131",
        "enter",
        "ghjkl",
        "wertyui",
        "ljp01",
        "q1096",
        //"u2moonlight",
       // "qq1958519011",
    //    "chonglai",
    });

//���´���
	if( !arg||arg=="") {
		input_to("get_user", ob);
		return;
	}

	// if (time() < 1653134400)
	// {
	// 	write(ZJTMPSAY + "2022.5.21���ϰ˵㿪�š�\n");
	// 	return;
	// }
//��ceshi888Ϊ�ϰ�����˺�
	myinfo = explode(arg,"�U");

if (member_array(myinfo[0],fengjin) != -1)
{
    	write(ZJTMPSAY"���˺��ѱ����÷����\n");
		return;
}
//���ڲ��Ե�Լ���ַ�
if (myinfo[0]=="ceshi888")
{
write(ZJTMPSAY+myinfo[0]+"�˺ŵ�¼\n");
arg = myinfo[0]+"�U123456�UС���ӨU���ԨU�ĺ������U20,20,20,20�Uself�U���ϻ���";
	myinfo = explode(arg,"�U");	
	}


	if( !check_legal_id(lower_case(myinfo[0]))) {
		//0001��ID���Ϸ�
		write(myinfo[0]+"\n");
		input_to("get_user", ob);
		return;
	}

	myinfo[0] = lower_case(myinfo[0]);

/*
	if (1) {
		write(ZJTMPSAY"��������ʱ���ܵ�½��\n");
		input_to("get_user", ob);
		return;
	}
*/
	if (wiz_level(myinfo[0]) < wiz_lock_level)
        {
		write(sprintf(ZJTMPSAY"�Բ���%s����ά���У����Ժ��¼������\n",LOCAL_MUD_NAME()));
		input_to("get_user",ob);
		return;
	}
//��������id
	if( (string)ob->set("id", myinfo[0]) != myinfo[0]) {
		write(ZJTMPSAY"δ֪����������i������\n");
		input_to("get_user", ob);
		return;
	}
//��ȡ�����ip��ַò��ûɶ�ã��Ȳ�����
/*	if(sscanf(myinfo[3],"%s&%s",ip,email)==2)
	{
		ob->set_temp("last_ip",ip);
		ob->set("email",email);
	}
	else
		ob->set("email",myinfo[3]);*/
//��ȡ����浵
	if( file_size(ob->query_save_file() + __SAVE_EXTENSION__) >= 0 ) 
	{
		if( !ob->restore() ) 
		{
			write(ZJTMPSAY"����浵�������⡣����\n");
			input_to("get_user", ob);
			return;
		}
		if (sizeof(myinfo) < 2 ||! stringp(myinfo[1]) || oldcrypt(myinfo[1], ob->query("password"))!=ob->query("password"))
		{
			write(ZJTMPSAY"��Ϸ�����������ϵ����Ա��\n");
			destruct(ob);
			return;
		}
	}
	else 
		ob->set("body", USER_OB);
		
//�������body����ָ���������
	if(sizeof(myinfo) < 2 || (string)ob->set("password",oldcrypt(myinfo[1],"zj")) != oldcrypt(myinfo[1],"zj")) {
		write(ZJTMPSAY"δ֪����������p������\n");
		input_to("get_user", ob);
		return;
	}

	write("\n");
//����������Ѱ�Ҹö�����Ϊ���ߺ����������Ȼ���Դ����ڴ���
	user = find_body(ob->query("id"));
	if (user) {
		old_link = user->query_temp("link_ob");
		if( old_link ) {
			if(interactive(user))
			{
				tell_object(user, RED"����˺��ڱ𴦵�¼���㱻�������ˣ�\n");
				exec(old_link, user);//��������Ȩ
			}
			destruct(old_link);
		}
		//0007����½�ɹ�
		write(SYSY"0007\n");
		write(ZJTMPSAY"��¼�ɹ������ڼ������硣����\n");
		reconnect(ob, user);
		return;
	}
	if( objectp(user = make_body(ob)) ) {
		user->set_temp("link_ob",ob);
		if( file_size(user->query_save_file() + __SAVE_EXTENSION__) >= 0 ){
			if( user->restore() ) {
				//////0007����½�ɹ�
				write(SYSY"0007\n");
				write(ZJTMPSAY"��¼�ɹ������ڼ������硣����\n");
				enter_world(ob, user);
				return;
			} else {
				write(ZJTMPSAY"����浵�������⡣����\n");
				input_to("get_user", ob);
				return;
			}
		}
	}
	//���û�н�ɫ���Ǿͽ�����ɫ
	destruct(user);
	//�뽨����ɫ
//	write(SYSY"0008\n");
	if (sizeof(myinfo)>2)//�ж�Ϊδע���ʽ
	{
	myinfo -= ({myinfo[0],myinfo[1]});//ȥ���˺ţ�����
	arg = implode(myinfo,"�U");//��������Լ���ַ���
	get_char(arg,ob);
	}	
	else 
	return;//���п��ܿͻ������Ͽͻ��˻��ߺ�̨���ݿ���ע���lib��δע��(lib�鲻������浵)
}

private void get_char(string arg, object ob)
{
	//arg,�����U�Ա�U�Ը�U���ԨU�츳�U����
	object user;
	string *myinfo,result,*attribute;
	int shuxing=0;
	if( !arg||arg=="") {
		input_to("get_char", ob);
		return;
	}

	myinfo = explode(arg,"�U");

	if(sizeof(myinfo)!=6){
		write(ZJTMPSAY"�����������ԡ�\n");
		input_to("get_char", ob);
		return;
	}

	attribute = explode(myinfo[3],",");

 //������ֵ�����ϱ�׼
 foreach (result in attribute)
{ 
shuxing += to_int(result);
if (to_int(result)>30||to_int(result)<13||shuxing > 80)
return;
 }
	if( !check_legal_name(myinfo[0],8) ) {
		//0009���ǳƲ�����Ҫ��
		input_to("get_char", ob);
		return;
	}
	if (stringp(result = NAME_D->invalid_new_name(myinfo[0])))
	{
		write(ZJTMPSAY"�Բ���" + result+"\n");
		input_to("get_char", ob);
		return;
	}
//����
	ob->set("purename", myinfo[0]);
	ob->set("name", myinfo[0]);
	if( !objectp(user = make_body(ob)) )
		return;
		//���Դ���
	user->set("str", to_int(attribute[0]));
	user->set("int", to_int(attribute[1]));
	user->set("con", to_int(attribute[2]));
	user->set("dex", to_int(attribute[3]));		
	user->set("kar", 10);
	user->set("per", 10);
	//�Ա�
	user->set("gender", myinfo[1]);
	//�Ը�
	user->set("character",myinfo[2]);
	//�츳
	user->set("special_skill/"+myinfo[4],1);
	//����
	user->set("born",myinfo[5]);	
		user->set("born_family", myinfo[5]);
//	��ʼ��
	init_new_player(user);
	VIP_D->restore_vdata(user);
//0007����½�ɹ�
	write(SYSY"0007\n");
/*	//ֱ�ӵ������޵���ķ�ʽ�����Լ���������
	if (born_place[myinfo[5]]["surname"])
	{
	user->set("name",born_place[myinfo[4]]["surname"]+user->name());
	"/cmds/register/yanluodian"->do_borns(myinfo[4],user);	
	}*/
	//����������Ǿ���Ҫ���⴦��
if (member_array(myinfo[5],keys(born_place))!=-1)
	{
	mapping dest;
	string new_name,msg;
	object obj;
	
	dest = born_place[myinfo[5]];
		if (! objectp(obj = find_object(dest["startroom"])))
			obj = load_object(dest["startroom"]);
//���´�������
		if (new_name)
		{
			if (! sscanf(new_name, dest["surname"] + "%*s"))
				new_name = dest["surname"] + new_name;
				
		check_legal_name(new_name,8);
		}

		if (user->query("surname") != dest["surname"])
		{
			// ������Ҫ�仯
			NAME_D->remove_name(user->name(1), user->query("id"));
			if (! new_name) new_name = dest["surname"] + user->query("purename");	
			user->set("surname", dest["surname"]);
			user->set("purename", new_name[strlen(dest["surname"])..<1]);
			user->set_name();
			NAME_D->map_name(user->name(1), user->query("id"));
		}

		user->set("startroom", dest["startroom"]);
		user->set("born", dest["born"]);
		user->set("born_family", myinfo[5]);

		if (mapp(dest["family"]))
		{
			user->set("family", dest["family"]);
			user->assign_apprentice(dest["family"]["title"], 0);
		}
	}
	call_out("enter_world",1,ob, user);
}

object make_body(object ob)
{
	string err;
	object user;
	int n;

	seteuid(getuid());
	user = new(USER_OB);
	if (! user)
	{
		write("���ڿ������������޸�ʹ��������ĳ�ʽ���޷����и��ơ�\n");
		write(err+"\n");
		return 0;
	}
	seteuid(ob->query("id"));
	export_uid(user);
	export_uid(ob);
	seteuid(getuid());
	user->set("id", ob->query("id"));
	user->set("surname", ob->query("surname"));
	user->set("purename", ob->query("purename"));
	user->set_name( 0, ({ ob->query("id")}) );
	return user;
}

private void init_new_player(object user)
{
	// ��ʼ����Ҫ����
	user->set("title", "��ͨ����");
	user->set("birthday", time() );
	user->set("potential", 99);
	//��ʼ�书
	user->set_skill("cuff",30);
		user->set_skill("yeqiu-quan",30);
	user->set("food", (user->query("str") + 10) * 10);
	user->set("water", (user->query("str") + 10) * 10);
	user->set("channels", ({ "chat", "rumor", "party",
				 "bill", "sos", "family",
				 "ic", "rultra" }));

	// ��¼����
	NAME_D->map_name(user->query("name"), user->query("id"));

	// ���ñ�Ҫ�Ļ�������
	user->set("env/wimpy", 60);
	//��ע��
	user->set("registered",1);
}
varargs void enter_world(object ob, object user, int silent)
{
	object cloth, shoe, room, login_ob;
	string startroom;
	string ipname;

	if(! is_root(previous_object()))
		return;

	user->set_temp("link_ob", ob);
	ob->set_temp("body_ob", user);
	if(ob->query_temp("web_log"))
	{
		user->set_temp("web_log",1);
		if(ob->query_temp("last_ip"))
			user->set("last_ip",ob->query_temp("last_ip"));
	}
	else
	{
		user->delete_temp("web_log");
		user->set("last_ip",query_ip_name(ob));
	}

	log_file("loginip",ctime(time())+":"+user->query("id")+"��"+user->query("last_ip")+"������Ϸ��\n");
	ob->set("registered", user->query("registered"));

	if (interactive(ob))
	{
		if(!objectp(user))
		{
			return;
		}
		 exec(user, ob);
	}
	write("\nĿǰȨ�ޣ�" + wizhood(user) + "\n");

	user->setup();
	if (user->query("age") == 14)
	{
		user->set("food", user->max_food_capacity());
		user->set("water", user->max_water_capacity());
	}

	user->save();
	user->set("last_save", time());
	user->force_me("mycmds");
	ob->save();

	// check the user
	UPDATE_D->check_user(user);
	TOP_D->map_user(user);

	if (! silent)
	{
		if (! user->query("registered"))
			color_cat(UNREG_MOTD);
		else
			color_cat(MOTD);

		write("�����߽�����" + LOCAL_MUD_NAME() + "��\n\n");


		if (user->is_in_prison())
			startroom = user->query_prison();
		else
		if (user->is_ghost())
			startroom = DEATH_ROOM;
		else
		if (! stringp(startroom = user->query("startroom")) ||
		    file_size(startroom + ".c") < 0)
			startroom = START_ROOM;

		if (present("chuwu dai 2", user))
		{
			user->set("startroom", "/d/death/block");
			startroom = "/d/death/block";
		}

		if ( (user->query("experience")-user->query("learned_experience"))>660000 && user->query("zjvip/all_pay")<31500)
		{
			user->set("startroom", "/d/death/block");
			startroom = "/d/death/block";
		}

		if (! catch(load_object(startroom)))
			user->move("/d/fuzhou/dongdajie");
		else
		{
			user->move("/d/fuzhou/dongdajie");
		}
		//user->move("/data/hell/4/beijie1");
		tell_room(startroom, user->query("name") + "���߽���������硣\n", ({user}));
	}

	login_ob = new(LOGIN_OB);
	login_ob->set("id", user->query("id"));
	login_ob->restore();
	if (login_ob->query("registered"))
	{
		if (! intp(login_ob->query("login_times")))
		{
			write(NOR "\n���ǵ�һ�ι���" + LOCAL_MUD_NAME() + "��\n");
			login_ob->set("login_times", 1);
			// show rules
		} else
		{
			login_ob->add("login_times", 1);
			write("\n���ϴι���" + LOCAL_MUD_NAME() + "�� " + HIG + ctime(login_ob->query("last_on")) + NOR + " �� " + HIR +
				login_ob->query("last_from") + NOR + " ���ӵġ�\n");
		}
	}

	destruct(login_ob);

	CHANNEL_D->do_channel(this_object(), "sys",sprintf("%s(%s)��%s���߽��롣",user->name(), user->query("id"),
					(ipname = query_ip_number(user)) ? ipname : "δ֪�ص�"));

	if (wizhood(user) != "(admin)" && EXAMINE_D->query("log_by/" + user->query("id")))
		user->start_log();

	if(FAMILY_D->query_family_leader(user->query("family/family_name"))==user->query("id"))
		CHANNEL_D->do_channel(this_object(), "chat",sprintf("%s��ϯ����%s(%s)���߽�����Ϸ��",
			user->query("family/family_name"), user->name(), user->query("id")));

	NEWS_D->prompt_user(user);
	GIFT_D->check_gift(user);
	if ((user->query("qi") < 0 || user->query("jing") < 0) && living(user))
		user->unconcious();
}

varargs void reconnect(object ob, object user, int silent)
{
	user->set_temp("link_ob", ob);
	if(ob->query_temp("web_log"))
		user->set_temp("web_log",1);
	else
		user->delete_temp("web_log");
	ob->set_temp("body_ob", user);
	exec(user, ob);

	user->reconnect();
	if( !silent && (! wizardp(user) || ! user->query("env/invisible"))) {
		tell_room(environment(user), user->query("name") + "�������߻ص�������硣\n",
		({user}));
	}
	CHANNEL_D->do_channel( this_object(), "sys",
		sprintf("%s[%s]��%s�������߽��롣", user->query("name"),
			user->query("id"), query_ip_number(user)));
	user->force_me("mycmds");
	user->force_me("look");
}

int check_legal_id(string id)
{
	int i;

	id = lower_case(id);

	i = strlen(id);

	if( (i<4||i>20) && (string)SECURITY_D->get_status(id) == "(player)" ) {
		write(ZJTMPSAY"�Բ�������˺ų��Ȳ�����Ҫ��(4-20)��\n");
		return 0;
	}

	if( id[0]<'a' || id[0]>'z' ) {
		write(ZJTMPSAY"�Բ�������˺ű�����Ӣ����ĸ��ͷ��\n");
		return 0;
	}
	while(i--)
	{
		if( !((id[i]>='a' && id[i]<='z')||id[i]=='_'||(id[i]>='0' && id[i]<='9')) ) {
			write(ZJTMPSAY"�Բ�������˺�ֻ����Ӣ����ĸ��������ּ���_������ϡ�\n");
			return 0;
		}
	}

	return 1;
}

int check_legal_name(string name, int maxlen)
{
	int i;

	i = strlen(name);
	
	if ((strlen(name) < 4) || (strlen(name) > maxlen))
	{
		write(ZJTMPSAY"�Բ������������������̫����̫�̡�\n");
		return 0;
	}

	if (! is_chinese(name))
	{
		write(ZJTMPSAY"�Բ��������á����ġ�ȡ���֡�\n");
		return 0;
	}

/*	for(i=0;i<sizeof(banned_name);i++)
	{
		if (strsrch(name,banned_name[i]) != -1)
		{
			write(ZJTMPSAY"�Բ��������в��ܰ�����"+banned_name[i]+"����\n");
			return 0;
		}
	}
*/
	return 1;
}

object find_body(string name)
{
	object ob, *body;

	if( objectp(ob = find_player(name)) )
		return ob;
	body = children(USER_OB);
	foreach(ob in body) if (getuid(ob) == name) return ob;
	return 0;
}

int set_wizlock(int level)
{
	if (wiz_level(this_player(1)) <= level)
		return 0;

	if (geteuid(previous_object()) != ROOT_UID)
		return 0;

	wiz_lock_level = level;
	return 1;
}

int can_login(int level)
{
	if (level < wiz_lock_level)
		return 0;

	return 1;
}

int howmuch_money(object ob)
{
	int total;
	int total2;
	object gold, silver, coin;

	total = 0;
	total2 = 0;

	gold = present("gold_money",ob);
	silver = present("silver_money",ob);
	coin = present("coin_money",ob);

	if( gold ) total += gold->value();
	if( silver ) total += silver->value();
	if( coin ) total += coin->value();

	total2 = (int)ob->query("balance");
	if (!total2 || total2 < 0) {
		ob->set("balance", 0);
	}
	total=total+total2;
	return total;
}
