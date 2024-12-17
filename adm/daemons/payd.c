
#define DEBUGGER "no-one"

#include <net/httpd.h>
#include <net/socket.h>
#include <localtime.h>
inherit F_DBASE;

#define MAXIMUM_RETRIES	10

#define HTTP_HEADER "HTTP/1.0 %s%c"
#define DEFAULT_HEADER "Server: "+MUD_NAME+"/0.2\nMIME-version: 1.0%c"

#define log_info(x, y) log_file(x, ctime(time()) + "\n"); log_file(x, y)

int httpSock;
mapping sockets;
mapping resolve_pending;
string *months,*pay_type;

mapping bad_cmd = BAD_CMD;
mapping access_denied = ACCESS_DENIED;
mapping not_found = NOT_FOUND;
mapping bad_gateway = BAD_GATEWAY;
int persistent;

protected void setup();
void close_connection(int fd);
void set_persistent(int which);
int chonzhi_reward(object ob);
void send_message(string id,string msg);
int accesses;

mapping *pay_fix = ({
	([
		"name"		:	"Ԫ����",
		"month"		:	1,
		"daymin"	:	1,
		"daymax"	:	3,
		"pay_fix"		:	30,
	]),
	([
		"name"		:	"���˽�",
		"month"		:	1,
		"daymin"	:	24,
		"daymax"	:	24,
		"pay_fix"		:	30,
	]),
	([
		"name"		:	"����",
		"month"		:	2,
		"daymin"	:	15,
		"daymax"	:	28,
		"pay_fix"		:	30,
	]),
	([
		"name"		:	"Ԫ����",
		"month"		:	3,
		"daymin"	:	1,
		"daymax"	:	2,
		"pay_fix"		:	30,
	]),
	([
		"name"		:	"������",
		"month"		:	4,
		"daymin"	:	5,
		"daymax"	:	7,
		"pay_fix"		:	30,
	]),
	([
		"name"		:	"�Ͷ���",
		"month"		:	4,
		"daymin"	:	29,
		"daymax"	:	30,
		"pay_fix"		:	30,
	]),
	([
		"name"		:	"�Ͷ���",
		"month"		:	5,
		"daymin"	:	1,
		"daymax"	:	1,
		"pay_fix"		:	30,
	]),
	([
		"name"		:	"�ѵ���",
		"month"		:	5,
		"daymin"	:	20,
		"daymax"	:	20,
		"pay_fix"		:	30,
	]),
	([
		"name"		:	"�����",
		"month"		:	6,
		"daymin"	:	16,
		"daymax"	:	18,
		"pay_fix"		:	30,
	]),
	([
		"name"		:	"����",
		"month"		:	7,
		"daymin"	:	10,
		"daymax"	:	30,
		"pay_fix"		:	30,
	]),
	([
		"name"		:	"��Ϧ��",
		"month"		:	8,
		"daymin"	:	17,
		"daymax"	:	17,
		"pay_fix"		:	30,
	]),
	([
		"name"		:	"�����",
		"month"		:	9,
		"daymin"	:	22,
		"daymax"	:	24,
		"pay_fix"		:	30,
	]),
	([
		"name"		:	"�����",
		"month"		:	10,
		"daymin"	:	1,
		"daymax"	:	7,
		"pay_fix"		:	30,
	]),
	([
		"name"		:	"������",
		"month"		:	10,
		"daymin"	:	17,
		"daymax"	:	17,
		"pay_fix"		:	30,
	]),
	([
		"name"		:	"˫ʮһ",
		"month"		:	11,
		"daymin"	:	11,
		"daymax"	:	11,
		"pay_fix"		:	30,
	]),
	([
		"name"		:	"˫ʮ��",
		"month"		:	12,
		"daymin"	:	12,
		"daymax"	:	12,
		"pay_fix"		:	30,
	]),
	([
		"name"		:	"ʥ����",
		"month"		:	12,
		"daymin"	:	25,
		"daymax"	:	25,
		"pay_fix"		:	30,
	]),
});

int fix_pay(int amount)
{
	int rmb = amount/10;
	//��������
 if(rmb>=498&&rmb<1000) amount = (amount*12)/10;
        else if (rmb>=1000&&rmb<2000) amount = (amount * 15)/10;
        else if (rmb >= 2000) amount *= 2;
		return amount;
	
}

string is_hol()
{
	int flag,i;
	mixed today;

	today = localtime(time());
	for(i=0;i<sizeof(pay_fix);i++)
	{
		if( (today[4]+1)==pay_fix[i]["month"] && today[3]>=pay_fix[i]["daymin"] && today[3]<=pay_fix[i]["daymax"] )
		{
			return pay_fix[i]["name"];
		}
	}

	return;
}

int query_accesses()
{
	return accesses;
}

protected void create()
{ 
	set("channel_id", "��ֵ����");
	seteuid( geteuid() );
	accesses = 0;
	set_persistent(1);
	months = ({"1��","2��","3��","4��","5��","6��","7��","8��","9��","10��","11��","12��"});
	pay_type = ({"���п�","֧����","��ֵ��","�Ƹ�ͨ��","���Ǯ��","���п�","΢��֧��","�ֶ�"});
	sockets = ([]);
	resolve_pending = ([]);
	CHANNEL_D->do_channel(this_object(), "sys", "��ֵ�����Ѿ�������");
	call_out("setup", 1);
}

protected void clean_up()
{
} 

protected void setup()
{
	if ((httpSock = socket_create(STREAM, "read_callback", "close_callback")) < 0)
	{
		CHANNEL_D->do_channel(this_object(), "sys", "��ֵ���񴴽�ʧ�ܡ�");
		return;
	}
	if (socket_bind(httpSock, ZJPAYPORT) < 0) {
		socket_close(httpSock);
		CHANNEL_D->do_channel(this_object(), "sys", "��ֵ����˿ڰ�ʧ�ܡ�");
		return;
	}
	if (socket_listen(httpSock, "listen_callback") < 0) {
		socket_close(httpSock);
		CHANNEL_D->do_channel(this_object(), "sys", "��ֵ�������ʧ�ܡ�");
	}
}

string http_header(string code)
{
	return sprintf(HTTP_HEADER, code, 10)+sprintf(DEFAULT_HEADER, 10);
}

protected void store_client_info(int fd)
{
	string addr;
	int port;

	sscanf(socket_address(fd), "%s %d", addr, port);
	sockets[fd] = ([
	 "address" : addr,
	 "name" : addr,
	 "port" : port,
	 "time" : time(),
	 "write_status" : EESUCCESS
	]);
}

protected void listen_callback(int fd)
{
	int nfd;

	if ((nfd = socket_accept(fd, "read_callback", "write_callback")) < 0) {
		CHANNEL_D->do_channel(this_object(), "sys", "��ֵ�����������ʧ�ܡ�");
		return;
	}
	store_client_info(nfd);
}

void write_callback(int fd)
{
	close_connection(fd);
}

string common_date(int t)
{
	mixed* r;

	r = localtime(t);
	return sprintf("%d��%s%02d��%02d:%02d:%02d",
		r[LT_YEAR], months[r[LT_MON]], r[LT_MDAY], r[LT_HOUR],
		r[LT_MIN], r[LT_SEC]);
}

void do_get(string, string);
void do_post(int, string, string);

protected void read_callback(int fd, string str)
{
	string cmd, args, file, url;
	string *request;
	string tmp, line0, ip;
	string *ips=({
		"123.56.142.96",
	});
	if (!sizeof(str))
	{
		log_file("pay/err", common_date(time())+":�����ݡ�����("+sockets[fd]["address"]+")\n");
		return;
	}
	if(member_array(sockets[fd]["address"],ips)==-1)
	{
		log_file("pay/err", common_date(time())+":�Ƿ�IP����("+sockets[fd]["address"]+")��\n");
		close_connection(fd);
		return;
	}
	accesses++;
	request = explode(replace_string(str, "\r", ""), "\n");
	line0 = request[0];
	sscanf(line0, "%s /?%s %s", cmd, file, args);
	ip = sockets[fd]["address"];
	switch(lower_case(cmd)) {
		case "get":
			close_connection(fd);
			do_get(file, ip);
			break;
		default:
			break;
	}
}

protected void close_callback(int fd)
{
	if (fd == httpSock) {
		log_info(LOG_HTTP_ERR,"��ֵ�����쳣�رգ���������...\n");
		call_out("setup", 1);
	} else {
		map_delete(sockets, fd);
	}
}

protected void close_connection(int fd)
{
	map_delete(sockets, fd);
	socket_close(fd);
}

//��ֵ�������ݴ��������������н�������������������������ж�
//�û�id(user_id)��������(order_id)��֧������(pay_type)��֧�����(result_code)��֧�����(amount)��֧��ʱ��(pay_time)
//֧�������0-�ɹ�������ֵ-ʧ��
//֧����XX.XXԪ
//֧�����ͣ�1"���п�",2"֧����",3"��ֵ��",4"�Ƹ�ͨ��",5"���Ǯ��",6"���п�"
//user_id=luoyun&order_id=luoyun-luoyun-1167994550017&pay_type=2&result_code=0&amount=1.00&pay_time=2016-02-01%2014:29:52
void do_get(string file, string ips)
{
	string *gets,*str,username,userid,mid;
	mapping datas=([]);
	int i,type,amount,rmb,pay_fixed=0;
	object mob,mobj,ob,obj;
	mixed today;

	gets = explode(file,"&");
	for(i=0;i<sizeof(gets);i++)
	{
		if(strsrch(gets[i],"=")!=-1)
		{
			str=explode(gets[i],"=");
			if(sizeof(str)==2)
				datas[str[0]]=str[1];
		}
	}

	if(!VIP_D->query_vips("order")||(member_array(datas["order_id"],VIP_D->query_vips("order"))==-1))
	{
		sscanf(datas["pay_type"],"%d",type);
		sscanf(datas["amount"],"%d",rmb);
		amount = rmb*10;
		amount = fix_pay(amount);
		VIP_D->add_order(datas["order_id"]);
		datas["user_id"] = lower_case(datas["user_id"]);
		if(!(obj=find_player(datas["user_id"])))
		{
			ob = new(LOGIN_OB);
			ob->set("id",datas["user_id"]);
			ob->set("body", USER_OB);
			obj = LOGIN_D->make_body(ob);
			destruct(ob);
			if(obj->restore())
			{
				obj->setup();
				username = obj->query("name");
				obj->add("zjvip/all_pay",rmb);
				if(obj->query("zjvip/tgm"))
					VIP_D->set_qian(obj->query("zjvip/tgm")+"/"+obj->query("id"),VIP_D->query_qian(obj->query("zjvip/tgm")+"/"+obj->query("id"))+rmb);
				obj->add("yuanbao",amount);
				obj->add("chonzhi/rmb",rmb);//�����ĳ�ֵ��ֵ
				obj->add("cxpay/gongxian",rmb);
			//	obj->add("reputation",amount*50);
				if(stringp(mid=obj->query("zjvip/master")))
				{
					if(!(mobj=find_player(mid)))
					{
						mob = new(LOGIN_OB);
						mob->set("id",mid);
						mob->set("body", USER_OB);
						mobj = LOGIN_D->make_body(mob);
						destruct(mob);
						if(mobj->restore())
						{
							mobj->setup();
							mobj->add("zjvip/dizi_pay",rmb);
							mobj->save();
						}
						destruct(mobj);
					}
					else if(mobj)
					{
						mobj->add("zjvip/dizi_pay",rmb);
						mobj->save();
					}
				}
				obj->save();
			}
			destruct(obj);
		}
		else if(obj)
		{
			username = obj->query("name");
			obj->add("zjvip/all_pay",rmb);
			if(obj->query("zjvip/tgm"))
				VIP_D->set_qian(obj->query("zjvip/tgm")+"/"+obj->query("id"),VIP_D->query_qian(obj->query("zjvip/tgm")+"/"+obj->query("id"))+rmb);
				obj->add("yuanbao",amount);
				obj->add("chonzhi/rmb",rmb);//�����ĳ�ֵ��ֵ
				obj->add("cxpay/gongxian",rmb);
			//	obj->add("reputation",amount*50);
			if(stringp(mid=obj->query("zjvip/master")))
			{
				if(!(mobj=find_player(mid)))
				{
					mob = new(LOGIN_OB);
					mob->set("id",mid);
					mob->set("body", USER_OB);
					mobj = LOGIN_D->make_body(mob);
					destruct(mob);
					if(mobj->restore())
					{
						mobj->setup();
						mobj->add("zjvip/dizi_pay",rmb);
						mobj->save();
					}
					destruct(mobj);
				}
				else if(mobj)
				{
					mobj->add("zjvip/dizi_pay",rmb);
					mobj->save();
				}
			}
			obj->save();
		}
		chonzhi_reward(obj);
		CHANNEL_D->do_channel(this_object(), "sys",sprintf("%s(%s)ͨ��%s��ֵ%sԪ%s��\n",username,datas["user_id"],pay_type[type-1],datas["amount"],datas["result_code"]=="0"?"�ɹ�":"ʧ��"));
		log_file("pay/success", sprintf("%s:%s(%s)ͨ��%s��ֵ%sԪ%s��������%s����ˮ��%s��֧��ʱ��%s��\n",common_date(time()),username,datas["user_id"],pay_type[type-1],datas["amount"],datas["result_code"]=="0"?"�ɹ�":"ʧ��",datas["order_id"],datas["trade_id"],replace_string(datas["pay_time"],"%20"," ")));
	}
}
void send_message(string id,string msg){
    object ob1;
    ob1 = find_player(id);
    tell_object(ob1,msg+"\n");
}
void set_persistent(int which)
{
	persistent = which;
}

int chonzhi_reward(object ob)
{
object reward_obj;
//int reward_yuanbao;
     if (ob->query("chonzhi/rmb")>=6&&!ob->query("chonzhi/obj/bei"))
   {  
      ob->set("chonzhi/obj/bei",1);
     reward_obj = new("/clone/vip/xumibei");//���ֱ�             
       if (objectp(reward_obj))
      {
      reward_obj->move(ob);
      tell_object(ob,"�������Ա���Ϸ�Ľܳ����ף��ش˽�����"+reward_obj->query("name")+"Ŷ����ע����ա�\n");
      }
   }
   
   if (ob->query("chonzhi/rmb")>=98&&!ob->query("chonzhi/obj/butian"))
   {
   ob->set("chonzhi/obj/butian",1);
   reward_obj = new("/clone/vip/butian");//����ʯ
     if (objectp(reward_obj))
      {
      reward_obj->move(ob);
      tell_object(ob,"�������Ա���Ϸ�Ľܳ����ף��ش˽�����"+reward_obj->query("name")+"Ŷ����ע����ա�\n");
      }
   }       
      return 1;
}