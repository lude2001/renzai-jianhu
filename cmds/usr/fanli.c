#include <ansi.h>

inherit F_CLEAN_UP;
int fanli(object ob)
{
//ZJOBACTS2+ZJMENUF(4,4,8,30);
string msg=ZJOBLONG"江湖通宝奖励系统："ZJBR;
if (ob->query("combat_exp") > ob->query("chonzhi/combat_exp")&&ob->query("cxpay/gongxian")>=30)
{
int yuanbao=0;
     if (ob->query("combat_exp")>=2000000&&ob->query("chonzhi/combat_exp")<2000000)  yuanbao += 1000;
     if (ob->query("combat_exp")>=1000000&&ob->query("chonzhi/combat_exp")<1000000)  yuanbao += 500;
     if (ob->query("combat_exp")>=700000&&ob->query("chonzhi/combat_exp")<700000)  yuanbao += 500;
     if (ob->query("combat_exp")>=400000&&ob->query("chonzhi/combat_exp")<400000)  yuanbao += 500;
     if (ob->query("combat_exp")>=200000&&ob->query("chonzhi/combat_exp")<200000)  yuanbao += 500;
     ob->set("chonzhi/combat_exp",ob->query("combat_exp"));//记录
     if (yuanbao>0)
     {
     ob->add("yuan_bao",yuanbao);
      msg+="恭喜您通宝奖励获得"+yuanbao+"个通宝，祝您游戏愉快！\n";
     }
     else msg+="通宝奖励如下："ZJBR"20万，40万，70万，100万经验档次奖励500通宝，200万经验档次奖励1000通宝，共计3000通宝，您目前还没有足够的经验哦\n";               
}
else msg+="您目前没有任何通宝返利哦\n";

tell_object(ob,msg);
return 1;
}
int main(object me, string arg)
{
 return fanli(me);
   
}