#include <ansi.h>

inherit F_CLEAN_UP;
#define GEM  "/clone/gem/"
int main(object me, string arg)
{
object suipian;
//��Ƭ�����������10
 if (objectp(suipian = present("gem suipian", me))&&to_int(suipian->query_autoload())>=10)
 {
   string obname,*all_gem;
   object gemob;
   all_gem=list_dirs(GEM);   
   
   if (me->query("balance")<5000000)
   return notify_fail("����Ǯׯ����500���ƽ�\n");
   
   me->add("balance",-5000000);
   if (random(10)==1)
    {
    suipian->add_amount(-10);
    gemob = new(GEM+all_gem[random(sizeof(all_gem))]);
    gemob->move(me);
    tell_object(me,"ֻ��һ�����죬��ʯ��Ƭ�������ں���������ϲ�������"+gemob->query("name")+"����������Ŷ��\n");
    }
    else 
    tell_object(me,"һ�������ȥ��ֻ����ʯ��Ƭ���ںϹ��̾����ų⣬�����˻�����\n");
    
   }
   else 	return notify_fail("�����ϵı�ʯ��Ƭ������������\n");
   return 1;
}