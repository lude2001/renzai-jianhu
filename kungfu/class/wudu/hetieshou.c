#include <ansi.h>
#include "wudu.h"

#define SHEYING     "/clone/lonely/sheying"
#define JINWUGOU    "/clone/lonely/jinwugou"
#define ZHUSUO      "/clone/lonely/zhusuo"
#define DUJING      "/clone/lonely/book/dujing3"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT;

mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_skill4();
mixed ask_skill5();
mixed ask_skill6();
mixed ask_gou();
mixed ask_suo();
mixed ask_she();
mixed ask_jing();
int ask_me();
string ask_ling();
void create()
{
        object ob, ob2;
        set_name("何铁手", ({ "he tieshou", "he", "tieshou" }));
        set("nickname", HIR "五毒仙子" NOR);
        set("long",@LONG
你对面的是一个一身粉红纱裙，笑靥如花的少女。
她长得肌肤雪白，眉目如画，赤着一双白嫩的秀
足，手脚上都戴着闪闪的金镯。谁能想到她就是
五毒教的教主何铁手，武林人士提起她无不胆颤
心惊。
LONG);
        set("title", "五毒教教主");
        set("gender", "女性");
        set("age", 25);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("per", 30);

        set("max_qi", 5000);
        set("max_jing", 4000);
        set("neili", 5500);
        set("max_neili", 5500);
        set("jiali", 200);
        set("combat_exp", 2500000);
        set("score", 10000);

        set_skill("force", 300);
        set_skill("wudu-shengong", 300);
        set_skill("xiuluo-yinshagong", 300);
        set_skill("dodge", 300);
        set_skill("wudu-yanluobu", 300);
        set_skill("strike", 300);
           set_skill("tianchan-zhang", 300);
        set_skill("hand", 300);
        set_skill("qianzhu-wandushou", 300);
        set_skill("claw", 300);
        set_skill("wusheng-zhao", 300);
        set_skill("parry", 300);
        set_skill("sword", 300);
        set_skill("jinwu-goufa", 300);
        set_skill("whip", 300);
        set_skill("ruanhong-zhusuo", 300);
        set_skill("xiewei-bian", 300);
        set_skill("throwing", 300);
        set_skill("hansha-sheying", 300);
        set_skill("literate", 300);
        set_skill("poison", 300);
        set_skill("wudu-qishu", 300 );
        set_skill("martial-cognize", 300);
        set_skill("wudu-jing", 300);

        map_skill("force", "xiuluo-yinshagong");
        map_skill("dodge", "wudu-yanluobu");
        map_skill("strike", "tianchan-zhang");
        map_skill("hand", "qianzhu-wandushou");
        map_skill("claw", "wusheng-zhao");
        map_skill("throwing", "hansha-sheying");
        map_skill("parry", "jinwu-goufa");
        map_skill("sword", "jinwu-goufa");
        map_skill("whip", "ruanhong-zhusuo");
        map_skill("poison", "wudu-qishu");

        prepare_skill("claw", "wusheng-zhao");
        prepare_skill("strike", "tianchan-zhang");

        create_family("五毒教", 11, "教主");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.duo" :),
                (: perform_action, "whip.teng" :),
                (: perform_action, "whip.pan" :),
                (: perform_action, "whip.bohu" :),
                (: perform_action, "whip.suo" :),
                (: perform_action, "claw.lian" :),
                (: perform_action, "strike.chan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }) );

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        setup();

        set("inquiry", ([
                "金蜈钩"   : (: ask_gou :),
                "软红蛛索" : (: ask_suo :),
                "含沙射影" : (: ask_she :),
                "毒经"     : "你是要毒经上篇、中篇还是下篇？",
                "毒经上篇" : "毒经上篇你去问炼毒室的道人要吧。",
                "毒经中篇" : "毒经中篇在齐长老手中，你去问他要吧。",
                "毒经下篇" : (: ask_jing :),
                "绝技"     : "你要问什么绝技？",
                //"万毒窟"    : (: ask_me :),
                "五毒珠"    : (: ask_ling :),
                "腾蛇诀"   : "这一招你去找齐长老学吧。",
                "盘鹰诀"   : (: ask_skill1 :),
                "搏虎诀"   : (: ask_skill2 :),
                "锁龙诀"   : (: ask_skill3 :),
                "金钩夺魄" : (: ask_skill4 :),
                "无影针"   : (: ask_skill5 :),
                "万毒穿心" : (: ask_skill6 :),
        ]));

        if (clonep())
        {
                ob = find_object(ZHUSUO);
                ob2 = find_object(SHEYING);

                if (! ob) ob = load_object(ZHUSUO);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        ob->wield();
                } else
                {
                        ob = find_object(JINWUGOU);
                        if (! ob) ob = load_object(JINWUGOU);
                        if (! environment(ob))
                        {
                                ob->move(this_object());
                                ob->wield();
                        } else
                        {
                                ob = new("/clone/weapon/changbian");
                                ob->move(this_object());
                                ob->wield();
                        }
                }
                if (! ob2) ob2 = load_object(SHEYING);
                if (! environment(ob2))
                {
                        ob2->move(this_object());
                        ob2->wear();
                }
        }
        //carry_object("/clone/cloth/moon-dress")->wear();
}

void init()
{
        add_action("do_show", "show");
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( ob->query("shen")>-1000 )
        {
                command("say 我越看你越象六扇门派来的卧底。");
                return;
        }

        if( ob->query("shen")>-50000 )
        {
                command("say 像你这样心慈手软的人是干不成大事的！");
                return;
        }

        if( ob->query("combat_exp")<350000 )
        {
                command("say 你现在经验尚浅，不能领会高深的武功，还是先去增长点经验吧。");
                return;
        }

        if ((int)ob->query_skill("wudu-shengong", 1) < 120)
        {
                command("say 你的五毒心法还学的不够啊。");
                return;
        }

        if ((int)ob->query_skill("wudu-qishu", 1) < 120)
        {
                command("say 你把本门的施毒绝学钻研透了再来找我吧。");
                return;
        }

        command("say 好吧，既然如此本姑娘就收下你这个徒弟。");
        command("recruit "+ob->query("id"));
        ob->set("title", MAG"五毒教长老"NOR);
        return;
}

mixed ask_gou()
{
        object me;
        object ob;
        object owner;

        me = this_player();
        if (me->is_good())
        {
                if( me->query("family/family_name") == "五毒教" )
                        message_vision(CYN "$N" CYN "冷哼一声，对$n" CYN "道："
                                       "“你身为我五毒教弟子，反而学起假仁假义"
                                       "来了，居然还有脸问我要金钩？”\n" NOR,
                                       this_object(), me);
                else
                        message_vision(CYN "$N" CYN "冷笑一声，对$n" CYN "说道"
                                       "：“你是什么人？居然敢在我面前打听这个"
                                       "！”\n" NOR,
                                       this_object(), me);
                return 1;
        }

        if( me->query("family/family_name") != "五毒教" )
                return "你不是我们五毒教的，打听它干什么？";

        if( me->query("family/master_id") != query("id") )
                return "只有我的弟子才能用金蜈钩，你拿去用只会替我丢脸。";

        if( me->query("shen")>-35000 )
                return "你这样心慈手软，这金钩你不用也罢。";

        if (me->query_skill("jinwu-goufa", 1) < 120)
                return "你连金蜈钩法都没学好，就算用金钩也是白搭。";

        ob = find_object(JINWUGOU);
        if (! ob) ob = load_object(JINWUGOU);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "嗯？金蜈钩现在不是你拿着在用吗？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "你来晚了一步，我已经把金蜈钩借给你同门师兄弟用去了。";

                if( owner->query("family/family_name") == "五毒教" )
                        return "金蜈钩现在暂时是你同门师兄弟"+owner->query("name")+
                               "在用，你要用就去找他吧。";
                else
                        return "本门的金蜈钩现在落在"+owner->query("name")+
                               "手中，你去把它抢回来吧！";
        }

        ob->move(this_object());

        ob = new("clone/weapon/changbian");
        ob->move(this_object());
        ob->wield();

        message_vision(CYN "$N" CYN "微微一笑，道：“这柄金蜈钩你就"
                       "拿去，让那些正派人士尝尝咱五毒教的厉害！”\n" NOR,
                       this_object(), me);
          command("give jinwu gou to "+me->query("id"));
        return 1;
}

mixed ask_suo()
{
        object me;
        object ob;
        object owner;

        me = this_player();
        if (me->is_good())
        {
                if( me->query("family/family_name") == "五毒教" )
                        message_vision(CYN "$N" CYN "冷哼一声，对$n" CYN "道："
                                       "“你身为我五毒教弟子，反而学起假仁假义"
                                       "来了，居然还有脸问我要软红蛛索？”\n" NOR,
                                       this_object(), me);
                else
                        message_vision(CYN "$N" CYN "冷笑一声，对$n" CYN "说道"
                                       "：“你是什么人？居然敢在我面前打听这个"
                                       "！”\n" NOR,
                                       this_object(), me);
                return 1;
        }

        if( me->query("family/family_name") != "五毒教" )
                return "你不是我们五毒教的，打听它干什么？";

        if( me->query("family/master_id") != query("id") )
                return "只有我的弟子才能用软红蛛索，你拿去用只会替我丢脸。";

        if( me->query("shen")>-35000 )
                return "你这样心慈手软，这蛛索你不用也罢。";

        if (me->query_skill("ruanhong-zhusuo", 1) < 150)
                return "你连软红蛛索都没学好，就算用蛛索也是白搭。";

        ob = find_object(ZHUSUO);
        if (! ob) ob = load_object(ZHUSUO);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "嗯？软红蛛索现在不是你拿着在用吗？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "你来晚了一步，我已经把软红蛛索借给你同门师兄弟用去了。";

                if( owner->query("family/family_name") == "五毒教" )
                        return "软红蛛索现在暂时是你同门师兄弟"+owner->query("name" )+
                               "在用，你要用就去找他吧。";
                else
                        return "本门的软红蛛索现在落在"+owner->query("name")+
                               "手中，你去把它抢回来吧！";
        }

        ob->move(this_object());

        ob = new("/clone/weapon/changbian");
        ob->move(this_object());
        ob->wield();

        message_vision(CYN "$N" CYN "微微一笑，道：“这根软红蛛索你就"
                       "拿去，让那些正派人士尝尝咱五毒教的厉害！”\n" NOR,
                       this_object(), me);
          command("give ruanhong zhusuo to "+me->query("id"));
        return 1;
}

mixed ask_she()
{
        object me;
        object ob;
        object owner;

        me = this_player();
        if (me->is_good())
        {
                if( me->query("family/family_name") == "五毒教" )
                        message_vision(CYN "$N" CYN "冷哼一声，对$n" CYN "道："
                                       "“你身为我五毒教弟子，反而学起假仁假义"
                                       "来了，居然还有脸问我要含沙射影？”\n" NOR,
                                       this_object(), me);
                else
                        message_vision(CYN "$N" CYN "冷笑一声，对$n" CYN "说道"
                                       "：“你是什么人？居然敢在我面前打听这个"
                                       "！”\n" NOR,
                                       this_object(), me);
                return 1;
        }

        if( me->query("family/family_name") != "五毒教" )
                return "你不是我们五毒教的，打听它干什么？";

        if( me->query("shen")>-10000 )
                return "你这样心慈手软，这含沙射影你不用也罢。";

        if (me->query_skill("hansha-sheying", 1) < 50)
                return "你这门暗器手法太差，用不好还会伤及自身。";

        //ob = new("/d/wudu/npc/obj/hanshasheying");
        ob = find_object(SHEYING);
        if (! ob) ob = load_object(SHEYING);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "嗯？含沙射影现在不是你拿着在用吗？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "含沙射影现在不在我这里。";

                if( owner->query("family/family_name") == "五毒教" )
                        return "含沙射影现在暂时是你同门"+owner->query("name")+
                               "在用，你要用就去找他吧。";
                else
                        return "我的含沙射影现在落在"+owner->query("name")+
                               "手中，你去把它抢回来吧！";
        }
        ob->move(this_object());

        message_vision(CYN "$N" CYN "微微一笑，道：含沙射影你拿去吧，叫他们尝尝我"
                       "们五毒教的厉害！\n" NOR, this_object(), me);
          command("give hansha sheying to "+me->query("id"));
        command("whisper"+me->query("id")+"这含沙射影里的毒针用完了，可以拿"
                "(show)回来让我给你装。");
        return 1;
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( me->query("can_perform/ruanhong-zhusuo/panying") )
                return "你不是已经会了吗？";

        if( me->query("family/family_name") != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本教素无瓜葛，何出此言？";

        if (me->query_skill("ruanhong-zhusuo", 1) < 1)
                return "你连软红蛛索都没学，何谈此言？";

        if( me->query("shen")>-30000 )
                return "心慈手软的人永远成不了大器，这招你不学也罢！";

        if (me->query_skill("ruanhong-zhusuo", 1) < 130)
                return "你的软红蛛索还练得不到家，自己下去练练再来吧！";

        message_sort(HIY "\n$n" HIY "点了点头，从腰间取下长索，手腕轻轻一抖，顿"
                     "时鞭影重重，完全笼罩$N" HIY "的四周，直看得$N" HIY "目瞪口"
                     "呆。\n\n" NOR, me, this_object());

        command("nod");
        command("say 这一招便是软红蛛索绝技盘鹰诀，你可看明白了？");
        tell_object(me, HIC "你学会了「盘鹰诀」。\n" NOR);

        if (me->can_improve_skill("whip"))
                me->improve_skill("whip", 150000);
        if (me->can_improve_skill("ruanhong-zhusuo"))
                me->improve_skill("ruanhong-zhusuo", 150000);
        me->set("can_perform/ruanhong-zhusuo/panying", 1);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( me->query("can_perform/ruanhong-zhusuo/bohu") )
                return "你不是已经会了吗？";

        if( me->query("family/family_name") != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本教素无瓜葛，何出此言？";

        if (me->query_skill("ruanhong-zhusuo", 1) < 1)
                return "你连软红蛛索都没学，何谈此言？";

        if( me->query("shen")>-50000 )
                return "心慈手软的人永远成不了大器，这招你不学也罢！";

        if (me->query_skill("ruanhong-zhusuo", 1) < 160)
                return "你的软红蛛索还练得不到家，自己下去练练再来吧！";

        message_sort(HIY "\n$n" HIY "点了点头，道：“本姑娘今天便传你这招，你可"
                     "看好了！”$n" HIY "说罢，从腰间取下长索，一声娇喝，手中长"
                     "索狂舞，漫天鞭影顿时幻作无数小圈，铺天盖地罩向$N" HIY "。"
                     "\n\n" NOR, me, this_object());

        command("nod");
        command("say 这一招便是软红蛛索绝技搏虎诀，你可看明白了？");
        tell_object(me, HIC "你学会了「搏虎诀」。\n" NOR);

        if (me->can_improve_skill("whip"))
                me->improve_skill("whip", 150000);
        if (me->can_improve_skill("ruanhong-zhusuo"))
                me->improve_skill("ruanhong-zhusuo", 150000);
        me->set("can_perform/ruanhong-zhusuo/bohu", 1);

        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( me->query("can_perform/ruanhong-zhusuo/suolong") )
                return "你不是已经会了吗？";

        if( me->query("family/family_name") != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本教素无瓜葛，何出此言？";

        if (me->query_skill("ruanhong-zhusuo", 1) < 1)
                return "你连软红蛛索都没学，何谈此言？";

        if( me->query("shen")>-80000 )
                return "心慈手软的人永远成不了大器，这招你不学也罢！";

        if (me->query_skill("ruanhong-zhusuo", 1) < 160)
                return "你的软红蛛索还练得不到家，自己下去练练再来吧！";

        message_sort(HIY "\n$n" HIY "对$N" HIY "赞许地点了点头，道：“既然你如"
                     "此有心，本姑娘就再传你这招！”说完$n" HIY "招了招手，$N"
                     HIY "连忙凑上前去，只见$n" HIY "轻声在$N" HIY "说了些话，"
                     "接着手中长索一抖，登时幻出漫天鞭影，宛如蛟龙通天，无数鞭"
                     "影一齐向四面八方席卷而去！\n\n" NOR, me, this_object());

        command("sweat");
        command("nod");
        command("say 这一招便是软红蛛索绝技锁龙诀，你下去需勤加练习！");
        tell_object(me, HIC "你学会了「锁龙诀」。\n" NOR);

        if (me->can_improve_skill("whip"))
                me->improve_skill("whip", 150000);
        if (me->can_improve_skill("ruanhong-zhusuo"))
                me->improve_skill("ruanhong-zhusuo", 150000);
        me->set("can_perform/ruanhong-zhusuo/suolong", 1);

        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();
        if( me->query("can_perform/jinwu-goufa/duo") )
                return "这招我已经教过你了，还是自己下去多多练习吧！";

        if( me->query("family/family_name") != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本教素无瓜葛，何出此言？";

        if (me->query_skill("jinwu-goufa", 1) < 1)
                return "你连金蜈钩法都没学，何谈此言？";

        if( me->query("shen")>-80000 )
                return "哼！你这样心慈手软能干成什么事？这招你不学也罢！";

        if (me->query_skill("jinwu-goufa", 1) < 160)
                return "你的金蜈钩法还练得不到家，自己下去练练再来吧！";

        message_sort(HIY "\n$n" HIY "微微点了点头，在$N" HIY "耳边轻声说了些话"
                     "，一边说还一边比划着些什么。如此这般，过了良久……\n\n"
                     NOR, me, this_object());

        command("say 刚才那些便是这招的口诀和练功的要领，你可要记牢了。");
        command("nod");
        command("say 这招金钩夺魄比较难练，你自己下来后要多加研究。");
        tell_object(me, HIC "你学会了「金钩夺魄」。\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 150000);
        if (me->can_improve_skill("jinwu-goufa"))
                me->improve_skill("jinwu-goufa", 150000);
        me->set("can_perform/jinwu-goufa/duo", 1);

        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();
        if( me->query("can_perform/hansha-sheying/zhen") )
                return "这招我不是已经教过你了吗？";

        if( me->query("family/family_name") != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本教素无瓜葛，何出此言？";

        if (me->query_skill("hansha-sheying", 1) < 1)
                return "你连含沙射影都没学，何谈此言？";

        if( me->query("shen")>-80000 )
                return "哼！你这样心慈手软能干成什么事？这招你不学也罢！";

        if (me->query_skill("hansha-sheying", 1) < 120)
                return "你的含沙射影还练得不到家，自己下去练练再来吧！";

        message_sort(HIY "\n$n" HIY "微微一笑，伸手将$N" HIY "招到面前，在$N"
                     HIY "耳边轻声嘀咕了些话。$N" HIY "听了半天，突然间不由会"
                     "心的一笑，看来大有所悟。\n\n" NOR, me, this_object());

        command("nod");
        command("say 这招并不复杂，但是用来偷袭和暗算敌人却很有效，你多练练吧！");
        tell_object(me, HIC "你学会了「无影针」。\n" NOR);
        if (me->can_improve_skill("throwing"))
                me->improve_skill("throwing", 150000);
        if (me->can_improve_skill("hansha-sheying"))
                me->improve_skill("hansha-sheying", 150000);
        me->set("can_perform/hansha-sheying/zhen", 1);

        return 1;
}

mixed ask_skill6()
{
        object me;

        me = this_player();
        if( me->query("can_perform/qianzhu-wandushou/chuan") )
                return "这招我不是已经教过你了吗？";

        if( me->query("family/family_name") != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本教素无瓜葛，何出此言？";

//        if( !me->query("reborn/times") )
//                return "你还未历经劫难，本门绝技可不能随便传给你。";


        if( me->query("shen")>-100000 )
                return "哼！你这样心慈手软能干成什么事？这招你不学也罢！";

        if (me->query_skill("qianzhu-wandushou", 1) < 300)
                return "你的千蛛万毒手还练得不到家，自己下去练练再来吧！";

        message_sort(HIY "\n$n" HIY "微微一笑，伸手将$N" HIY "招到面前，在$N"
                     HIY "耳边轻声嘀咕了些话。$N" HIY "听了半天，突然间不由会"
                     "心的一笑，看来大有所悟。\n\n" NOR, me, this_object());

        command("nod");
        command("say 这招可是本门秘传，极为博大精深，你下去后可得多练习练习！");
        tell_object(me, HIC "你学会了「万毒穿心」。\n" NOR);
        if (me->can_improve_skill("qianzhu-wandushou"))
                me->improve_skill("qianzhu-wandushou", 150000);
        if (me->can_improve_skill("hand"))
                me->improve_skill("qianzhu-wandushou", 150000);
        me->set("can_perform/qianzhu-wandushou/chuan", 1);

        return 1;
}

int accept_object(object me, object ob)
{
        int r;
        if (r = ::accept_object(me, ob))
                return r;

        if (base_name(ob) != JINWUGOU
        && base_name(ob) != ZHUSUO)
        {
                command("say 你给我这种东西干什么？");
                return 0;
        }

        if( me->query("family/master_id") != query("id") )
                command("say 多谢这位" + RANK_D->query_respect(me) + "将本门宝物交回。");
        else
                command("say 很好，很好！");
        destruct(ob);
        return 1;
}

mixed ask_jing()
{
        object me;
        object ob;
        object owner;

        me = this_player();

        if( me->query("family/family_name") != "五毒教" )
                return "你是谁？我认识你么？";

        if( me->query("shen")>-30000 )
                return "你这人心肠那么好，又去学毒做甚？";

        if( me->query("combat_exp")<150000 )
                return "你现在经验太浅，不用忙着去阅读毒经。";

        if (me->query_skill("wudu-qishu", 1) > 149)
                return "你对本门的毒技已经通晓得比较透彻了，还是自己多研究吧。";

        ob = find_object(DUJING);
        if (! ob) ob = load_object(DUJING);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "不就是你拿着么？怎么反倒问我来了？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "…嗯…毒经下篇现在不在我手里。";

                if( owner->query("family/family_name") == "五毒教" )
                        return "毒经现在是你同门"+owner->query("name")+
                               "在看，去找他吧。";
                else
                        return "我教的毒经现落在"+owner->query("name")+
                               "的手中，你去把它夺回来吧！";
        }
        ob->move(this_object());
        message_vision(CYN "$N" CYN "点头道：你拿去看吧，若有不解之处"
                       "可以来问我。\n" NOR, this_object(), me);
          command("give du jing3 to "+me->query("id"));
        return 1;
}

int do_show(string arg)
{
        object ob;
        object me;
        int n;

        if (! arg)
                return notify_fail("你要亮出什么东西？\n");

        me = this_player();

        if (! objectp(ob = me->present(arg)))
                return notify_fail("你身上没有这种东西。\n");

        if( me->query("family/family_name") != "五毒教" )
                return notify_fail(CYN "何铁手冷冷望了你一眼，没理你。\n" NOR);

        if( ob->query("id") != "hanshasheying" )
                return notify_fail(CYN "何铁手皱了皱眉头，说道：你给我看这个"
                                   "干嘛？\n" NOR);

        if( ob->query("equipped") )
                return notify_fail(CYN "何铁手说道：你不把含沙射影脱下来，叫"
                                   "我怎么帮你装针？\n" NOR);

        if( ob->query("zhen")>5 )
                return notify_fail(CYN "何铁手说道：含沙射影里的毒针用了一半"
                                   "还不到，你瞎急什么！\n" NOR);

        message_vision(HIC "\n何铁手微微一笑，从$N" HIC "手中接过含沙射影，轻"
                       "轻拨弄几下，又还给了$N" HIC "。\n\n" NOR, me);

        command("say 行了，含沙射影里的毒针已经补满了。");
        ob->set("zhen", 10);
        return 1;
}

string ask_ling()
{
        mapping fam;
        object *allob,env,ob,me=this_player();
        string *sname;
        int i, count, here = 0;

        //if (query("ling_count") < 1)
        //        return "你来晚了，五毒令别的教众正在用呢。\n";
        if( !(fam=me->query("family")) || fam["family_name"] != "五毒教" )
                return RANK_D->query_respect(me) + "与本派素无来往，不知此话从何谈起？";

        if( me->query("wudu_zhu") == 1 )
                return "不是已经给你了么？";

        env = environment(me);
        allob = all_inventory(env);
        count = 0;
        for(i=0; i<sizeof(allob); i++)
                if(allob[i] != me && allob[i]!=this_object() )
                {
                        if( allob[i]->query("host_id") == me->query("id") )
                        {
                                here = 1;
                        }
                        count++;
                }

        if (present("wudu zhu", this_player()))
        {
         message_vision(HIG"你想死吗？。。。\n"NOR,me);
                return 0;
        }

        if( me->query("wudu_zhu") == 0 && count >= 1 )
                return "现在人多眼杂，你回头再来吧！";


        add("wudu_zhu",-1);
        ob = new("clone/fam/wudu-zhu");
        ob->move(me);
        message_vision("$N获得一颗五毒珠。\n",me);
        remove_call_out ("wudu_zhu");
        call_out ("wudu_zhu", 600); // 10 分钟

        return "好吧，凭这五毒珠，你可以吸收珠子的毒气。";

}

void unconcious()
{
        die();
}