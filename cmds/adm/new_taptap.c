#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
  object ob;

  if (!arg)
    return notify_fail(INPUTTXT(HIY + ZJSIZE(22) + "�����˭�������" NOR, "taptap $txt# ") + "\n");
  if (!SECURITY_D->valid_grant(me, "(admin)"))
  {
    write("��û��Ȩ�޷������\n");
    return 1;
  }

  if (!objectp(ob = find_player(arg)))
    return notify_fail("���뷢���������û�������Ұ���\n");

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
    tell_object(ob, HIR "���յ��˺�������Ŷ������ʮ���鿨Ƭ���ĸ���ת�𵤣�ף����Ϸ��졣\n" NOR);
    tell_object(me, HIR "���" + ob->name() + "�ɹ������˽�����\n" NOR);
    return 1;
  }

  return notify_fail("���ǲ��Ƿ��ˣ��������Ѿ�����˰���\n");
}