#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
  object ob;

  if (!arg)
    return notify_fail(INPUTTXT(HIY + ZJSIZE(22) + "�����˭�������" NOR, "new_luntan $txt# ") + "\n");
  if (!SECURITY_D->valid_grant(me, "(admin)"))
  {
    write("��û��Ȩ�޷������\n");
    return 1;
  }

  if (!objectp(ob = find_player(arg)))
    return notify_fail("���뷢���������û�������Ұ���\n");

  if (!ob->query("kuaibaohuodong/1"))
  {
    object obj;
    obj = new ("/clone/baiyi/tencard");
    obj->set_amount(2);
    obj->move(ob);
    ob->set("kuaibaohuodong/1", 1);
    tell_object(ob, HIR "���յ��˿챬�����Ŷ��2��ʮ���鿨Ƭ��ף����Ϸ��졣\n" NOR);
    tell_object(me, HIR "���" + ob->name() + "�ɹ������˽�����\n" NOR);
    return 1;
  }

  return notify_fail("���ǲ��Ƿ��ˣ��������Ѿ�����˰���\n");
}