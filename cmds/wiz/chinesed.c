inherit F_CLEAN_UP;
int main(object me, string arg)
{		
if( !arg || arg=="" )
		return notify_fail("指令格式：chinese <英文>==<中文>\n");
	if (arg)
	{
	write(INPUTTXT("请输入要将"+arg+"设定成的中文武功名称。","chinese "+arg+"==$txt#")+"\n");
		return 1;
	}
	return 0;
}
int help()
{
	write ( @HELP
指令格式：chinesed <英文>==<中文>
HELP
	);
	return 1 ;
}
