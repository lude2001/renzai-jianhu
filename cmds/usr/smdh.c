#include <ansi.h>

nosave mapping chenghao_list = ([
    0 : (["name" :({"九阳神功", }),"id" :({"jiuyang-shengong", }),"lev" :({180, }),"gx" :({25000,}),"type" :({1,}),]),
    1 : (["name" :({"神照经", }),"id" :({"shenzhaojing", }),"lev" :({180, }),"gx" :({20000,}),"type" :({1,}),]),
    2 : (["name" :({"凝血神爪", }),"id" :({"ningxue-shenzhao", }),"lev" :({180, }),"gx" :({19000,}),"type" :({1,}),]),
    3 : (["name" :({"补天石", }),"address" :({"/clone/vip/butian", }),"gx" :({6000,}),"type" :({2,}),]),
    4 : (["name" :({"冰蚕丝", }),"address" :({"/clone/vip/tiancs", }),"gx" :({6000,}),"type" :({2,}),]),
    5 : (["name" :({"10血量", }),"id" :({"10xue", }),"add" :({10, }),"onlie" :({100, }),"gx" :({100,}),"info" :({"gain/max_qi",}),"type" :({3,}),]),
    6 : (["name" :({"20内力", }),"id" :({"20nei", }),"add" :({20, }),"onlie" :({100, }),"gx" :({100,}),"info" :({"max_neili",}),"type" :({3,}),]),
    7 : (["name" :({"天香玉露", }),"address" :({"/clone/maintask/obj/tianxiang"}), "gx" : ({300}), "type" : ({2,}),]),
    8 : (["name" :({"神奇葡萄", }),"address" :({"/clone/vip/putao1", }),"gx" :({300,}),"type" :({2,}),]),
    9 : (["name" :({"天灵丹", }),"address" :({"/clone/vip/tianling", }),"gx" :({200,}),"type" :({2,}),]),
    10 : (["name" :({"下品冲脉丹", }),"address" :({"/clone/vip/dan_chongmai1", }),"gx" :({20,}),"type" :({2,}),]),
]);

int main(object me, string arg)
{
    string str;
    mapping my;
    int i,type,status;
    object ob;
    my = me->query_entire_dbase();

    if (! arg){
        str = ZJOBLONG"你目前的师门贡献有"+ my["gongxian"] +"，请选择您想兑换的武功：\n"ZJOBACTS2+ZJMENUF(4,4,8,30); 
        for(i=0;i<sizeof(chenghao_list);i++){
            //str += sprintf("%s:smdh dh %d"ZJBR" %s"ZJSEP,chenghao_list[i]["name"][0],i,chenghao_list[i]["gx"][0]+"贡献");
            str += sprintf("%s"ZJBR"%s:smdh dh %d %d"ZJSEP,chenghao_list[i]["name"][0],chenghao_list[i]["gx"][0]+"贡献",i,(int)chenghao_list[i]["type"][0]);
        }
        write(str+"\n");
        return 1;
    } 
    if(sscanf(arg,"dh %d %d",type,status)==2){
        //判断贡献是不是足够
        if(my["gongxian"] >= (int)chenghao_list[type]["gx"][0]){
            //判断是技能还是要物品
            if(status == 1){
                me->set_skill(chenghao_list[type]["id"][0],(int)chenghao_list[type]["lev"][0]);
                write("你成功从商城兑换了"HIM"" + chenghao_list[type]["name"][0]+"。"NOR"\n");
                me->add("gongxian",-(int)chenghao_list[type]["gx"][0]);
                return 1;
            }
            if(status == 2){
                ob = new_bind(chenghao_list[type]["address"][0],1);
                ob->move(me);
                me->add("gongxian",-(int)chenghao_list[type]["gx"][0]);
                write("你成功从商城兑换了"HIM"" + chenghao_list[type]["name"][0]+"。"NOR"\n");
                return 1;
            }
            if(status == 3){
                //判断人物有没有达到使用上限
                if(me->query(chenghao_list[type]["id"][0]) < (int)chenghao_list[type]["onlie"][0]){
                    me->add(chenghao_list[type]["info"][0],chenghao_list[type]["add"][0]);
                    me->add(chenghao_list[type]["id"][0],1);
                    me->add("gongxian",-(int)chenghao_list[type]["gx"][0]);  
                    write("你成功从商城兑换了"HIM"" + chenghao_list[type]["name"][0]+"。"NOR"\n");  
                    write("您当前兑换"HIM"" + chenghao_list[type]["name"][0]+"。"NOR "" + me->query(chenghao_list[type]["id"][0]) + "次\n");
                    return 1;
                }else{
                    write("您可兑换次数已经达到了上限，最多一百次！\n");
                }

            }
        }else{
            write("您的贡献不够！\n");
            return 1;
        }
    }  
}