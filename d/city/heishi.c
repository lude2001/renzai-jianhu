// by ranger_����
// heishi.c

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", "�����Ǻ��У���Ʒ���׵ĳ�����");
	set("exits", ([




		"northwest":__DIR__"guangchang",
	]));
	set("objects", ([
		__DIR__"npc/shenyi" : 1,
		__DIR__"npc/heixin" : 1,
		__DIR__"npc/baoshishangren" : 1,
	]));
	set("action_list", ([
		"������Ʒ" : "jishou",
		"��Ʒ�б�" : "jylist",
		"��ѡ�Ը�" : "xingge",
		"����ϴ��" : "xidian",
		//"������Ʒ" : "huishou"
	]));
	set("no_fight","1");
	set("no_steal", "1");
	set("no_sleep_room", "1");
	setup();
}

void init()
{
	add_action("do_stock", "jishou");
	add_action("do_buy", "jybuy");
	add_action("do_list", "jylist");
	add_action("do_cha", "jychakan");
	add_action("do_cha", "jychakan");
	add_action("do_unstock", "quhui");
	add_action("do_effect", "effect");
	add_action("do_xingge","xingge");
	add_action("do_uses","xidian");
	add_action("do_huishou","huishou");
			
}

int do_stock(string arg)
{
	tell_object(this_player(),SALE_D->do_stock(this_player(),arg)+"\n");
	return 1;
}

int do_buy(string arg)
{
	if (this_player()->query("combat_exp") < 1000000)
	{
		tell_object(this_player(), "��ľ������100���޷�������Ʒ��\n");
		return 1;
	}
	tell_object(this_player(),SALE_D->do_buy(this_player(),arg)+"\n");
	return 1;
}

int do_cha(string arg)
{
	tell_object(this_player(),SALE_D->do_cha(this_player(),arg)+"\n");
	return 1;
}

int do_list(string arg)
{
//	return notify_fail(OKSAY"������ʱ�رգ�\n");
	if(!arg)
		arg = "ȫ�� 1";
	tell_object(this_player(),SALE_D->do_list(this_player(),arg)+"\n");
	return 1;
}

int do_unstock(string arg)
{
	tell_object(this_player(),SALE_D->do_unstock(this_player(),arg)+"\n");
	return 1;
}


int do_xingge(string arg)
{
object me = this_player();
tell_object(me,ZJOBLONG"��ѡ���Ը񣬵�һ����ѣ�֮��ÿ�ο۷�200Ԫ����\n"
		ZJOBACTS2+ZJMENUF(2,2,6,30)+
        "������:effect ������"ZJSEP
		"��������:effect ��������"ZJSEP
		"���ռ�թ:effect ���ռ�թ"ZJSEP
		"�ĺ�����:effect �ĺ�����\n");
	return 1;
}


int do_effect(string arg)
{
	object me = this_player();
	if (me->query("xixingge")&&me->query("yuanbao") < 200)
	{
	tell_object(me,HIR"���Ԫ��������������"NOR"\n");		
		return 1;
	}
	if (me->query("character")==arg)
		{
	tell_object(me,HIR"��ѡ�����������Ը�һ���ģ�"NOR"\n");		
		return 1;
	}
	if (arg=="������") 
	 me->set("character", "������");
	else
	 if (arg=="��������") 
	   me->set("character", "��������");

	else 
	if (arg=="�ĺ�����") 
	 me->set("character", "�ĺ�����");

	else 
	if (arg=="���ռ�թ") 
	me->set("character", "���ռ�թ");
		else 	
		{
	tell_object(me,HIR"\n�����ڴ����Ը�"NOR"\n");		
	return 1;
		}
	  tell_object(me,"�Ը�ת���ɹ�!\n");
	  if (me->query("xixingge"))
	  {	  me->add("yuanbao",-200);
    tell_object(me,"200Ԫ���ѿ۳�!\n");
	  }
	  me->set("xixingge",1);
    return 1;
}

varargs int do_uses(string arg)
{
	mapping shuxing=([]), my;
	string *sname, str, line;
	int i;
	int max_sx, max_sx2;
	int tmpstr, tmpint, tmpcon, tmpdex;
	object me = this_player();
		
	if (!me->query("xidian")) {
		tell_object(me, "�㵱ǰ�����������һ�Ρ�\n");
	}
	if (me->query("xidian") && me->query("yuanbao") < 200)
	{
		return notify_fail("���Ԫ��������\n");
	}
	if(!arg) {
		str = ZJOBLONG+ "����������·�������������������ѡ��һ��ϴ��������غ���Ų����𣬵�һ�����,�����շ�200Ԫ����\n";
		str += ZJOBACTS2+ZJMENUF(3,3,9,30);
		
		str += sprintf("ȷ��:xidian -yes" + ZJSEP);
		str += sprintf("ȡ��:look");
		tell_object(me, str + "\n");
	 return 1;
	} else if(arg == "-yes") {
		max_sx = (me->query("con") + me->query("dex")+me->query("int")+me->query("str"));
				
		write(INPUTTXT(HIR"ע��ֵ������13-100֮��"ZJBR"�ܺͲ��ܳ��������е�����"+max_sx+"�㡣"
											+NOR+ZJBR+HIW+"(���� ���� ���� ��)"
											+NOR+ZJBR+HIY+"(����20 20 20 20���м��Կո����)"+NOR+
												ZJBR+"�������������������","xidian $txt#")+"\n");
	} else if(sscanf(arg, "-yes %d %d %d %d", tmpstr, tmpint, tmpcon, tmpdex) == 4) {
		if (tmpstr < 13 || tmpstr >100
			|| tmpint < 13 || tmpint >100
			|| tmpcon < 13 || tmpcon >100
			|| tmpdex < 13 || tmpdex >100) {
				write(HIR"����һ�����벻��(13-100)��Χ֮�ڡ�"NOR"\n");
				return 1;
			}
		my = me->query_entire_dbase();
		max_sx = (my["con"] + my["dex"]+my["int"]+my["str"]);

			
		if (tmpstr+ tmpint+ tmpcon+ tmpdex != max_sx) {
			write(HIR"���������������������Ŀǰ�����������ԡ�"NOR"\n");
			return 1;
		}
		
		line = sprintf("str(%d)int(%d)con(%d)dex(%d)", tmpstr, tmpint, tmpcon, tmpdex);
		
		max_sx2 = tmpstr+ tmpint+ tmpcon+ tmpdex;
		
		my["str"]= tmpstr;
		my["int"]= tmpint;
		my["con"]= tmpcon;
		my["dex"]= tmpdex;
		
		CHANNEL_D->do_channel(present("shenyi",this_object()), "chat", "���գ�"+me->name()+"���Ҵ����������壡");
		message_vision(HIY"$N�ں������������壡"NOR"\n", me);
		tell_object(me, HIY"�������ܳɹ���"NOR"\n");
		
		//�����������ļ����Ƿ����Ҫ�󣬲����ϵ�ɾ��
		UPDATE_D->check_skill(me);
		me->save();
		log_file("/cmds/xidian", sprintf("%s  ϴ��=%s  �ܼ�=str(%d)int(%d)con(%d)dex(%d) �ܹ�(%d/%d��) ϴ��ʱ�䣺%s\n", 
											me->name()+"("+my["id"]+")", line, tmpstr, tmpint, tmpcon, tmpdex, max_sx, max_sx2, CHINESE_D->chinese_date(time(), 2)));
	if (me->query("xidian"))
		me->add("yuanbao",-200);
		
	 me->set("xidian", 1);
	} else if(sscanf(arg, "%d %d %d %d", tmpstr, tmpint, tmpcon, tmpdex) == 4) {
		
		str = ZJOBLONG+ HIC"������ã�"HIG"����("+tmpstr+") ����("+tmpint+") ����("+tmpcon+") ��("+tmpdex+")"NOR
				+ZJBR"��������·�������������"ZJBR
										+"������ѡ�����һ�����ѣ�һ��ϴ�㣬�����ɻָ���������غ���Ų�����"NOR"\n";
		str += ZJOBACTS2+ZJMENUF(3,3,9,30);
		
		str += sprintf("ȷ��:xidian -yes " +tmpstr+" "+ tmpint+" "+ tmpcon+" "+ tmpdex+ ZJSEP);
		str += sprintf("ȡ��:look");
		tell_object(me, str + "\n");
	} else 
		me->force_me("xidian");
	return 1;
}

//���յ�Ԫ������ԭ�۸����10
int jiage(object ob)
{
  if (ob->query("yuanbao")>10)
 return ob->query("yuanbao")/5;
 else
 if (ob->query("yuanbao") >=5)
 return 1;
 
 return 0;
}

int do_huishou(string arg)
{
    string msg,id_name;
	object me = this_player();
	object obj;
	int amount;
     if (!arg)
     {
	object *pobj;
	pobj = all_inventory(me);
	pobj = filter_array(pobj,(: jiage($1) :));
	
	if (!sizeof(pobj))
	return 1;
	
	msg = ZJOBLONG"��ѡ������Ҫ���յ���Ʒ��\n"
		ZJOBACTS2+ZJMENUF(2,2,6,30);
		
	 foreach (obj in pobj)
	 {
	  amount = obj->query_amount()?obj->query_amount():1;
	  msg += sprintf("%d��%s"ZJBR"(%dԪ��):huishou %s"ZJSEP,amount,obj->query("name"),jiage(obj),obj->query("id"));
     }
     
	  msg += "ȡ��:look\n";
	 tell_object(me,msg);
	 return 1;
	}
	//Ĭ����string ��Ҫ����ת����int
	if (sscanf(arg, "%s==%s", id_name, arg) == 2)
	{
	
	 obj = present(id_name,me);
	 amount = to_int(arg);
	 if (amount < 1)
	 {
	     write("�����������������롣\n");
	     return 1;
	 }
	 
	 if (!objectp(obj))
	 return notify_fail("��û�и���Ʒ\n");
	 
	 if (obj->query_amount()<amount)
	 return notify_fail("�����û����ô��"+obj->query("name")+"\n");
	 
	 log_file("pay/huishou", ctime(time()) + "  " + me->query("name") + me->query("id") + "������" + chinese_number(amount) + "��" + obj->query("name") + "\n");
     //Ϊɶ��Ҫ��ǰ���أ������Ʒ����û�����أ�Сǧ��ע��һ��Ŷ��
     //emmmmm����
     me->add("yuan_bao",jiage(obj)*amount);
     obj->add_amount(-amount);
     
      write("��ɹ������˸���Ʒ\n");
      return 1;
      
	}
	
	if (arg)
	{
	 obj = present(arg,me);
	 amount = obj->query_amount();
	 
	 if (amount)
	 return notify_fail(INPUTTXT("����"+amount+"�ݣ�������Ҫ���ն��ٷ�"+obj->query("name"),"huishou "+arg+"==$txt#")+"\n");
	 	
	me->add("yuan_bao",jiage(obj));
	log_file("pay/huishou", ctime(time()) + "  " + me->query("name") + me->query("id") + "������һ��" + obj->query("name") + "\n");
//	destruct(obj);
	destruct(obj);
	write("��ɹ������˸���Ʒ\n");
	return 1;
	}
	return 1;
}

int query_autoload() { return 1; }


