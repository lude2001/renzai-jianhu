#include <ansi.h>

inherit F_CLEAN_UP;
int main(object me, string arg)
{
     object dan,dan2;

     // chongmai_hc/��Ʒ������
     // chongmai_hc/��Ʒ������
     // chongmai_hc/��Ʒ������
     if (arg)
     {
          mapping path = ([
               "��Ʒ������":"/clone/vip/dan_chongmai2",
               "��Ʒ������":"/clone/vip/dan_chongmai3",
          ]);
          int number;
          string dan_id;

          if (sscanf(arg, "%s %d", arg,number) != 2)
          {
          	write(INPUTTXT("����ϳɸ�"+arg+"��"ZJBR"��ȷ����ı����ռ��㹻��","cmhc " + arg + " $txt#")+"\n");
               return 1;
          }
          if (arg == "��Ʒ������")
          dan_id = "chongmai dan";
          else if (arg == "��Ʒ������")
          dan_id = "chongmai dan2";
          else
          return notify_fail("��ʱû�����ֵ�ҩ�ϳɡ�\n");

          if (!objectp(dan = present(dan_id, me)) || !dan->query("needle/level") || dan->query_amount() < 3 * number)
          {
               return notify_fail("��û�ж�Ӧ�Ĳ��ϲ���,��Ҫ����Ϊ"+ number * 3 +"�Ĳ��ϡ�\n");
          }

          dan2 = new_bind(path[arg]);
          dan2->set_amount(number);
          dan->add_amount(-3 * number);

          dan2->move(me);

          write("�ϳɳɹ������"+ number +"ö" + dan2->query("name") + "��\n");
     }
     else if (!arg)
     {
          string msg;

          msg = ZJOBLONG"��Ҫִ��ʲô������\n"ZJOBACTS2;
          msg += "�ϳ���Ʒ������:cmhc ��Ʒ������"ZJSEP;
          msg += "�ϳ���Ʒ������:cmhc ��Ʒ������\n";
          write(msg);
     }

     return 1;
}