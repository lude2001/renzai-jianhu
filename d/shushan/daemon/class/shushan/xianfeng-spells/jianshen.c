//Cracked by Roath
//Ansi 99.8
#define SSERVER       "/feature/sserver.c"
#include <ansi.h>
inherit SSERVER;
int cast(object me, object target)
{
   string msg;
   int damage, ap, dp, s_num, chance;
     if( !target ) target = offensive_target(me);
     if( !target
   ||   !target->is_character()
   ||   target->is_corpse()
   ||   target==me)
     return notify_fail("��Ҫ��˭ʩ�����񡹣�\n");

   if(me->query("family/family_name")!="��ɽ��")
           return notify_fail("������ɽ�Ĳ����á����񡹣�\n");
        
   if(me->query("shushan/jianshen_cast")!=1)
          return notify_fail("�㻹û��ᡸ���񡹣�\n");

   if((int)me->query_skill("xianfeng-spells", 1) < 100 )
              return notify_fail("�����ʦ�ɷ���򲻹����Ŀ��ܺ����������񡹣�\n");

   if((int)me->query("mana") < 125+(int)me->query("mana_factor") )
             return notify_fail("��ķ��������������������񡹿���Ҳû��ʲô�ã�\n");

   if((int)me->query("neili") < 100 )
             return notify_fail("��������������޷��������񡹺���������\n");

   if((int)me->query("jing") < 10 )
             return notify_fail("���������ǲ��壡\n");

   me->add("mana", -125-(int)me->query("mana_factor"));
   me->add("force", -100);
   me->receive_damage("jing", 10);

   if( random(me->query("max_mana")) < 50 ) 
   {
     write("��һ�κ����顣\n");
     return 1;
   }
        s_num = (int)(random(me->query_skill("spells")/20)) + (int)(me->query_skill("spells")/20)+ 1;
   msg = HIC "$N���������дǣ�ͻȻ����г��֡����񡹵���Ӱ����ǧ������齣��$n��ȥ��\n" NOR;

   ap = me->query_skill("spells");
   ap =  ap * ap * ap / 100;
   dp = target->query("combat_exp")* 4 /5;
   chance = (int)(random(ap + dp) * 100 / dp);
   if( chance > 66 ) 
   {
        damage = s_num * 30 ;
        damage +=(int)me->query("mana_factor")-random((int)target->query("mana_factor"));
        msg += HIC "���$n����"+chinese_number(s_num)+"����\n" NOR;
        target->receive_wound("qi", damage, me);
        me->improve_skill("xianfeng-spells", s_num, 1);
     }
     else if ( chance > 33 ) 
     {
        damage = s_num * 15 ;        
        msg += HIC "���$n��"+chinese_number(s_num)+"�����ˣ�\n" NOR;
        target->receive_wound("qi", damage, target);
        me->improve_skill("xianfeng-spells", s_num, 1);
     } 
   else
     msg += "���Ǳ�$nȫ�㿪�ˡ�\n";

   message_vision(msg, me, target);
   if( damage > 0 ) COMBAT_D->report_status(target);
   else if( damage < 0 ) COMBAT_D->report_status(me);

   if( !target->is_fighting(me) ) 
   {
     if( living(target) ) 
     {
        if( userp(target) ) target->fight_ob(me);
        else target->kill_ob(me);
     }
     me->kill_ob(target);
   }

   me->start_busy(2+random(2));
   return 10+random(5);
}
