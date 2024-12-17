#include <login.h>

object find_body(string name);

int main(object me, string arg)
{
	object ob, link_ob, obj;
	string id;
	int amount;
	string order;

	log_file("cxpay", ctime(time()) + "  ʹ����" + me->query("name") + "(" + me->query("id") + ")  ����" + arg + "��\n");
	seteuid(ROOT_UID);
	if (me != this_player(1)) return 0;

	if (wiz_level(me) < 4 )
		return notify_fail("ֻ�� admin ������������\n");
	// if(me->query("id")!="paycx")
	// 	return notify_fail("ֻ�� admin ������������\n");

	if (!arg || sscanf(arg, "%s %d %s", id, amount, order) != 3)
	{
		log_file("cxpay", "��������" + arg + "��\n");
		return notify_fail("�����������������롣\n");
	}

	if (!objectp(ob = find_body(id)))
	{
		tell_object(me, "cx_pay_api#@#" + order + "#@#ʧ��#@#" + id + "\n");
		log_file("cxpay", "1δ�ҵ����" + id + "��\n");
		return notify_fail("�Ҳ�����ҡ�\n");
	}

	link_ob = ob->query_temp("link_ob");
	if (!ob || !link_ob)
	{
		ob = new(LOGIN_OB);
		ob->set("id", id);
		ob->set("body", USER_OB);
		obj = LOGIN_D->make_body(ob);
		destruct(ob);
		if (!obj->restore())
		{
			destruct(obj);
			tell_object(me, "cx_pay_api#@#" + order + "#@#ʧ��#@#" + id + "\n");
			log_file("cxpay", "2δ�ҵ����" + id + "��\n");
			return notify_fail("û�������ҡ�\n");
		}
		else
		{
			obj->setup();
			obj->add("yuanbao", amount);
			ob->add("cxpay/gongxian", amount / 10);
			log_file("cxpay", "���" + obj->query("name") + "(" + obj->query("id") + ")�ɹ����" + amount + "Ԫ����\n");
			tell_object(me, "cx_pay_api#@#" + order + "#@#�ɹ�#@#" + id + "\n");
			obj->save();
			destruct(obj);
			return 1;
		}
	}

	if (link_ob)
	{
		ob->add("yuanbao", amount);
		ob->add("cxpay/gongxian", amount / 10);
		ob->save();
		log_file("cxpay", "���" + ob->query("name") + "(" + ob->query("id") + ")�ɹ����" + amount + "Ԫ����\n");
		tell_object(me, "cx_pay_api#@#" + order + "#@#�ɹ�#@#" + id + "\n");
		return 1;
	}
}

object find_body(string name)
{
    object ob;
    
    if (objectp(ob = find_player(name)))
        return ob;
        
    if (file_size("/data/user/" + name[0..0] + "/" + name + ".o") != -1)
        return load_object("/clone/user/user");
    else
    	return 0;
}