//#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
  object ob;
  object obj;

  string objPath,playerId;
  int objNumber,state;


  if (!arg)
    return notify_fail("必须指定参数");

  if (!SECURITY_D->valid_grant(me, "(admin)"))
  {
    
    write("你没有权限发礼包。\n");
    return 1;

  }

  if (sscanf(arg, "%s %s %d %d", playerId,objPath,objNumber,state) == 4)
  {

    if (!objectp(ob = find_player(playerId)))
    return notify_fail("找不到指定的玩家。\n");

    //处理逻辑，先判定是否是绑定物品，然后根据物品是否可叠加进行下次的操作

    if (state == 1)
    obj = new_bind(objPath);
    else
    obj = new(objPath);

    if (!objectp(obj))
    return notify_fail(objPath + "路径下没有该物品");


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

    tell_object(ob,sprintf("你获得了系统特别奖励的%d-%s。\n",objNumber,obj->query("name")));
    tell_object(me,sprintf("你给%s发放了系统特别奖励的%d-%s。\n",ob->query("name"),objNumber,obj->query("name")));
    return 1;

  }

  


  return 1;

}