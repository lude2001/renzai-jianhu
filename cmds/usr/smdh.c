#include <ansi.h>

nosave mapping chenghao_list = ([
    0 : (["name" :({"������", }),"id" :({"jiuyang-shengong", }),"lev" :({180, }),"gx" :({25000,}),"type" :({1,}),]),
    1 : (["name" :({"���վ�", }),"id" :({"shenzhaojing", }),"lev" :({180, }),"gx" :({20000,}),"type" :({1,}),]),
    2 : (["name" :({"��Ѫ��צ", }),"id" :({"ningxue-shenzhao", }),"lev" :({180, }),"gx" :({19000,}),"type" :({1,}),]),
    3 : (["name" :({"����ʯ", }),"address" :({"/clone/vip/butian", }),"gx" :({6000,}),"type" :({2,}),]),
    4 : (["name" :({"����˿", }),"address" :({"/clone/vip/tiancs", }),"gx" :({6000,}),"type" :({2,}),]),
    5 : (["name" :({"10Ѫ��", }),"id" :({"10xue", }),"add" :({10, }),"onlie" :({100, }),"gx" :({100,}),"info" :({"gain/max_qi",}),"type" :({3,}),]),
    6 : (["name" :({"20����", }),"id" :({"20nei", }),"add" :({20, }),"onlie" :({100, }),"gx" :({100,}),"info" :({"max_neili",}),"type" :({3,}),]),
    7 : (["name" :({"������¶", }),"address" :({"/clone/maintask/obj/tianxiang"}), "gx" : ({300}), "type" : ({2,}),]),
    8 : (["name" :({"��������", }),"address" :({"/clone/vip/putao1", }),"gx" :({300,}),"type" :({2,}),]),
    9 : (["name" :({"���鵤", }),"address" :({"/clone/vip/tianling", }),"gx" :({200,}),"type" :({2,}),]),
    10 : (["name" :({"��Ʒ������", }),"address" :({"/clone/vip/dan_chongmai1", }),"gx" :({20,}),"type" :({2,}),]),
]);

int main(object me, string arg)
{
    string str;
    mapping my;
    int i,type,status;
    object ob;
    my = me->query_entire_dbase();

    if (! arg){
        str = ZJOBLONG"��Ŀǰ��ʦ�Ź�����"+ my["gongxian"] +"����ѡ������һ����书��\n"ZJOBACTS2+ZJMENUF(4,4,8,30); 
        for(i=0;i<sizeof(chenghao_list);i++){
            //str += sprintf("%s:smdh dh %d"ZJBR" %s"ZJSEP,chenghao_list[i]["name"][0],i,chenghao_list[i]["gx"][0]+"����");
            str += sprintf("%s"ZJBR"%s:smdh dh %d %d"ZJSEP,chenghao_list[i]["name"][0],chenghao_list[i]["gx"][0]+"����",i,(int)chenghao_list[i]["type"][0]);
        }
        write(str+"\n");
        return 1;
    } 
    if(sscanf(arg,"dh %d %d",type,status)==2){
        //�жϹ����ǲ����㹻
        if(my["gongxian"] >= (int)chenghao_list[type]["gx"][0]){
            //�ж��Ǽ��ܻ���Ҫ��Ʒ
            if(status == 1){
                me->set_skill(chenghao_list[type]["id"][0],(int)chenghao_list[type]["lev"][0]);
                write("��ɹ����̳Ƕһ���"HIM"" + chenghao_list[type]["name"][0]+"��"NOR"\n");
                me->add("gongxian",-(int)chenghao_list[type]["gx"][0]);
                return 1;
            }
            if(status == 2){
                ob = new_bind(chenghao_list[type]["address"][0],1);
                ob->move(me);
                me->add("gongxian",-(int)chenghao_list[type]["gx"][0]);
                write("��ɹ����̳Ƕһ���"HIM"" + chenghao_list[type]["name"][0]+"��"NOR"\n");
                return 1;
            }
            if(status == 3){
                //�ж�������û�дﵽʹ������
                if(me->query(chenghao_list[type]["id"][0]) < (int)chenghao_list[type]["onlie"][0]){
                    me->add(chenghao_list[type]["info"][0],chenghao_list[type]["add"][0]);
                    me->add(chenghao_list[type]["id"][0],1);
                    me->add("gongxian",-(int)chenghao_list[type]["gx"][0]);  
                    write("��ɹ����̳Ƕһ���"HIM"" + chenghao_list[type]["name"][0]+"��"NOR"\n");  
                    write("����ǰ�һ�"HIM"" + chenghao_list[type]["name"][0]+"��"NOR "" + me->query(chenghao_list[type]["id"][0]) + "��\n");
                    return 1;
                }else{
                    write("���ɶһ������Ѿ��ﵽ�����ޣ����һ�ٴΣ�\n");
                }

            }
        }else{
            write("���Ĺ��ײ�����\n");
            return 1;
        }
    }  
}