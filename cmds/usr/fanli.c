#include <ansi.h>

inherit F_CLEAN_UP;
int fanli(object ob)
{
//ZJOBACTS2+ZJMENUF(4,4,8,30);
string msg=ZJOBLONG"����ͨ������ϵͳ��"ZJBR;
if (ob->query("combat_exp") > ob->query("chonzhi/combat_exp")&&ob->query("cxpay/gongxian")>=30)
{
int yuanbao=0;
     if (ob->query("combat_exp")>=2000000&&ob->query("chonzhi/combat_exp")<2000000)  yuanbao += 1000;
     if (ob->query("combat_exp")>=1000000&&ob->query("chonzhi/combat_exp")<1000000)  yuanbao += 500;
     if (ob->query("combat_exp")>=700000&&ob->query("chonzhi/combat_exp")<700000)  yuanbao += 500;
     if (ob->query("combat_exp")>=400000&&ob->query("chonzhi/combat_exp")<400000)  yuanbao += 500;
     if (ob->query("combat_exp")>=200000&&ob->query("chonzhi/combat_exp")<200000)  yuanbao += 500;
     ob->set("chonzhi/combat_exp",ob->query("combat_exp"));//��¼
     if (yuanbao>0)
     {
     ob->add("yuan_bao",yuanbao);
      msg+="��ϲ��ͨ���������"+yuanbao+"��ͨ����ף����Ϸ��죡\n";
     }
     else msg+="ͨ���������£�"ZJBR"20��40��70��100���鵵�ν���500ͨ����200���鵵�ν���1000ͨ��������3000ͨ������Ŀǰ��û���㹻�ľ���Ŷ\n";               
}
else msg+="��Ŀǰû���κ�ͨ������Ŷ\n";

tell_object(ob,msg);
return 1;
}
int main(object me, string arg)
{
 return fanli(me);
   
}