//zhangwuji.c

inherit F_MASTER;
inherit F_UNIQUE;
inherit F_QUESTER;
inherit NPC;

#include <ansi.h>
#include "mingjiao.h"

void greeting(object ob);

void create()
{
    seteuid(getuid());
    set_name("张无忌", ({ "zhang wuji", "zhang", "wuji" }));
    set("long", @LONG
明教教主张无忌，统领天下十万教众，豪气干云，叱咤千秋，
「九阳神功」、「乾坤大挪移」独步天下，是江湖中不世出的
少年英雄。
LONG );
    set("title",HIG "明教" HIM " 教主" NOR);
    set("gender", "男性");
    set("age", 20);
	set("no_get", 1);
    set("shen_type",1);
    set("attitude", "friendly");
    set("class", "fighter");

    set("str", 33);
    set("int", 35);
    set("con", 38);
    set("dex", 33);

    set("qi", 5800);
    set("max_qi", 5800);
    set("jing", 2700);
    set("max_jing", 2700);
    set("neili", 8000);
    set("max_neili", 8000);
    set("jiali", 120);

    set("combat_exp", 2900000);
    set("score", 455000);
    
    set_skill("force", 340);
    set_skill("unarmed", 200);
    set_skill("dodge", 200);
    set_skill("parry", 300);
    set_skill("sword", 260);
    set_skill("jiuyang-shengong", 340);
    set_skill("qiankun-danuoyi", 350);
    set_skill("qishang-quan", 250);
    set_skill("taiji-quan", 250);
    set_skill("taiji-jian", 260);
    set_skill("shenghuo-ling", 220);

    map_skill("force", "jiuyang-shengong");
    map_skill("dodge", "qiankun-danuoyi");
    map_skill("unarmed", "taiji-quan");
    map_skill("sword", "shenghuo-ling");
    map_skill("parry", "qiankun-danuoyi");

    create_family("明教", 34, "教主");

    set("chat_chance", 1);
    set("chat_msg", ({
	"张无忌愤然说道“大丈夫当以国为家, 捐躯沙场, 抗元大业未成, 同辈仍需努力!”\n",
	"张无忌叹道“人生失一知己, 生亦何欢, 死亦何忧, 敏儿, 你在哪里?”\n",
	"张无忌道“我教兄弟听了: 生于乱世, 当克己为公, 行侠仗义, 荡寇驱魔!”\n",
    }));

    set("inquiry",([
	  "明教" :     "你打听我们明教做什么？。\n",
	  "金毛狮王" : "那是我义父谢大侠的职司。\n",
	  "谢逊" :     "他就是我义父的大号。\n",
	  "张翠山" :   "你想找我父亲有事麽? \n",
	  "殷素素" :   "我妈是明尊座下紫微堂主。\n",
	  "张三丰" :   "我太师父近来可好? \n",
	  "赵敏" :     "人生失一知己, 生亦何欢, 死亦何忧, 敏儿, 你在哪里?\n",
	  "小昭" :     "小昭我可一直念着她的好处。\n",
	  "周芷若" :   "找她就去峨嵋山, 别来烦我。\n",
    ]));
    setup();
    add_money("silver", 70);
}

void init()
{
	object ob;

	::init();

	if (interactive(this_player()) && this_player()->query_temp("fighting"))
	{
		COMBAT_D->do_attack(this_object(), this_player(), query_temp("weapon"));
		this_player()->add_temp("beat_count", 1);
	}       
	if (interactive(ob=this_player()) && ! is_fighting())
	{
		remove_call_out("greeting");
		call_out("greeting",1,ob);
	}
}

void greeting(object ob)
{
	if (! ob || environment(ob)!=environment()) return;
	if ((int)ob->query("shen") < -50000)
	{
		command("wield yitian jian");
		command("hit" + (string)ob->query("id"));
		command("unwield yitian jian");
	} else
	if ((int)ob->query("shen") < -5000)
	{
		command("say 魔从心起，于武学不利，其道必诛，劝君放下屠刀，"
			"立地成佛。");
	} else
	if((int)ob->query("shen") < -100)
	{
		command("say 这位朋友，人行江湖，言行当正，切务走进邪魔歪道。");
	} else
	if((int)ob->query("shen") >= 0)
	{
		command("say 光明正道任人走，劝君多加保重。");
	} else
	if((int)ob->query("shen") > 50000)
	{
		command("say 大侠在上，受无忌一礼，大侠它日必为武林翘楚。");
	}
	return;
}

int accept_fight(object ob)
{
	if ((ob->query("combat_exp") < 30000) && (ob->query("shen") > 0))
	{
		message_vision("武林中人最忌争强斗狠，你不是我的对手，"
			       "回去吧。\n",ob);
		return 0;
	}
	message_vision("张无忌一拱手说道：这位" + RANK_D->query_respect(ob) +
		       "，在下领教了。\n", ob);
	return 1;
}

int recognize_apprentice(object ob, string skill)
{
    return -1;
}