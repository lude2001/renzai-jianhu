#include <ansi.h>



inherit F_CLEAN_UP;


string query_name() { return "ʨ�Ӻ�"; }

int exert(object me, object target)

{

        object *ob;

        int i, skill, damage;

	if (environment(me)->query("no_fight"))
		return notify_fail("�����ﲻ�ܹ������ˡ�\n");


     if ( me->query("family/family_name") != "�ƻ���")

                return notify_fail("�㲻���ƻ������Ӳ���ʹ��ʨ�Ӻ�.\n");


 if (me->query("age",1)<=16)
                return notify_fail("СС���Ҳ������ô��µ��书?\n");

  if( ((int)me->query("neili") < 600 ) || ( (int)me->query_skill("mingyu-shengong") < 20) )

                return notify_fail("���������\"��\"�ĺ���һ��, ��������˼�ֻ����\n");





        skill = me->query_skill("force");


        me->start_busy(5);
        me->add("neili", -150);

        me->receive_damage("qi", 10);



        me->start_busy(1);

        message_vision(

                HIY "$N�������һ�����������ŷ�������һ�����춯�صľ޺�\n" NOR, me);



        ob = all_inventory(environment(me));

        for(i=0; i<sizeof(ob); i++) {

                if( !living(ob[i]) || ob[i]==me ) continue;

                if( skill/2 + random(skill/2) < (int)ob[i]->query("con") * 2 ) continue;

                

                damage = skill * 3 - ((int)ob[i]->query("max_neili") / 10);

                if( damage > 0 ) {

                        ob[i]->receive_damage("jing", damage * 2, me);

                        if( (int)ob[i]->query("neili") < skill * 2 )

                                ob[i]->receive_wound("jing", damage, me);

                        tell_object(ob[i], "�������ǰһ�������ð������ʹ������Ҫ�ѿ�һ����\n");

                }

                if( !ob[i]->is_killing(me) ) ob[i]->kill_ob(me);

                if( !me->is_killing(ob[i]) ) me->fight_ob(ob[i]);
if (userp(ob[i]))
{
ob[i]->set_temp("zjb_roar",""+me->query("id")+"");
}


        }



        return 1;

}

