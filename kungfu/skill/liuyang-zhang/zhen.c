// This program is a part of NITAN MudLIB
// zhen.c һ������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "һ������"; }
string query_name() { return "һ��"ZJBR"����"; }
int perform(object me, object target)
{
        int ap, dp, damage;
        string msg, pmsg;

        if (! target)
                target = offensive_target(me);

        if (! target || ! target->is_character()
        ||  ! me->is_fighting(target))
                return notify_fail("��һ�����졹ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( me->query_temp("weapon") )
                return notify_fail("�������ֲ���ʹ�á�һ�����졹֮����\n");

        if (me->query_skill("liuyang-zhang", 1) < 200)
                return notify_fail("�����ɽ�����Ʋ�����죬�޷�ʹ�á�һ�����졹֮����\n");

        if (me->query_skill("strike", 1) < 180)
                return notify_fail("��Ļ����Ʒ�������죬�޷�ʹ�á�һ�����졹֮����\n");

        if (me->query_skill("force", 1) < 220)
                return notify_fail("��Ļ����ڹ���Ϊ���㣬�޷�ʹ�á�һ�����졹֮����\n");
        
        if (me->query("family/family_name") != "���չ�" && me->query("family/family_name") != "��ң��")
                return notify_fail("��ķ���ң�ɻ������չ����ӣ��޷�ʹ�á�һ�����졹֮����\n");
                        
        if (me->query_skill("bahuang-gong", 1) < 240 && me->query("family/family_name") == "���չ�")
                return notify_fail("��İ˻�����Ω�Ҷ�����Ϊ���㣬�޷�ʹ�á�һ�����졹֮����\n");
                
        if (me->query_skill("beiming-shengong") < 240 && me->query("family/family_name") == "��ң��")
                    return notify_fail("��İ˻�����Ω�Ҷ�����Ϊ���㣬�޷�ʹ�á�һ�����졹֮����\n");
                    
        if (me->query_str() < 38)
                return notify_fail("��ĺ����������㣬�޷�ʹ�á�һ�����졹֮����\n");

        if (me->query_str() < 38)
                return notify_fail("��ĺ�����ǲ��㣬�޷�ʹ�á�һ�����졹֮����\n");

        if( me->query("neili")<2000 )
                return notify_fail("�������������㣬����ʹ�á�һ�����졹��\n");

        if( me->query("max_neili")<4000 )
                return notify_fail("������������Ϊ���㣬����ʹ�á�һ�����졹��\n");

        if( me->query("jiali")<50 )
                return notify_fail("�������ôС����ô��ʩչ��һ�����졹�أ�\n");


        msg = WHT" \nֻ��$N" WHT "��Ȼ��Ե�����������֮ɫ��˿˿����������䣬ת˲���ѽ�$P�����ư���������\n" +
             "���ô�ʱ��$n" WHT "�Ѿ������֪�������㣬$N" WHT "���С�" HIY "һ������" WHT "����Ȼ������ǰ��������\n" +
             "������$pֻ�����ܵĿ����·��Ѿ����ᣬ��һ��֮���ѽ���������ǰ�����������ʵ����\n"+
             "�԰��ѡ�˲��Ŀ�������ֱ��һ����մ󶴣�ʹ�����ܵ��˾�����һ�����ͣ�\n\n"NOR;

        ap = me->query_skill("strike") + me->query_con()*10;
        dp = target->query_skill("force") + target->query_con()*10;

        if (ap / 2 + random(ap) > dp)
        {
                damage = me->query_skill("strike");
                damage+= me->query("jiali");
                me->add("neili", -500);

                pmsg = HIR "$n" HIR "�ۼ�$N" HIR "һ���������ƾ���飬�������ȣ�Ȼ��������������֮�У����޿ɱܣ�ֻ��\n" +
                       "��΢Ų���Ų�Ҳ������֮���������$N" HIR "һ��ӡ����ǰ���Ǹ�һ��ʹ����裬ȴ���߹Ǳ�\n" +
                       "��һ��֮����ϣ���Ѫ��ӿ��Ȼʧ�أ�һ����Ѫ�����ӿڱ������˳�����\n\n" NOR;
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 65, pmsg);

                me->start_busy(3);
        } else
        {
                msg += HIG "����$n" HIG "�����쳣��һ�۵���$N" HIG "���е�����֮���������е����ģ���伫Ϊ����������\n"+
                       "���ֳ�ָ��������$N" HIG "���������ϣ�������ָ����$P���ĵ�" HIR "�ٸ�"
                       HIG "��" HIR "�͹�" HIG "��Ѩ�����$N" HIG "Ѩ����\n" +
                      "�⣬�������޴���й������ʴ���������$P�����ֽ���ڴ����࣬����������ˣ�\n\n" NOR;

                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}