#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    string npcName,userId,objAdd;
    int number;
    object mob,mobj,ob,obj,player,dan;

    // if(me->query("id")!="xxxx"){
    //     write("��ûȨ��\n");
    //     return 1;
    //}
    if (!arg){
        write("ʲô��\n");
        return 1;
    }else if( sscanf(arg,"%s %s %s %d",npcName,userId,objAdd,number)==4 ){
        //�ҵ���� �����߲�����
        player = find_player(userId);
        if (player)
		{
            dan = new(objAdd);
            dan->set_amount(number);
            dan->move(player);
            tell_object(player,"���շ���" + npcName + "����������"+ number +"��"+ dan->query("name") +"��\n");
            return 1;
        }else{

            mob = new(LOGIN_OB);
            mob->set("id",userId);
            mob->set("body", USER_OB);
            player = LOGIN_D->make_body(mob);
            destruct(mob);
            if(player->restore()){
                write("apiStatus"+userId+","+objAdd+","+number+"\n");
            }
            destruct(player);
             return 1;
        }
         return 1;
    }else if( sscanf(arg,"%s %d",objAdd,number)==2 ){
        
        dan = new(objAdd);
        dan->set_amount(number);
        dan->move(me);
        tell_object(me,"�������ڼ���"+ number +"��"+ dan->query("name") +"��\n");
        return 1;
    }
}