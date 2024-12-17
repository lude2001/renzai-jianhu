//#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
  object ob;
  object obj;

  string objPath,playerId;
  int objNumber,state;


  if (!arg)
    return notify_fail("����ָ������");

  if (!SECURITY_D->valid_grant(me, "(admin)"))
  {
    
    write("��û��Ȩ�޷������\n");
    return 1;

  }

  if (sscanf(arg, "%s %s %d %d", playerId,objPath,objNumber,state) == 4)
  {

    if (!objectp(ob = find_player(playerId)))
    return notify_fail("�Ҳ���ָ������ҡ�\n");

    //�����߼������ж��Ƿ��ǰ���Ʒ��Ȼ�������Ʒ�Ƿ�ɵ��ӽ����´εĲ���

    if (state == 1)
    obj = new_bind(objPath);
    else
    obj = new(objPath);

    if (!objectp(obj))
    return notify_fail(objPath + "·����û�и���Ʒ");


    if (obj->query_amount())
    {
      obj->set_amount(objNumber);
      obj->move(ob);
      
    }
    else
    {

      for (int i = 0; i < objNumber; i++) {
        object singleObj;

        singleObj = new(objPath);
        singleObj->move(ob);
      }

    }

    tell_object(ob,sprintf("������ϵͳ�ر�����%d-%s��\n",objNumber,obj->query("name")));
    tell_object(me,sprintf("���%s������ϵͳ�ر�����%d-%s��\n",ob->query("name"),objNumber,obj->query("name")));
    return 1;

  }

  


  return 1;

}