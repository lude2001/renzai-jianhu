#include <login.h>

object find_body(string name);

int main(object me, string arg)
{
	object ob, link_ob, obj;
	string id;
	int amount;
	string order;

	log_file("cxpay", ctime(time()) + "  使用者" + me->query("name") + "(" + me->query("id") + ")  参数" + arg + "。\n");
	seteuid(ROOT_UID);
	if (me != this_player(1)) return 0;

	if (wiz_level(me) < 4 )
		return notify_fail("只有 admin 才能这样做。\n");
	// if(me->query("id")!="paycx")
	// 	return notify_fail("只有 admin 才能这样做。\n");

	if (!arg || sscanf(arg, "%s %d %s", id, amount, order) != 3)
	{
		log_file("cxpay", "参数错误" + arg + "。\n");
		return notify_fail("参数错误，请重新输入。\n");
	}

	if (!objectp(ob = find_body(id)))
	{
		tell_object(me, "cx_pay_api#@#" + order + "#@#失败#@#" + id + "\n");
		log_file("cxpay", "1未找到玩家" + id + "。\n");
		return notify_fail("找不到玩家。\n");
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
			tell_object(me, "cx_pay_api#@#" + order + "#@#失败#@#" + id + "\n");
			log_file("cxpay", "2未找到玩家" + id + "。\n");
			return notify_fail("没有这个玩家。\n");
		}
		else
		{
			obj->setup();
			obj->add("yuanbao", amount);
			ob->add("cxpay/gongxian", amount / 10);
			log_file("cxpay", "玩家" + obj->query("name") + "(" + obj->query("id") + ")成功获得" + amount + "元宝。\n");
			tell_object(me, "cx_pay_api#@#" + order + "#@#成功#@#" + id + "\n");
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
		log_file("cxpay", "玩家" + ob->query("name") + "(" + ob->query("id") + ")成功获得" + amount + "元宝。\n");
		tell_object(me, "cx_pay_api#@#" + order + "#@#成功#@#" + id + "\n");
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