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
    "你", "你", "我", "他", "她", "它","东方",
    "爸", "爷", "　", "妈","她妈","他妈","操操","fuck","下阴","阴部","口交","性交","阴唇","阴道",
    "屎", "尿", "粪","操你","日你","大爷","老妈","干你","操妈",
"自己","杀手","闪电","雪人","逍遥","我们","你们","他们","咱们","大家","某人","尸体",
"天神","总管","龙神","仙人","巫师","门客","玩家","书","书剑","名字待定","中神通","蒙面",
"蒙面人","刺客","忍者","镖师","鬼魂","头颅","杀人犯",
// Mud 地名，门派名
"衡山","华山","嵩山","恒山","泰山","雪山","黄山","天山","西域","苗疆","东北","中原",
"南疆","长江","黄河","中国","中华","昆仑山","长白山","白驼山","武当山","峨嵋山",
"冰火岛","桃花岛","黑木崖",
"少林","丐帮","明教","密宗","古墓","全真","铁掌","大理","白驼","桃花","星宿",
"天龙寺","大轮寺","五毒教","正义","邪恶","五岳剑派","日月神教","官府","武林",
"少林寺","武当派","铁掌帮","普通百姓","峨嵋派","姑苏慕容","古墓派","华山派","嵩山派",
"明教","神龙教","星宿派",
// 重要人物名字
"金庸","邓小平","江泽民","毛泽东","朱榕基","皇帝", "皇上","总理", "主席", "习近平", "李克强",
 "管理员", "巫师", "干部",
// 小说人物
"张三丰","张无忌","郭靖","杨过","令狐冲","胡斐","苗人凤","韦小宝","袁承志","胡一刀",
"陈家洛","段誉","萧锋","乔锋","虚竹","东方不败","欧阳锋","洪七公","黄药师","段皇爷",
"一灯大师","王重阳","周伯通","黄蓉","风清扬","独孤求败",
// 脏话
"统一","法轮","法轮研究","法轮大","吃人","他妈的","去你的","操你妈","干你娘","废物",
"混蛋","坏蛋","杀人","抢劫","强奸","妓女","台独","领导","中央","屁眼","屁股","裸体",
"放屁","鸡巴","阴道","婊子","你丫","日你","赤佬","瘪三","傻逼","蠢蛋","操他","我操",
"太监","宦官","阉割","阉人","鸡", "奸淫", "淫荡", "轮奸", "奸", "三级", "政治",
//特殊名字
"淑女","君子",

});
//出生地，有一些世界需要使用mapping处理
mapping born_place = ([
	"欧阳世家" : ([ "born"      : "西域人氏",
			"surname"   : "欧阳",
			"startroom" : "/d/baituo/dating",
		     ]),
	"关外胡家" : ([ "born"      : "关外人氏",
			"surname"   : "胡",
			"startroom" : "/d/guanwai/xiaowu",
		     ]),
	"段氏皇族" : ([ "born"      : "大理人氏",
			"surname"   : "段",
			"startroom" : "/d/dali/wangfugate",
		     ]),
	"慕容世家" : ([ "born"      : "江南人氏",
			"surname"   : "慕容",
			"startroom" : "/d/yanziwu/cuixia",
		     ]),
]);

// 内部调用的函数
private void get_user(string arg, object ob);
private void get_char(string arg, object ob);
void jiance(string arg,object ob,string str);
private void init_new_player(object user);

// 可以被外部调用的函数
object  make_body(object ob);
varargs void enter_world(object ob, object user, int silent);
varargs void reconnect(object ob, object user, int silent);
object find_body(string name);
int check_legal_id(string arg);
int check_legal_name(string arg, int maxlen);

void create() 
{
	seteuid(ROOT_UID);
	set("channel_id", "连线");
}

void logon(object ob)
{
	string str;
	if (BAN_D->is_banned(query_ip_name(ob)) == 1) {
		write(ZJTMPSAY"你的地址在本 MUD 不受欢迎。\n");
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
	write("版本验证成功\n");
	input_to("get_user", ob);
}

private void get_user(string arg, object ob)
{
	/*arg,demouser||ads123||独孤求败||男||光明磊落||20,13,30,24||trick||世家
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

//重新传送
	if( !arg||arg=="") {
		input_to("get_user", ob);
		return;
	}

	// if (time() < 1653134400)
	// {
	// 	write(ZJTMPSAY + "2022.5.21晚上八点开放。\n");
	// 	return;
	// }
//以ceshi888为老版测试账号
	myinfo = explode(arg,"║");

if (member_array(myinfo[0],fengjin) != -1)
{
    	write(ZJTMPSAY"该账号已被永久封禁。\n");
		return;
}
//用于测试的约定字符
if (myinfo[0]=="ceshi888")
{
write(ZJTMPSAY+myinfo[0]+"账号登录\n");
arg = myinfo[0]+"║123456║小伙子║男性║心狠手辣║20,20,20,20║self║段氏皇族";
	myinfo = explode(arg,"║");	
	}


	if( !check_legal_id(lower_case(myinfo[0]))) {
		//0001，ID不合法
		write(myinfo[0]+"\n");
		input_to("get_user", ob);
		return;
	}

	myinfo[0] = lower_case(myinfo[0]);

/*
	if (1) {
		write(ZJTMPSAY"调试中暂时不能登陆。\n");
		input_to("get_user", ob);
		return;
	}
*/
	if (wiz_level(myinfo[0]) < wiz_lock_level)
        {
		write(sprintf(ZJTMPSAY"对不起，%s正在维护中，请稍后登录。。。\n",LOCAL_MUD_NAME()));
		input_to("get_user",ob);
		return;
	}
//赋予人物id
	if( (string)ob->set("id", myinfo[0]) != myinfo[0]) {
		write(ZJTMPSAY"未知错误，请重试i。。。\n");
		input_to("get_user", ob);
		return;
	}
//读取邮箱和ip地址貌似没啥用，先不理它
/*	if(sscanf(myinfo[3],"%s&%s",ip,email)==2)
	{
		ob->set_temp("last_ip",ip);
		ob->set("email",email);
	}
	else
		ob->set("email",myinfo[3]);*/
//读取人物存档
	if( file_size(ob->query_save_file() + __SAVE_EXTENSION__) >= 0 ) 
	{
		if( !ob->restore() ) 
		{
			write(ZJTMPSAY"人物存档出现问题。。。\n");
			input_to("get_user", ob);
			return;
		}
		if (sizeof(myinfo) < 2 ||! stringp(myinfo[1]) || oldcrypt(myinfo[1], ob->query("password"))!=ob->query("password"))
		{
			write(ZJTMPSAY"游戏密码错误，请联系管理员！\n");
			destruct(ob);
			return;
		}
	}
	else 
		ob->set("body", USER_OB);
		
//生成人物，body变量指代人物对象
	if(sizeof(myinfo) < 2 || (string)ob->set("password",oldcrypt(myinfo[1],"zj")) != oldcrypt(myinfo[1],"zj")) {
		write(ZJTMPSAY"未知错误，请重试p。。。\n");
		input_to("get_user", ob);
		return;
	}

	write("\n");
//在线人物中寻找该对象，因为断线后人物对象仍然可以存在内存中
	user = find_body(ob->query("id"));
	if (user) {
		old_link = user->query_temp("link_ob");
		if( old_link ) {
			if(interactive(user))
			{
				tell_object(user, RED"你的账号在别处登录，你被迫下线了！\n");
				exec(old_link, user);//交换控制权
			}
			destruct(old_link);
		}
		//0007，登陆成功
		write(SYSY"0007\n");
		write(ZJTMPSAY"登录成功，正在加载世界。。。\n");
		reconnect(ob, user);
		return;
	}
	if( objectp(user = make_body(ob)) ) {
		user->set_temp("link_ob",ob);
		if( file_size(user->query_save_file() + __SAVE_EXTENSION__) >= 0 ){
			if( user->restore() ) {
				//////0007，登陆成功
				write(SYSY"0007\n");
				write(ZJTMPSAY"登录成功，正在加载世界。。。\n");
				enter_world(ob, user);
				return;
			} else {
				write(ZJTMPSAY"人物存档出现问题。。。\n");
				input_to("get_user", ob);
				return;
			}
		}
	}
	//如果没有角色，那就建立角色
	destruct(user);
	//请建立角色
//	write(SYSY"0008\n");
	if (sizeof(myinfo)>2)//判断为未注册格式
	{
	myinfo -= ({myinfo[0],myinfo[1]});//去除账号，密码
	arg = implode(myinfo,"║");//重新连接约定字符串
	get_char(arg,ob);
	}	
	else 
	return;//很有可能客户端是老客户端或者后台数据库已注册而lib内未注册(lib查不到人物存档)
}

private void get_char(string arg, object ob)
{
	//arg,姓名║性别║性格║属性║天赋║世家
	object user;
	string *myinfo,result,*attribute;
	int shuxing=0;
	if( !arg||arg=="") {
		input_to("get_char", ob);
		return;
	}

	myinfo = explode(arg,"║");

	if(sizeof(myinfo)!=6){
		write(ZJTMPSAY"错误，请检查重试。\n");
		input_to("get_char", ob);
		return;
	}

	attribute = explode(myinfo[3],",");

 //属性数值不符合标准
 foreach (result in attribute)
{ 
shuxing += to_int(result);
if (to_int(result)>30||to_int(result)<13||shuxing > 80)
return;
 }
	if( !check_legal_name(myinfo[0],8) ) {
		//0009，昵称不符合要求
		input_to("get_char", ob);
		return;
	}
	if (stringp(result = NAME_D->invalid_new_name(myinfo[0])))
	{
		write(ZJTMPSAY"对不起，" + result+"\n");
		input_to("get_char", ob);
		return;
	}
//姓名
	ob->set("purename", myinfo[0]);
	ob->set("name", myinfo[0]);
	if( !objectp(user = make_body(ob)) )
		return;
		//属性处理
	user->set("str", to_int(attribute[0]));
	user->set("int", to_int(attribute[1]));
	user->set("con", to_int(attribute[2]));
	user->set("dex", to_int(attribute[3]));		
	user->set("kar", 10);
	user->set("per", 10);
	//性别
	user->set("gender", myinfo[1]);
	//性格
	user->set("character",myinfo[2]);
	//天赋
	user->set("special_skill/"+myinfo[4],1);
	//世家
	user->set("born",myinfo[5]);	
		user->set("born_family", myinfo[5]);
//	初始化
	init_new_player(user);
	VIP_D->restore_vdata(user);
//0007，登陆成功
	write(SYSY"0007\n");
/*	//直接调用阎罗殿里的方式不比自己处理香吗？
	if (born_place[myinfo[5]]["surname"])
	{
	user->set("name",born_place[myinfo[4]]["surname"]+user->name());
	"/cmds/register/yanluodian"->do_borns(myinfo[4],user);	
	}*/
	//如果是世家那就需要额外处理
if (member_array(myinfo[5],keys(born_place))!=-1)
	{
	mapping dest;
	string new_name,msg;
	object obj;
	
	dest = born_place[myinfo[5]];
		if (! objectp(obj = find_object(dest["startroom"])))
			obj = load_object(dest["startroom"]);
//重新处理姓名
		if (new_name)
		{
			if (! sscanf(new_name, dest["surname"] + "%*s"))
				new_name = dest["surname"] + new_name;
				
		check_legal_name(new_name,8);
		}

		if (user->query("surname") != dest["surname"])
		{
			// 名字需要变化
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
		write("现在可能有人正在修改使用者物件的程式，无法进行复制。\n");
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
	// 初始化必要属性
	user->set("title", "普通百姓");
	user->set("birthday", time() );
	user->set("potential", 99);
	//初始武功
	user->set_skill("cuff",30);
		user->set_skill("yeqiu-quan",30);
	user->set("food", (user->query("str") + 10) * 10);
	user->set("water", (user->query("str") + 10) * 10);
	user->set("channels", ({ "chat", "rumor", "party",
				 "bill", "sos", "family",
				 "ic", "rultra" }));

	// 记录名字
	NAME_D->map_name(user->query("name"), user->query("id"));

	// 设置必要的环境参数
	user->set("env/wimpy", 60);
	//已注册
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

	log_file("loginip",ctime(time())+":"+user->query("id")+"从"+user->query("last_ip")+"进入游戏。\n");
	ob->set("registered", user->query("registered"));

	if (interactive(ob))
	{
		if(!objectp(user))
		{
			return;
		}
		 exec(user, ob);
	}
	write("\n目前权限：" + wizhood(user) + "\n");

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

		write("你连线进入了" + LOCAL_MUD_NAME() + "。\n\n");


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
		tell_room(startroom, user->query("name") + "连线进入这个世界。\n", ({user}));
	}

	login_ob = new(LOGIN_OB);
	login_ob->set("id", user->query("id"));
	login_ob->restore();
	if (login_ob->query("registered"))
	{
		if (! intp(login_ob->query("login_times")))
		{
			write(NOR "\n你是第一次光临" + LOCAL_MUD_NAME() + "。\n");
			login_ob->set("login_times", 1);
			// show rules
		} else
		{
			login_ob->add("login_times", 1);
			write("\n你上次光临" + LOCAL_MUD_NAME() + "是 " + HIG + ctime(login_ob->query("last_on")) + NOR + " 从 " + HIR +
				login_ob->query("last_from") + NOR + " 连接的。\n");
		}
	}

	destruct(login_ob);

	CHANNEL_D->do_channel(this_object(), "sys",sprintf("%s(%s)由%s连线进入。",user->name(), user->query("id"),
					(ipname = query_ip_number(user)) ? ipname : "未知地点"));

	if (wizhood(user) != "(admin)" && EXAMINE_D->query("log_by/" + user->query("id")))
		user->start_log();

	if(FAMILY_D->query_family_leader(user->query("family/family_name"))==user->query("id"))
		CHANNEL_D->do_channel(this_object(), "chat",sprintf("%s首席弟子%s(%s)连线进入游戏。",
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
		tell_room(environment(user), user->query("name") + "重新连线回到这个世界。\n",
		({user}));
	}
	CHANNEL_D->do_channel( this_object(), "sys",
		sprintf("%s[%s]由%s重新连线进入。", user->query("name"),
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
		write(ZJTMPSAY"对不起，你的账号长度不符合要求(4-20)。\n");
		return 0;
	}

	if( id[0]<'a' || id[0]>'z' ) {
		write(ZJTMPSAY"对不起，你的账号必须用英文字母开头。\n");
		return 0;
	}
	while(i--)
	{
		if( !((id[i]>='a' && id[i]<='z')||id[i]=='_'||(id[i]>='0' && id[i]<='9')) ) {
			write(ZJTMPSAY"对不起，你的账号只能用英文字母或包含数字及‘_’的组合。\n");
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
		write(ZJTMPSAY"对不起，你的中文姓名不能太长或太短。\n");
		return 0;
	}

	if (! is_chinese(name))
	{
		write(ZJTMPSAY"对不起，请您用「中文」取名字。\n");
		return 0;
	}

/*	for(i=0;i<sizeof(banned_name);i++)
	{
		if (strsrch(name,banned_name[i]) != -1)
		{
			write(ZJTMPSAY"对不起，名字中不能包含【"+banned_name[i]+"】。\n");
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
