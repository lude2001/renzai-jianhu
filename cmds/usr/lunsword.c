// time.c					  
#include <ansi.h>

int main(object me, string arg)
{   
    mapping lunjian = FAMILY_D->query_lunjian();
    string *title = keys(lunjian);
    object ob;
    string msg,str;  
    if (!arg)
    {
     msg = ZJOBLONG"这里是天下五绝的雕像，你可以查看：\n";
    msg += ZJOBACTS2+ZJMENUF(3,3,10,30);
     foreach (str in title)  
     {
      if (objectp(ob =find_player(lunjian[str])))
      msg += sprintf("%s—%s:lunsword %s"ZJSEP,str,ob->query("name"),lunjian[str]);
      else 
      msg += sprintf("%s—不知所踪"ZJSEP,str);
     }
     write(msg+"刷新:look\n");
     
     }
     else
     if (objectp(ob = find_player(arg)))
     {
      msg = ZJOBLONG"这里是天下五绝的雕像，你可以查看："ZJBR;
      msg += "姓名："+ob->query("name")+ZJBR;
      msg += "门派："+ob->query("family/family_name")+ZJBR;
      msg += "帮会："+ob->query("banghui/name")+ZJBR;
      msg += "年龄："+ob->query("age")+ZJBR;
      msg += "性别："+ob->query("gender");
      msg += "\n"ZJOBACTS2+ZJMENUF(3,3,10,30);
      msg += "膜拜:look "+getuid(ob)+ZJSEP;
      msg += "送鲜花:sendlun hua "+getuid(ob)+ZJSEP;
      msg += "丢臭鸡蛋:sendlun dan "+getuid(ob);
      write(msg+"\n");
     }
	return 1;
		
	
}

int help(object me)
{
     write(@HELP
指令格式: lunsword，这个指令告诉你当前的天下五绝的信息。

HELP
    );
    return 1;
}
