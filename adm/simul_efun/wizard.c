// wiz.c

string json_encode(mixed data)
{
	string str,*strDataList = ({  });
	mixed value,key;
    
	if (arrayp(data))
	{
		str = "[";

		foreach (value in data)
		{
			strDataList += ({ json_encode(value)});
		}

		str += implode(strDataList,",");
		str += "]";
		
		return str;
	}

	if (mapp(data))
	{

		str = "{";

		foreach (key in keys(data))
		{
			value = data[key]; 

			strDataList += ({ sprintf("%s:%s",json_encode(key),json_encode(value))});
		}

		str += implode(strDataList,",");
		
		str += "}";
		return str;
	}

	if (intp(data) || floatp(data))
	{
		return "" + data;
	}

	if (stringp(data))
	{
		return "\"" + data + "\"";
	}

	return "{}";
}

string wizhood(mixed ob)
{
	return SECURITY_D->get_status(ob);
}

int wiz_level(mixed ob)
{
	return SECURITY_D->get_wiz_level(ob);
}

//下划线
string info_button(string *buttonData)
{
	string msg = ESA + "301";
	string *singleKey;
	string *keybut = ({});

	foreach (string key in buttonData)
	{
		singleKey = explode(key,":");
		keybut += ({ sprintf("{\"cmd\":\"%s\",\"name\":\"%s\"}",singleKey[1],singleKey[0]) });
	}

	msg += "[" + implode(keybut,",") +"]";
	msg += "\n";

	return msg;

}

//从数组里随机取出来一个对象
mixed rand_array(mixed *arrayTo)
{
    return arrayTo[random(sizeof(arrayTo))];
}

//生成一个绑定物品 输入的路径不需要改变，但是开头必须要带/
object new_bind(string path)
{
    string new_path = "/common/bind_obj" + path + ".c"; 
    object obj;
    if (file_size(new_path) == -1)
    {
        string str;
        assure_file(new_path);
        str = read_file("/common/bind_obj/reference");
        str = replace_string(str,"path",path);
        write_file(new_path,str,1);
    }

    obj = new(new_path);
    return obj;
}

//区间器 判断传入的数字是否存在这个firstTarget----secondTarget这个区间里，contain代表区间是一个包含区间，否之为非包含
int section(int enterValue, int firstTarget, int secondTarget, int contain)
{
    if (contain && enterValue >= firstTarget && enterValue <= secondTarget)
    {
        return 1;
    }
    else if (!contain && enterValue > firstTarget && enterValue < secondTarget)
    {
        return 1;
    }

    return 0;
}

//概率生成器 只传入一个参数代表概率 传入两个参数 则判断经过随机以后的数字是否等于第二个参数 传入三个参数则代表第一个参数经过随机后 是否在第一个和第二个参数之间
int generate_probability(int probability, int firstTarget, int secondTarget)
{
    int generateValue;

    if (probability)
        generateValue = random(probability);

    if (probability && firstTarget && secondTarget)
    {
        if (section(generateValue, firstTarget, secondTarget, 1))
            return 1;
    }
    else if (!secondTarget && firstTarget && probability)
    {
        if (generateValue == firstTarget)
            return 1;
    }
    else if (probability && !firstTarget && !secondTarget)
    {
        if ( random(100) >=  (100 - probability) )
            return 1;
    }

    return 0;
}