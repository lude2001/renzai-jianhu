inherit F_CLEAN_UP;
int main(object me, string arg)
{		
if( !arg || arg=="" )
		return notify_fail("ָ���ʽ��chinese <Ӣ��>==<����>\n");
	if (arg)
	{
	write(INPUTTXT("������Ҫ��"+arg+"�趨�ɵ������书���ơ�","chinese "+arg+"==$txt#")+"\n");
		return 1;
	}
	return 0;
}
int help()
{
	write ( @HELP
ָ���ʽ��chinesed <Ӣ��>==<����>
HELP
	);
	return 1 ;
}
