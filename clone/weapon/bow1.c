// Updated by Lonely

#include <ansi.h>
#include <weapon.h>
inherit HAMMER;

mapping exits_name=([
	"east":            "东方",
	"south":           "南方",
	"west":            "西方",
	"north":           "北方",
	"eastup":          "东上方",
	"southup":         "南上方",
	"westup":          "西上方",
	"northup":         "北上方",
	"eastdown":        "东下方",
	"southdown":       "南下方",
	"westdown":        "西下方",
	"northdown":       "北下方",
	"northeast":       "东北方",
	"northwest":       "西北方",
	"southeast":       "东南方",
	"southwest":       "西南方",
	"up":              "上方",
	"down":            "下方",
	"enter":           "里边",
	"out":             "外边",
]);

int do_shoot(string id, object me, object bow, object room, string what, int m);
string exits_reverse(string dir);

string exits_reverse(string dir)
{
 	if (dir == "east") return "west";
 	if (dir == "west") return "east";
 	if (dir == "south") return "north";
 	if (dir == "north") return "south";
 	if (dir == "eastup") return "westdown";
 	if (dir == "westup") return "eastdown";
 	if (dir == "southup") return "northdown";
 	if (dir== "northup") return "southdown";
 	if (dir == "eastdown") return "westup";
 	if (dir == "westdown") return "eastup";
 	if (dir == "southdown") return "northup";
 	if (dir == "northdown") return "southup";
 	if (dir == "northeast") return "southwest";
 	if (dir == "northwest") return "southeast";
 	if (dir == "southwest") return "northeast";
 	if (dir == "southeast") return "northwest";
 	if (dir == "up") return "down";
 	if (dir == "down") return "up";
 	if (dir == "enter") return "out";
 	if (dir == "out") return "enter";

 	return "";
}

void create()
{
        set_name(YEL"铜胎长弓"NOR, ({ "tong bow", "bow", "gong" }) );
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一把铜制的长弓。\n");
                set("unit", "把");
                set("value", 10000);
                set("consistence", 42);
                set("dam", 400);
                set("no_put", 1);
                set("is_bow", 1);
                set("wield_msg", HIY"$N将$n"HIY"从肩上取下，握在手中。\n"NOR);
                set("unwield_msg", HIY"$N将$n"HIY"横跨，背在肩上。\n"NOR);
                set("material", "iron");
        }
        init_hammer(10);
}

void init()
{
        add_action("do_she", "she");
}

int do_she(string arg)
{
   	object me = this_player(), bow, ob, room;
   	int i, n, m;
   	string what;
   	mapping exits;

   	room = environment(me);
   	// 为了后面的循环
   	bow = me->query_temp("weapon");

   	if (room->query("no_fight"))
   		return notify_fail("这里不许战斗！\n");

   	if (! bow || ! bow->query("is_bow"))
   		return notify_fail("弓还在背上呢，怎么射呀！\n");

   	if (me->query_str() < bow->query("dam") / 20)
   		return notify_fail("你使尽吃奶的力气也拉不开弓来，看来力气不够！\n");

   	if (bow->query("consistence") < 0)
   	{
    		message_vision(HIW"$N手中的" + bow->query("name") + HIW"“嘣”地一声断了！\n", me);
    		bow->unequip();
    		destruct(bow);
    		return 1;
   	}

   	if (me->is_busy())
   		return notify_fail("你现在正忙着呢！\n");

   	if (me->query("qi") < 200 || me->query("jing") < 100)
   		return notify_fail("你现在精气不够充盈，硬拉功怕有危险啊！\n");

   	if (! arg || sscanf(arg, "%s %d", what, n) != 2)
   		return notify_fail("不会射箭？找人家教教你吧！\n");

    	if (n > bow->query("dam") / 200 ) n = bow->query("dam") / 200;

    	for (i = 0; i < n; i++)
     	{
     		reset_eval_cost();
      		if (room && mapp(exits = room->query("exits")) && stringp(exits[what]))
      		{
      			m = i + 1;
       			room = get_object(exits[what]);
      		}

	}

     	if (room == environment(me))
      		return notify_fail("看清楚点，朝哪里射呀你？\n");

     	if (objectp(room))
     	{
      		if (room->query("have_quest") || room->query("no_fight"))
      			return notify_fail("那里有神明佐佑，不容你胡来也！\n");

      		"/cmds/std/look.c"->look_room(me, room);

      		message_vision(HIY"$N从箭囊内抽出一支"HIW"羽箭"HIY"，搭在"
       				+ bow->query("name") + HIY"上，随后立了一个霸王上弓式，\n朝"HIR
       				+ exits_name[what] + HIY"把弓拉满.......\n"NOR, me);

      		tell_object(all_inventory(room), HIB"你觉得一股猛烈的杀机从"HIR
       				+ exits_name[exits_reverse(what)] + HIB"传来！！\n"NOR);

      		tell_object(me, HIR + exits_name[what] + HIW"的情景你一目了然，"
                                + "你把利箭渐渐瞄准了——>\n"NOR);
      		me->start_busy(2 + random(3));
      		input_to("do_shoot", me, bow, room, what, m);
     	} else return notify_fail("看清楚点，朝哪里射呀你？\n");

    	return 1;
}

int do_shoot(string id, object me, object bow, object room, string what, int m)
{
    	object ob, obj, *env;
        int damage;
        mixed exp, ratio;

    	if (! id || id == "")
    	{
     		message_vision("$N叹了口气，将箭从" + bow->query("name") + "上又取了下来。\n", me);
     		return 1;
    	}

    	if (objectp(ob = present(id, room)) && ob->is_character())
    	{
     		if (ob->query("is_quest") && ob->query("killer") != me->query("id"))
     		{
      			tell_object(me, "“砰”地一声，你被" + bow->query("name")
                                  	+ "震了一下，看来目标不好惹呀！\n");
      			return 1;
     		}

     		if (playerp(ob) && ob->query("age") < 18)
     		{
      			tell_object(me, "“砰”地一声，你被" + bow->query("name")
                                  	+ "震了一下，原来你的目标是小朋友呀！\n");
      			return 1;
     		}

      		message_vision(HIY"$N“嗖”地一箭朝"HIR + exits_name[what] + HIY"射了出去！\n", me);

      		damage = bow->query("dam") * (5 + me->query_str()) / (m * 5 + ob->query_dex());
      		if (damage < 100) damage = 100;
      		if (damage > 1500) damage = 1500;
      		damage = damage + random(damage);

                me->want_kill(ob);


                if (random(me->query_skill("arrow", 1)) > ob->query_skill("dodge", 1) / 4
//                ||  random(me->query("combat_exp")) > ob->query("combat_exp"))
                || random(me->query("combat_exp"))>ob->query("combat_exp") )
     		{
      			if (damage > 2000)
        			message_vision(HIY"“嗖”地一声，一枚"HIW"羽箭从"HIR
           					+ exits_name[exits_reverse(what)]
           					+ HIY"飞来，"HIR"“噗嗤”"HIY"一声扎在$N"HIR"额头"HIY"上！\n"NOR,
           					ob);
      			else if (damage > 1500)
        			message_vision(HIY"“嗖”地一声，一枚"HIW"羽箭从"HIR
           					+ exits_name[exits_reverse(what)]
           					+ HIY"飞来，"HIR"“噗嗤”"HIY"一声扎在$N"HIR"胸口"HIY"上！\n"NOR,
           					ob);
      			else if (damage > 1000)
        			message_vision(HIY"“嗖”地一声，一枚"HIW"羽箭从"HIR
           					+ exits_name[exits_reverse(what)]
           					+ HIY"飞来，"HIR"“噗嗤”"HIY"一声扎在$N"HIR"肩膀"HIY"上！\n"NOR,
           					ob);
      			else if (damage > 500)
        			message_vision(HIY"“嗖”地一声，一枚"HIW"羽箭从"HIR
           					+ exits_name[exits_reverse(what)]
           					+ HIY"飞来，"HIR"“噗嗤”"HIY"一声扎在$N"HIR"小腿"HIY"上！\n"NOR,
           					ob);
      			else
        			message_vision(HIY"“嗖”地一声，一枚"HIW"羽箭从"HIR
           					+ exits_name[exits_reverse(what)]
           					+ HIY"飞来，"HIR"“噗嗤”"HIY"一声扎在$N"HIR"手臂"HIY"上！\n"NOR,
           					ob);
      			damage = damage / 4 + random(damage / 2);
      			ob->receive_damage("qi", damage, me);

      			if (damage > (int)ob->query_temp("apply/armor"))
      				ob->receive_wound("qi", damage - (int)ob->query_temp("apply/armor"), me);

      			COMBAT_D->report_status(ob, random(2));
      				tell_object(me, HIR"嘿嘿，目标应声而倒，真是好箭法！\n"NOR);

//                        ratio = me->query("combat_exp") / 100;
//                        ratio = ob->query("combat_exp") / ratio;
                              ratio=me->query("combat_exp")/100;
                              ratio=ob->query("combat_exp")/ratio;
      			if (ratio > 1000) ratio = 1000;
      			if (ratio < 10) ratio = 10;
      			if (! playerp(ob))
      				me->improve_skill("arrow",
      					random((damage / 2 + me->query_int() / 10) * ratio / 100), 0);

      		} else
      		if (random(3) > 0)
      		{
       			env = all_inventory(room);
       			obj = env[random(sizeof(env))];
       			if (obj != ob && obj->is_character())
       			{
       				damage = bow->query("dam") * (5 + me->query_str()) / (m * 5 + obj->query_dex());
       				if (damage < 100) damage = 100;
       				if (damage > 1500) damage = 1500;
       				damage = damage / 2 + random(damage / 2);

       				if (damage > 2000)
        				message_vision(HIY"“嗖”地一声，一枚"HIW"羽箭从"HIR
           						+ exits_name[exits_reverse(what)]
           						+ HIY"飞来，"HIR"“噗嗤”"HIY"一声扎在$N"HIR"额头"HIY"上！\n"NOR,
           						obj);
       				else if (damage > 1500)
        				message_vision(HIY"“嗖”地一声，一枚"HIW"羽箭从"HIR
           						+ exits_name[exits_reverse(what)]
           						+ HIY"飞来，"HIR"“噗嗤”"HIY"一声扎在$N"HIR"胸口"HIY"上！\n"NOR,
           						obj);
       				else if (damage > 1000)
        				message_vision(HIY"“嗖”地一声，一枚"HIW"羽箭从"HIR
           						+ exits_name[exits_reverse(what)]
           						+ HIY"飞来，"HIR"“噗嗤”"HIY"一声扎在$N"HIR"肩膀"HIY"上！\n"NOR,
           						obj);
       				else if (damage > 500)
        				message_vision(HIY"“嗖”地一声，一枚"HIW"羽箭从"HIR
           						+ exits_name[exits_reverse(what)]
           						+ HIY"飞来，"HIR"“噗嗤”"HIY"一声扎在$N"HIR"小腿"HIY"上！\n"NOR,
           						obj);
       				else
        				message_vision(HIY"“嗖”地一声，一枚"HIW"羽箭从"HIR
           						+ exits_name[exits_reverse(what)]
           						+ HIY"飞来，"HIR"“噗嗤”"HIY"一声扎在$N"HIR"手臂"HIY"上！\n"NOR,
           						obj);
        			damage = damage / 4 + random(damage / 2);
        			obj->receive_damage("qi", damage, me);
        			if (damage > (int)obj->query_temp("apply/armor"))
        				obj->receive_wound("qi", damage - (int)obj->query_temp("apply/armor"), me);
        			COMBAT_D->report_status(obj, random(2));

        			tell_object(me,HIB"糟糕，箭好象射到别人了，好好练箭法吧！\n"NOR);
       			} else
       			{
        			message_vision(HIY"一枚"HIW"羽箭从"HIR + exits_name[exits_reverse(what)]
           					+ HIY"飞来，"HIR"“嗖”"HIY"地一声从$N"HIR"耳边"NOR"飞过！\n"NOR,
           					ob);
        			tell_object(me, HIW"哎呀，箭射飞了，好好练箭法吧！\n"NOR);
       			}
      		} else
      		{
        		message_vision(HIY"一枚"HIW"羽箭从"HIR + exits_name[exits_reverse(what)]
           				+ HIY"飞来，"HIR"“嗖”"HIY"地一声从$N"HIR"耳边"NOR"飞过！\n"NOR,
           				ob);
        		tell_object(me,HIW"哎呀，箭射飞了，好好练箭法吧！\n"NOR);
      		}
    	} else
     		tell_object(me, "可惜，目标现在不在那里了，你的箭飞了耶！\n");

     	bow->add("consistence", -1);
     	me->receive_damage("jing", 50, me);
     	me->receive_damage("qi", 100, me);

     	return 1;
}

