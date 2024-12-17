#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
  object ob;

  if (!arg)
    return notify_fail(INPUTTXT(HIY + ZJSIZE(22) + "你想给谁发礼包？" NOR, "taptap $txt# ") + "\n");
  if (!SECURITY_D->valid_grant(me, "(admin)"))
  {
    write("你没有权限发礼包。\n");
    return 1;
  }

  if (!objectp(ob = find_player(arg)))
    return notify_fail("你想发礼包，可是没有这个玩家哎。\n");

  if (!ob->query("taptap2"))
  {
    object obj;
    obj = new ("/clone/maintask/obj/jiuzhuan");
    obj->set_amount(4);
    obj->move(ob);
    obj = new ("/clone/baiyi/tencard");
    obj->set_amount(2);
    obj->move(ob);
    ob->set("taptap3", 1);
    tell_object(ob, HIR "你收到了好评奖励哦，二个十连抽卡片，四个九转金丹，祝您游戏愉快。\n" NOR);
    tell_object(me, HIR "你给" + ob->name() + "成功发放了奖励。\n" NOR);
    return 1;
  }

  return notify_fail("你是不是疯了，这个玩家已经领过了啊。\n");
}