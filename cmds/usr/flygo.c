// miss ׷Ѱ��Ʒ

#include <ansi.h>

inherit F_CLEAN_UP;
string *anjian=({
"ǩ��:daysign",
"�齱:luckdraw",
// "��ȡ�����:flygo daizi",
// "����װ��:walk Īа",
// "��ʦ��:walk ʦ��",
// "�Խ�����:flygo room",
// "ʦ�Ŷһ�:smdh",
// "�ٸ�����:walk ��ҩ��",
// "��������:maintask",
"�������:who",
// "ħ��:flygo moku",
// "�þ�:flygo huanjing",
// "��������:flygo caoren",
// "Ԫ�����׽���:fanli",
// "������ѡ����:new_fanli",
// "��ɽ�۽�:flygo lunjian",
// "ʦ��ɨ��:shimensd",
// "����ɨ��:wolongsd",
// "�������ϳ�:cmhc",
//"��Ϧ֮��:flygo qixi",
// "ʱ�䳤��:flygo god_mj",
// "�߽������ʸ�����:mengpai_tuijian",
});
mapping where=([
"qiandao":"/d/city/wumiao",
"daizi":"/d/wizard/guest_room",
"room":"/data/hell/4/guangchang",
"lunjian" : "/d/lunjian/enter",
"turen" : "/d/pk/entry",
"qianchi" : "/d/fuben/qianchipu/qianchipu",
]);
int main(object me, string str)
{

	if(environment(me)->query("no_magic", 1))
		return notify_fail("�����޷�ʹ��������ܡ�\n");
	
 if(!str)
 {
string bynb,msg;
msg=ZJOBLONG"���¹��ܼ�����ѡ��\n"ZJOBACTS2+ZJMENUF(4,4,8,30);
  foreach (bynb in anjian)
 msg+= bynb+ZJSEP;

 if (environment(me)->query("outdoors") == "hell" || environment(me)->query("owner_build")==getuid(me))
 {
	msg +="������԰:crroom"ZJSEP"������԰:crroom"ZJSEP"�޸ļ�԰:edroom"ZJSEP"���ӹ���:edroom"ZJSEP"�������:delroom"ZJSEP"��԰����:closeroom"ZJSEP;
 }

 msg+="Ѱ·:walk\n";
 tell_object(me,msg);
 return 1;
 }

	if (me->is_ghost())
		return notify_fail("�㻹�ǵȻ�������˵�ɡ�\n");
	if (me->is_busy())
		return notify_fail("��������æ��\n");
	if (me->is_fighting())
		return notify_fail("������ս���С�\n");

    {	//����
    	object room;
    	
        if (str == "moku")
        {
        	if(!objectp(room = new("/d/fuben_moku/moku")))
        	{
        		write("��������ʧ�ܡ�\n");
        		return 1;
        	}
        	if(!room->start_fuben_moku(this_player()))
        		destruct(room);
        	return 1;
        }
        if (str == "caoren")
        {
        	if(!objectp(room = new("/d/fuben_caoren/shilianchang")))
        	{
        		write("��������ʧ�ܡ�\n");
        		return 1;
        	}
        	if(!room->start_fuben_caoren(this_player()))
        		destruct(room);
        	return 1;
        }
        
        if (str == "huanjing")
        {
            "/d/fuben_huanjing/huanjing"->start_fuben(me);
            return 1;
        }
        
//         if (str == "qixi")
// 		{
// 			"/d/fuben/qixi/enter"->enquire_fuben(me);

// 			return 1;
// 		}
		
		if (str == "god_mj")
		{
            if (me->query("yuanbao") < 50)
            {
                write("���Ԫ����Ŀ����50��\n");
                return 1;
            }
            
            if (me->query("god_mj/time") / 86400 >= time() / 86400)
            {
                write("������Ѿ���ս��ʱ�䳤���ˡ�\n");
                return 1;
            }
            
//             if (me->query("id") != "wwweee2")
// 			{
// 				write("������.\n");
// 				return 1;
// 			}
			
			if (!me->query("guizhen"))
			{
			   write("����δ���棬û��������ѧ�����⣬���Խ���ʱ��֮�����׶�ʧ������\n");
			   return 1;
			}
			
			me->add("yuanbao",-50);
            me->set("god_mj/time",time());
            
            //��һ��ʱ�����ֹ��ͼ�ظ�
			me->move(new("/xuni/god_mj/map/room/" + time() + ",1,1"));

			return 1;
		}
    }

 if (stringp(where[str]))
 me->move(where[str]);
return 1;	
}

int help(object me)
{
write(@HELP
ָ���ʽ :
baiyiţ�ƣ�
HELP
    );
    return 1;
}
