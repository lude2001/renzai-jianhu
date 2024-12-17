// made by lks

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "欢喜游戏"; }

int exert(object me, object target)
{
        object weapon,*team;
        int damage;
        string msg;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("「旋涡劲」只能对战斗中的对手使用。\n");

        if( (int)me->query_skill("force", 1) < 80 )
                return notify_fail("你的内功底子太薄，不能使用。\n");
                                
        if( (int)me->query_skill("hx-jing", 1) < 80 )
                return notify_fail("你的欢喜转轮经不够熟练。\n");
                        
        if( (int)me->query("neili", 1) < 300 )
                return notify_fail("你现在内力太弱，不能使用「旋涡劲」。\n");
        
        if (time() < me->query("hx-jing/time"))
                return notify_fail("还是再缓缓吧，游戏不能太过频繁。\n");

        if (sizeof(team = me->query_team()) == 2)
        {
                object dx;
                //string msg;

                team -= ({ me });
                dx = team[0];

                if (environment(me) != environment(dx))
                return notify_fail("这个游戏可不能隔空玩，必须一起转轮子才能增长功力。\n");

                if (me->query("gender") == dx->query("gender"))
                return notify_fail("这个不太好吧？找不着通道啊，还是换个人吧。");

                msg = HIR"嘿...嘿嘿...你只感觉快乐的飞起来了，一时间...芜湖....你意识到一个人玩游戏就是和两个人玩游戏不是一个概念的,男女搭配干活不累，你们两一起转轮子功力大增。"NOR"。\n";

                if (me->query("hx-jing/point") < (me->query("guizhen/number") * me->query("guizhen/number") * 1000))
                {
                        string *jcList = ({ "qi","jing","neili" });
                        mapping desc = ([
                                "qi":"气血",
                                "neili":"内力极限",
                                "jing" : "精神",
                        ]);
                        string q;

                        q = jcList[random(sizeof(jcList))];

                        me->add("hx-jing/" + q,10);

                        tell_object(me,"你作为游戏的主力操作手获得了:10点" + desc[q] + "。\n");
                }
                else
                {
                        me->add("combat_exp",me->query("hx-jing/point") / 2);
                        me->add("potential",me->query("hx-jing/point") / 4);

                        tell_object(me,sprintf("你获得了%d点经验,%d点潜能。\n",me->query("hx-jing/point") / 2,me->query("hx-jing/point") /4));
                }

                me->add("hx-jing/point",1);
                me->set("hx-jing/time",time() + 1800);

                tell_object(me,msg);
                tell_object(dx,msg);
        }
        else if (sizeof(team = me->query_team()) != 2)
        {
                return notify_fail("你这样子可顶不住啊！\n");
        }
        else
        {
                return notify_fail("这可是双人游戏啊，一个人可不行。\n");
        }

        return 1;
}

