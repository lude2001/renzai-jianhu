
#include <ansi.h>

inherit F_CLEAN_UP;

//string json_encode(mixed data);

int main(object me, string arg)
{
    object ob;
    
    foreach (ob in children(USER_OB))
    {
            if (ob->query("max_neili") > ob->query_current_neili_limit() && ob->query("max_neili") > 1000 && (ob->query("max_neili") - ob->query_current_neili_limit()) > 999 && ob->query("max_neili") > 1000 && ob->query_skill("beiming-shengong"))
            {
                write(sprintf("%s的内力极限为:%d,当前最大内力为:%d,超出点数为:%d\n",ob->query("name"),ob->query_current_neili_limit(),ob->query("max_neili"),ob->query("max_neili") - ob->query_current_neili_limit()));
            }
        
    }
    // mapping a;
    
    // a = copy(me->query_entire_dbase());
    
    // write(json_encode(a) + "\n");
    
    // log_file("beibaocs",json_encode(a) + "\n");
    return 1;
}

// string json_encode(mixed data)
// {
// 	string str,*strDataList = ({  });
// 	mixed value,key;

// 	if (arrayp(data))
// 	{
// 		str = "[";

// 		foreach (value in data)
// 		{
// 			strDataList += ({ json_encode(value)});
// 		}

// 		str += implode(strDataList,",");
// 		str += "]";
		
// 		return str;
// 	}

// 	if (mapp(data))
// 	{

// 		str = "{";

// 		foreach (key in keys(data))
// 		{
// 			value = data[key]; 

// 			strDataList += ({ sprintf("%s:%s",json_encode(key),json_encode(value))});
// 		}

// 		str += implode(strDataList,",");
		
// 		str += "}";
// 		return str;
// 	}

// 	if (intp(data) || floatp(data))
// 	{
// 		return "" + data;
// 	}

// 	if (stringp(data))
// 	{
// 		return "\"" + data + "\"";
// 	}

// 	return "{}";
// }