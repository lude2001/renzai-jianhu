// Room: /city/chaguan.c 
inherit ROOM; 
	
void create() 
{ 
	set("short", "�������"); 
	set("long", @LONG 
��һ�߽��������ŵ�һ�ɲ���������Ƣ������Ϊ֮һˬ�����Ű�����һ�� 
�ſ��������˿��ˣ������̸Ц����ͷ�Ӷ�����Ҫ����������ƹʺ�ҥ�ԣ� 
�����Ǹ������ڡ� 
LONG 
	); 
	set("resource/water", 1); 
	set("exits", ([



		"east" : __DIR__"nandajie2", 
		"down" : __DIR__"bocai",
	])); 
	set("objects", ([ 
		__DIR__"npc/aqingsao" : 1, 
		"/kungfu/class/youxia/fu" : 1, 
		"/kungfu/class/youxia/wu" : 1, 
		"/kungfu/class/youxia/qing" : 1, 
		"/kungfu/class/youxia/xiao" : 1, 
	])); 
	setup(); 
	replace_program(ROOM); 
} 
