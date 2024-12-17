inherit F_CLEAN_UP;
mixed obtain_player(string playerId);
//接受的字段 账号 属性 uuid
int main(object me, string arg)
{
    //先开始接受字段
    string playerId,attribute,uuid;
    string result;

    if (sscanf(arg,"%s %s %s",playerId,attribute,uuid) == 3)
    {
        mixed playerOb;

        int state = 0;//这个状态码记录的是在获取数据之时该玩家是否在线，如果该玩家不在线，那么给其记录为1

        if (!objectp(playerOb = find_player(playerId)))
        {
            state = 1;
            playerOb = obtain_player(playerId);

            if (!objectp(playerOb))//如果找不到这个玩家返回特定的字符串
            {
                result = "javaUserQuery@" + playerId + "@" + attribute + "@null";
                write(result + "\n");
                return playerOb;
            }

            if (!environment(playerOb))
            playerOb->move(environment(me));
            
        }

        result = "javaUserQuery@" + playerId + "@" + uuid + "@" + playerOb->query(attribute);
        write(result + "\n");

        
        if (state==1) {
        destruct(playerOb);
        }

    }

    return 1;
}

//需要使用到一个核心的函数，这个函数可用加载处于任何状态下的user对象，包括昏迷，死亡，不在线以及在线的多种情况
//如果该user对象不在线，需要通过load虚拟化的方式将该玩家加载出来

mixed obtain_player(string playerId)
{
    object playerOb;

    //默认使用find_player的方式进行对user的查找，如果该情况下无法找到指定的user，则使用虚拟化
    if (!objectp(playerOb = find_player(playerId)))
    {
        object ob;

        ob = new(LOGIN_OB);
        ob->set("id",playerId);
        ob->set("body", USER_OB);
        playerOb = LOGIN_D->make_body(ob);
        

        //如果一个login无法生成一个user,报错未知的情况下，返回-2告诉调用它的使用者
        if (!objectp(playerOb))
        {
            return -2;
        }
        
        

        //如果一个user并没有存档，说明其尚未注册，返回-1告诉调用它的使用者。
        if (!playerOb->restore())
        {
            return -1;
        }

        playerOb->setup();
    }

    return playerOb;
}