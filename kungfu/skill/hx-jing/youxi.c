// made by lks

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "��ϲ��Ϸ"; }

int exert(object me, object target)
{
        object weapon,*team;
        int damage;
        string msg;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("�����о���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( (int)me->query_skill("force", 1) < 80 )
                return notify_fail("����ڹ�����̫��������ʹ�á�\n");
                                
        if( (int)me->query_skill("hx-jing", 1) < 80 )
                return notify_fail("��Ļ�ϲת�־�����������\n");
                        
        if( (int)me->query("neili", 1) < 300 )
                return notify_fail("����������̫��������ʹ�á����о�����\n");
        
        if (time() < me->query("hx-jing/time"))
                return notify_fail("�����ٻ����ɣ���Ϸ����̫��Ƶ����\n");

        if (sizeof(team = me->query_team()) == 2)
        {
                object dx;
                //string msg;

                team -= ({ me });
                dx = team[0];

                if (environment(me) != environment(dx))
                return notify_fail("�����Ϸ�ɲ��ܸ����棬����һ��ת���Ӳ�������������\n");

                if (me->query("gender") == dx->query("gender"))
                return notify_fail("�����̫�ðɣ��Ҳ���ͨ���������ǻ����˰ɡ�");

                msg = HIR"��...�ٺ�...��ֻ�о����ֵķ������ˣ�һʱ��...�ߺ�....����ʶ��һ��������Ϸ���Ǻ�����������Ϸ����һ�������,��Ů����ɻ�ۣ�������һ��ת���ӹ���������"NOR"��\n";

                if (me->query("hx-jing/point") < (me->query("guizhen/number") * me->query("guizhen/number") * 1000))
                {
                        string *jcList = ({ "qi","jing","neili" });
                        mapping desc = ([
                                "qi":"��Ѫ",
                                "neili":"��������",
                                "jing" : "����",
                        ]);
                        string q;

                        q = jcList[random(sizeof(jcList))];

                        me->add("hx-jing/" + q,10);

                        tell_object(me,"����Ϊ��Ϸ�����������ֻ����:10��" + desc[q] + "��\n");
                }
                else
                {
                        me->add("combat_exp",me->query("hx-jing/point") / 2);
                        me->add("potential",me->query("hx-jing/point") / 4);

                        tell_object(me,sprintf("������%d�㾭��,%d��Ǳ�ܡ�\n",me->query("hx-jing/point") / 2,me->query("hx-jing/point") /4));
                }

                me->add("hx-jing/point",1);
                me->set("hx-jing/time",time() + 1800);

                tell_object(me,msg);
                tell_object(dx,msg);
        }
        else if (sizeof(team = me->query_team()) != 2)
        {
                return notify_fail("�������ӿɶ���ס����\n");
        }
        else
        {
                return notify_fail("�����˫����Ϸ����һ���˿ɲ��С�\n");
        }

        return 1;
}

