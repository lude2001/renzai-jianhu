#pragma optimize
#pragma save_binary

inherit F_SAVE;
inherit F_DBASE;

public string query_save_file() { return DATA_DIR "yijingd"; }

//存储意境的数据，存储的key直接以玩家id存储
mapping data = ([]);

void create()
{
    seteuid(getuid());
    restore();
}

void remove()
{
    save();
}

public void mud_shutdown()
{
    save();
}

public int set_data(object me)
{
    if (!me->query("yijing") || !mapp(me->query("yijing")))
        return 0;
    
    data[me->query("id")]= me->query("yijing");
    save();

    return 1;
}

//读取数据
public mixed query_data(string playerId)
{

    if (!playerId)
    {
        if (data == ([]))
            return 0;

        return data;
    }

    if (undefinedp(data[playerId]))
        return 0;

    return data[playerId];
}

//检查一个意境的名字是否重复
int check_yj_name_is_repetition(string name,string type)
{
    string *keyList;
    mapping playerYjData;

    if (data == ([]))
    return 0;

    keyList = keys(data);

    foreach (string playerId in keyList)
    {
        playerYjData = data[playerId];

        //undefin就是用来寻找是否有这个意境的一个设定
        if (!undefinedp(playerYjData[name]) && playerYjData[name]["type"] == type)
        return 1;

    }

    return 0;
}