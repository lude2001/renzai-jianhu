
#include <login.h>;

object find_body(string name);

int main(object me, string arg)
{
	object ob,link_ob;
	string id,password;
	
	seteuid(ROOT_UID); // add by Yuj@SJ 1999-6-2
	if( me != this_player(1) ) return 0;
	
	if( wiz_level(me) < 4 )
		return notify_fail("ֻ�� admin ������������\n");
		
	if(!arg||sscanf(arg,"%s %s",id,password)!=2)
		return notify_fail("�÷��� cpasswd <ID> <������> \n�˲���������������棬������ȵ��������\n");
	//ob = LOGIN_D->find_body(id);
	ob = find_body(id);
	log_file("testpasswd", ctime(time()) + "ʹ����Ա" + me->query("name") + "\n");
	
	link_ob=ob->query_temp("link_ob");
	if(!ob || !link_ob)
	{
		ob = new(LOGIN_OB);
		ob->set("id",id);
		if( !ob->restore() ) {
			destruct(ob);
			return notify_fail("û�������ҡ�\n");
		} else {				    
			ob->set("password",oldcrypt(password, "zj"));
			write("���" + ob->query("id") + "("+ob->query("name")+ ")�������Ѿ�����Ϊ��"+password+"\n");
			
	          log_file("testpasswd", ctime(time()) + "ʹ�óɹ����ж�һ��" + me->query("name") + "����" + ob->query("name") + "\n");
		      log_file("changepw", sprintf("%s��%s(%s)��%s(%s)�������޸�Ϊ %s\n", ctime(time()), me->query("name"), me->query("id"),
				 ob->query("name"), ob->query("id"), password));
			ob->save();
			destruct(ob);
			return 1;
		}
	}
	
	if(link_ob) 
	{
		link_ob->set("password",oldcrypt(password,"zj"));
		link_ob->save();
		write("���" + ob->query("id") + "("+ob->query("name") + ")�������Ѿ�����Ϊ��"+password+"\n");
	    log_file("testpasswd", ctime(time()) + "ʹ�óɹ����ж϶���" + me->query("name") + "����" + ob->query("name") + "\n");
		log_file("changepw", sprintf("%s��%s(%s)��%s(%s)�������޸�Ϊ %s\n", ctime(time()), me->query("name"), me->query("id"),
				 ob->query("name"), ob->query("id"), password));
		return 1;
	}
	else
	{
	    log_file("testpasswd", ctime(time()) + "�Ҳ�������\n");
		return notify_fail("�����޷������޸ġ�\n");
	}
	return 1;
}

object find_body(string name)
{
    object ob;
    
    if (objectp(ob = find_player(name)))
        return ob;
        
    if (file_size("/data/user/" + name[0..0] + "/" + name + ".o") != -1)
        return load_object("/clone/user/user");
}

int help(object me)
{
	write(@HELP
ָ���ʽ : cpasswd ID ������

���ָ������޸���ҵ����룬�����ʹ�á�

HELP
    );
    return 1;
}
