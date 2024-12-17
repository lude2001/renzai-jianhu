#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    string npcName,userId,objAdd;
    int number;
    object mob,mobj,ob,obj,player,dan;

    // if(me->query("id")!="xxxx"){
    //     write("你没权限\n");
    //     return 1;
    //}
    if (!arg){
        write("什么！\n");
        return 1;
    }else if( sscanf(arg,"%s %s %s %d",npcName,userId,objAdd,number)==4 ){
        //找到玩家 看在线不在线
        player = find_player(userId);
        if (player)
		{
            dan = new(objAdd);
            dan->set_amount(number);
            dan->move(player);
            tell_object(player,"您收服的" + npcName + "给您送来了"+ number +"个"+ dan->query("name") +"！\n");
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
        tell_object(me,"您离线期间获得"+ number +"个"+ dan->query("name") +"！\n");
        return 1;
    }
}