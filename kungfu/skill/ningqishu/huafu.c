#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
 
string query_name() { return "����"ZJBR"�ɷ�"; }
string *pfm_type() { return ({ "fufa", }); }

int perform(object me)
{
    object bi;
    object zhi;
    object mo;
    object fu;
    int a;
    int fu_damage;
	if (!environment(me)->query("is_jingxiu"))
	    return notify_fail("��Ҫ���䵱�ؾ����ȫ�澲�����в���ʹ�������ɷ���\n");
	    
	if (me->is_busy())
	    return notify_fail("��������æ���޷�ʹ�������ɷ���\n");
	    
	if (me->is_fighting())
	    return notify_fail("���������ڴ�ܣ��޷�ʹ�������ɷ���\n");
	
	if (!living(me))
	    return notify_fail("�����ڵ�״̬�޷�ʹ�������ɷ���\n");
	    
	if (me->query_skill("ningqishu", 1) < 300)
	    return notify_fail("�������������⻹�������޷�ʹ�������ɷ���\n");
	    
	if (me->query("max_jing") < 2500)
	    return notify_fail("�������ڵľ����޷�������������\n");
	
	if (me->query("max_neili") < 5000)
	    return notify_fail("�������ڵ������޷�������������\n");
	    
	if (me->query("neili") < me->query("max_neili"))
	    return notify_fail("��������������޷���ת��������\n");
	    
	if (me->query("jing") < me->query("max_jing") / 3)
	    return notify_fail("��ľ���������֮һ���޷���ת��������\n");
	    
	if (me->query("jingli") < me->query("max_jingli") / 3)
	    return notify_fail("��ľ�����������֮һ���޷���ת��������\n");
	    
	if (!objectp(bi = present("langhao bi", me)))
	    return notify_fail("������û���Ǻ��ʡ�\n");
	
	if (!objectp(mo = present("zhu sha", me)))
	    return notify_fail("������û����ɰ��\n");
	    
	if (!objectp(zhi = present("huang zhi", me)))
	    return notify_fail("������û�з�ֽ��\n");
	
	me->add("neili", -me->query("max_neili"));
	me->add("jing", -me->query("max_jing") / 3);
	me->add("jingli", -me->query("max_jingli") / 3);
	
	a = (me->query_skill("fufa", 1) + me->query_skill("taoism", 1)) / 2 + me->query_skill("force", 1) / 3;
	
	zhi->add_amount(-1);
	
	fu = new("/clone/fufa/ningqi");
	if (!objectp(fu))
	    return notify_fail("��������ϵ����Ա����\n");
	
	fu_damage = a + random(a);
	fu->set("fu/damage", fu_damage);
	fu->set("long", fu->query("long") + "\n��������" + fu_damage + "\n");
	fu->move(me);
	
	tell_object(me, "����ת���������ӱʻ���һ����������\n");
	message("vision", me->query("name") + "��ת���������ӱʻ���һ����������\n", environment(me), ({me})); 
	me->start_busy(30);
	
	return 1;
}
