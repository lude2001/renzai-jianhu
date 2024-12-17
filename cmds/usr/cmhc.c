#include <ansi.h>

inherit F_CLEAN_UP;
int main(object me, string arg)
{
     object dan,dan2;

     // chongmai_hc/下品冲脉丹
     // chongmai_hc/中品冲脉丹
     // chongmai_hc/上品冲脉丹
     if (arg)
     {
          mapping path = ([
               "中品冲脉丹":"/clone/vip/dan_chongmai2",
               "上品冲脉丹":"/clone/vip/dan_chongmai3",
          ]);
          int number;
          string dan_id;

          if (sscanf(arg, "%s %d", arg,number) != 2)
          {
          	write(INPUTTXT("你想合成个"+arg+"？"ZJBR"请确认你的背包空间足够。","cmhc " + arg + " $txt#")+"\n");
               return 1;
          }
          if (arg == "中品冲脉丹")
          dan_id = "chongmai dan";
          else if (arg == "上品冲脉丹")
          dan_id = "chongmai dan2";
          else
          return notify_fail("暂时没有这种丹药合成。\n");

          if (!objectp(dan = present(dan_id, me)) || !dan->query("needle/level") || dan->query_amount() < 3 * number)
          {
               return notify_fail("你没有对应的材料不够,需要数量为"+ number * 3 +"的材料。\n");
          }

          dan2 = new_bind(path[arg]);
          dan2->set_amount(number);
          dan->add_amount(-3 * number);

          dan2->move(me);

          write("合成成功，获得"+ number +"枚" + dan2->query("name") + "。\n");
     }
     else if (!arg)
     {
          string msg;

          msg = ZJOBLONG"你要执行什么操作？\n"ZJOBACTS2;
          msg += "合成中品冲脉丹:cmhc 中品冲脉丹"ZJSEP;
          msg += "合成上品冲脉丹:cmhc 上品冲脉丹\n";
          write(msg);
     }

     return 1;
}