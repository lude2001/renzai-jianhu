#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
  object ob;

  if (!arg)
    return notify_fail(INPUTTXT(HIY + ZJSIZE(22) + "�����˭�������" NOR, "weixin $txt# ") + "\n");
  if (!SECURITY_D->valid_grant(me, "(admin)"))
  {
    write("��û��Ȩ�޷������\n");
    return 1;
  }

  if (!objectp(ob = find_player(arg)))
    return notify_fail("���뷢���������û�������Ұ���\n");

  if (!ob->query("weixin/1"))
  {
    object obj;
    obj = new ("/clone/baiyi/onecard");
    obj->set_amount(5);
    obj->move(ob);
    ob->set("weixindong/1", 1);
    tell_object(ob, HIR "���յ���΢�Ż����Ŷ��5�����鿨Ƭ��ף����Ϸ��졣\n" NOR);
    tell_object(me, HIR "���" + ob->name() + "�ɹ������˽�����\n" NOR);
    return 1;
  }

  return notify_fail("���ǲ��Ƿ��ˣ��������Ѿ�����˰���\n");
}