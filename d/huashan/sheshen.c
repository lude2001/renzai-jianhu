// sheshenya.c
inherit ROOM;
void create()
{
	set("short", "������");
	set("long", @LONG
����һ�μ�խ���յ�ɽ�£�����������ƣ�����Ԩ���޵ס��粻С��
��һʧ�����ȥ��ֻ������ͷ���Ҳ����������и�Сɽ��(dong)��
LONG );
	set("exits", ([ /* sizeof() == 1 */
	    "eastdown" : __DIR__"canglong",
	]));
	set("item_desc", ([
		"��ɽ����" : "����������ʯ�ڵ�С�����ں����Ĳ�֪�ж��\n"
		ZJOBACTS2"�궴:enter dong\n",
		"����" : ZJOBACTS2"����ȥ:jump down\n",
	]));
	set("outdoors", "xx" );

	setup();
}

void init()
{
	object me = this_player();
	add_action("do_enter", "enter");
	add_action("do_enter", "zuan");
	add_action("do_jump", "jump");
	if (me->query_temp("xunshan")) me->set_temp("xunshan/sheshen", 1);
	return;
}

int do_jump(string arg)
{
	object me=this_player(), room;

	if(!arg || arg!="down")
		return notify_fail("������벻ͨ��\n");

	if(!( room = find_object("/d/yihua/xiaojin")) )
		room = load_object("/d/yihua/xiaojin");

	if(!objectp(room))
		return notify_fail("ERROR:not found 'xiaojin.c' \n");
	message_vision("$N˫��һ�գ���Ȼ������ȥ��\n",me);
//       ��message("vision","��ֻ��һ����Ӱ���������\n", room);
        me->move(room);
        return 1;
}

int do_enter(string arg)
{
	object me;
	mapping fam;

	me = this_player();
	if( !arg || arg=="" ) return 0;
	if( arg=="dong" )
	{
	   if( (fam = me->query("family")) && fam["family_name"] == "ؤ��")
	   {
	       message("vision",
			me->name() + "����ؤ�����ǹ���һ�������������˽�ȥ��",
			environment(me), ({me}) );
	       me->move("/d/gaibang/underhs");
	       message("vision",
			me->name() + "�Ӷ������˽�����\n",
			environment(me), ({me}) );
			return 1;
	   }
	   else  return notify_fail("��ôС�Ķ�������ý�ȥ��\n");
       }
}
