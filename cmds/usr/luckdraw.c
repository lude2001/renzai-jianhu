#include <ansi.h>

int start_ken(object me);
int main(object me, string arg)
{ 
string str;
    if (! arg){
        str = ZJOBLONG"���ص�ǰ�аٷ�֮4�ļ��ʳ鵽��ʯ���ٷ�֮��鵽��������";
        str += ZJBR"150Ԫ����һ��, 1400Ԫ��ʮ����";
        str += ZJBR"���龭���㹻����������180���ٽ��г齱��";
        str += ZJBR"����鵽�����������ߵȼ��������";
        str += ZJBR"�Ų����𣡣�";
        str += "\n"ZJOBACTS2+ZJMENUF(4,4,8,30); 
        if (present("ten card",me))
        	str += "ʮ����:luckdraw ten"ZJSEP;
        if  (present("one card",me))
        	str += "���鿨:luckdraw one"ZJSEP;
        str += "Ԫ������:luckdraw yuanbao"ZJSEP;
        str += "Ԫ��ʮ��:luckdraw yuanbao_sl";
        write(str+"\n");
        return 1;
    }
    if(arg == "yuanbao"){
        if(me->query("yuanbao")<150)
            return notify_fail("��ȷ�������㹻��Ԫ����\n");       
            me->add("yuanbao",-150);
            start_ken(me);
    }
    
    if (arg == "yuanbao_sl")
    {
        int i;
        
        if (me->query("yuanbao") < 1400)
            return notify_fail("��ȷ�������㹻��Ԫ����\n");
        
        me->add("yuanbao", -1400);
        for(i = 0; i < 10; i++)
        {
            start_ken(me);
        }
        return 1;
    }
    
    if(arg == "one")
    {
    	object ob;
    	if (!objectp(ob = present("one card",me)))
        {
            if (!ob->query("yuanbao"))
    		return notify_fail("����û�е��鿨������\n");
        }
        if (!ob->query("yuanbao"))
        return notify_fail("����û�е��鿨������\n");
    	ob->add_amount(-1);
    	start_ken(me);
    	return 1;
    }
    
    if (arg == "ten")
    { 
    object ob;
    int i=0;
       if (!objectp(ob = present("ten card",me)))
       return notify_fail("����û��ʮ���鿨������\n");    
       ob->add_amount(-1);
       while (i<10)
       {
       start_ken(me);
       i++;
       }
       return 1;
    }
    return 1;

}
int start_ken(object me)
{
//������Ʒ Ԫ������
    string *ob_list = ({
        "/clone/gift/dan_chongmai3",
        "/clone/gift/dan_chongmai3",
        "/clone/gift/dan_chongmai3",
        "/u/cx/luck/butian",
        "/u/cx/luck/tiancs",
        "/u/cx/luck/tiancs",
        "/u/cx/luck/jiuzhuan",
        "/clone/vip/card_name",
        "/clone/vip/card_name",
    });
    
    //�������
    string *pt_list = ({
        "/u/cx/luck/putao",
        "/u/cx/luck/daputao",
        "/u/cx/luck/daputao",
        "/u/cx/luck/daputao",
        "/u/cx/luck/daputao",
        "/u/cx/luck/putao",
        "/u/cx/luck/lingzhi",
        "/clone/gift/hundunshi",
         "/clone/gift/dan_chongmai1",
        "/clone/gift/dan_chongmai2",
        "/u/cx/luck/putao",
        "/u/cx/luck/lingzhi",
         "/clone/gift/dan_chongmai1",
        "/clone/gift/dan_chongmai2",
        "/u/cx/luck/putao",
        "/u/cx/luck/lingzhi",
         "/clone/gift/dan_chongmai1",
        "/clone/gift/dan_chongmai2",
        "/u/cx/luck/putao",
        "/u/cx/luck/lingzhi",
         "/clone/gift/dan_chongmai1",
        "/clone/gift/dan_chongmai2",
        "/u/cx/luck/putao",
        "/u/cx/luck/lingzhi",
         "/clone/gift/dan_chongmai1",
        "/clone/gift/dan_chongmai2",
        
    });
    
    //�������
    string *skill_list = ({
      //  "jiuyang-shengong",
       // "shenzhaojing",
        "qishang-quan",
        "baihua-quan",
        "hanbing-mianzhang",
        "xuanming-zhang",
        "sougu",
         "zhuihun-jian",
        "yunlong-bian",
        "hanxing-bada",
        "bizhen-qingzhang",
         "huanyin-zhi",
        "ningxue-shenzhao",
        "sanfen-jianshu",
        "zijinbagua-dao",
    });

    //��ʯ���
    string *gem_list = ({
        "/clone/gem/hujiagem",
        "/clone/gem/wanjian",
        "/clone/gem/lonelygem",
        "/clone/gem/xuedaogem",
        "/clone/gem/luoye",
        "/clone/gem/liuyang-rx",
        "/clone/gem/lonelyfxgem",
        "/clone/gem/lonelyymgem",
         "/clone/gem/xueshangem",
         "/clone/gem/manmiao-gem",
         "/clone/gem/hmgonggem",
         "/clone/gem/liumai-qi",
         "/clone/gem/liumai-six",
         "/clone/gem/xianglong-xiang",
         "/clone/gem/qitun-gem",
         "/clone/gem/shedao-chang1",
    });
    
     mapping skills;
    string str,*sk,skill;
    int random,i;
    object obj;
    
    random = random(100)+1;
        if(random<=1 || me->query("luckdraw/number") >= 100){
            obj = new(gem_list[random(sizeof(gem_list))]);
            me->delete("luckdraw/number");//�鵽��ʯ�Ժ��������
            
            if (random(30) == 1)
            {
            me->set("special_skill/lun", 1);
            write("��ϲ�����˱��ڲʵ����츳�����������ֻ�.\n");
            CHANNEL_D->do_channel(this_object(),"rumor",me->query("name")+"����˱��ڲʵ����츳�����������ֻ�!\n");
            }
            
        }else if(random<=1){
            skill = skill_list[random(sizeof(skill_list))];
            //�жϻ�ļ�������û�д˼���
            skills = me->query_skills();
		    sk = keys(skills);
            for(i=0; i<sizeof(skills); i++) {
                if(skill == sk[i]){
                	log_file("luckdraw", ctime(time()) + "   " + me->name() + me->query("id") + "  �鵽��ӵ���书" + skill + "\n");
                    write("��鵽��һ�����Ѿ�ѧ��ļ��ܣ���ξͲ�������\n");
                    return 1;
                }
            }

            me->set_skill(skill,180);
       //     me->add("yuanbao",-150);
            log_file("luckdraw", ctime(time()) + "   " + me->name() + me->query("id") +  "  �鵽" + skill + "\n");
            write("��ϲ�鵽��"+ skill +"��!\n");
            CHANNEL_D->do_channel(this_object(),"rumor",me->query("name")+"�鵽��һ�����ܡ�"+ skill +"��!\n");
            return 1;
        }else if(random<=85){
            obj = new(pt_list[random(sizeof(pt_list))]);
        }else{
            obj = new(ob_list[random(sizeof(ob_list))]);
        }
        log_file("luckdraw", ctime(time()) + "   " + me->name() + me->query("id") + "  �鵽" + obj->name() + "\n");
        obj->move(me);
        
        me->add("luckdraw/number",1);//���㱣��
        write("��ϲ�鵽��"+ obj->query("name") +"��!\n");
  //      me->add("yuanbao",-150);
        CHANNEL_D->do_channel(this_object(),"rumor",me->query("name")+"�鵽��һ����Ʒ��"+ obj->query("name") +"��!\n");
        return 1;
}