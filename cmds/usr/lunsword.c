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
     msg = ZJOBLONG"��������������ĵ�������Բ鿴��\n";
    msg += ZJOBACTS2+ZJMENUF(3,3,10,30);
     foreach (str in title)  
     {
      if (objectp(ob =find_player(lunjian[str])))
      msg += sprintf("%s��%s:lunsword %s"ZJSEP,str,ob->query("name"),lunjian[str]);
      else 
      msg += sprintf("%s����֪����"ZJSEP,str);
     }
     write(msg+"ˢ��:look\n");
     
     }
     else
     if (objectp(ob = find_player(arg)))
     {
      msg = ZJOBLONG"��������������ĵ�������Բ鿴��"ZJBR;
      msg += "������"+ob->query("name")+ZJBR;
      msg += "���ɣ�"+ob->query("family/family_name")+ZJBR;
      msg += "��᣺"+ob->query("banghui/name")+ZJBR;
      msg += "���䣺"+ob->query("age")+ZJBR;
      msg += "�Ա�"+ob->query("gender");
      msg += "\n"ZJOBACTS2+ZJMENUF(3,3,10,30);
      msg += "Ĥ��:look "+getuid(ob)+ZJSEP;
      msg += "���ʻ�:sendlun hua "+getuid(ob)+ZJSEP;
      msg += "��������:sendlun dan "+getuid(ob);
      write(msg+"\n");
     }
	return 1;
		
	
}

int help(object me)
{
     write(@HELP
ָ���ʽ: lunsword�����ָ������㵱ǰ�������������Ϣ��

HELP
    );
    return 1;
}
