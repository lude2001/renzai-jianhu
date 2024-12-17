#include <ansi.h>

inherit F_CLEAN_UP;
void lingqu_gift(mapping gift_list, object me);     //������Ʒ����

// mapping attribute_chinese = ([
//      "skill_gem":"��ѡ��ѧ��ʯ����һ��",
// ]);

int main(object me, string arg)
{
     //����VIP����Ҫ�Ĺ���
     int * vip_gongxian = ({ 30,50,100,200,300,400, 500,600,1000, 2000,3000,4000,5000/*, 3000, 4000, 5000, 6000, 7000, 9000, 10000*/});

     //itemΪ��������Ʒ��skill_gemΪ��ѡ��ʯ���书����
     mapping vip_gitf = ([
          1 : ([ "item" : ([ "/clone/vip/xumibei" : 1, "/clone/vip/dan_jiuzhuan":2,"/clone/vip/putao1":2]), ]),//30
          2 : ([ "item" : ([ "/clone/vip/butian" : 2,  "/clone/vip/dan_jiuzhuan":2,"/clone/vip/putao1":4,"/clone/baiyi/tencard":1]), ]),//50
          3 : ([ "item" : ([ "/clone/vip/dan_chongmai1" : 50,  "/clone/shizhe/mengzi":1,"/clone/vip/putao1":5,"/clone/baiyi/tencard":1]), ]),//100
          4 : ([ "item" : ([ "/clone/vip/dan_chongmai1" : 100,  "/clone/shizhe/mengzi":1,"/clone/vip/putao1":5,"/clone/baiyi/tencard":1,"/clone/shizhe/kuilei":1]), ]),//200
          5 : ([ "item" : ([ "/clone/vip/dan_chongmai1" : 150, "/clone/vip/putao1":5,"/clone/baiyi/tencard":1,"/clone/shizhe/kuilei":1]), ]),//300
          6 : ([ "item" : ([ "/clone/vip/dan_chongmai1" : 200, "/clone/vip/putao1":5,"/clone/baiyi/tencard":1,"/clone/shizhe/kuilei":1]), ]),//400
          7 : ([ "item" : ([ "/clone/vip/dan_chongmai2" : 50, "/clone/vip/putao1":5,"/clone/baiyi/tencard":1,"/clone/shizhe/kuilei":1]), ]),//500
          8 : ([ "item" : ([ "/clone/vip/dan_chongmai2" : 100, "/clone/vip/putao1":5,"/clone/baiyi/tencard":1,"/clone/shizhe/kuilei":1]), "skill_gem":1]),//600
          9 : ([ "item" : ([ "/clone/vip/dan_chongmai3" : 100, "/clone/vip/dan_xixin":1,"/clone/baiyi/tencard":2,"/clone/shizhe/kuilei":2]), ]),//1000
          10 : ([ "item" : ([ "/clone/vip/dan_chongmai3" : 200]),"skill_gem" : 1 ]),//2000
          11 : ([ "item" : ([ "/clone/vip/dan_chongmai3" : 200,"/clone/vip/dan_chongmai2" : 300,"/clone/vip/dan_jiuzhuan" : 30]),"skill_gem" : 1 ]),//3000
          12 : ([ "item" : ([ "/clone/vip/dan_chongmai3" : 250,"/clone/vip/dan_chongmai2" : 350,"/clone/vip/dan_jiuzhuan" : 40]),"skill_gem" : 1 ]),//4000
          13 : ([ "item" : ([ "/clone/vip/dan_chongmai3" : 300,"/clone/vip/dan_chongmai2" : 400,"/clone/vip/dan_chongmai4" : 100,"/clone/vip/dan_jiuzhuan" : 50]),"skill_gem" : 1 ]),//5000
     ]);

     string * skill_list = ({
          "jiuyang-shengong",
          "shenzhaojing",
          "qishang-quan",
          "baihua-quan",
          "hanbing-mianzhang",
          "xuanming-zhang",
          "shexing-lifan",
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

     string * gem_list = ({
          "/clone/gem/hujiagem",
          "/clone/gem/lonelygem",
          "/clone/gem/xuedaogem",
          "/clone/gem/xueshangem",
          "/clone/gem/manmiao-gem",
           "/clone/gem/luoye",
          "/clone/gem/hmgonggem",
          "/clone/gem/liumai-qi",
          "/clone/gem/liumai-six",
          "/clone/gem/xianglong-xiang",
          "/clone/gem/qitun-gem",
          "/clone/gem/shedao-chang1",
     });

     int vip_level = 0;
     int i;
     string sign;
     int choose_lvl;
     string str = "";
     string temp;
     string skill_id;
     string gem_file_name;
     object gem;

     //����VIP�ȼ�
     for (i = 0; i < sizeof(vip_gongxian); i++)
     {
          if (me->query("cxpay/gongxian") >= vip_gongxian[i])
               vip_level++;
          else
               break;
     }

     if (!arg || arg == "")
     {
          string msg = "";
          
          tell_object(me, ZJOBLONG + "�㵱ǰ��VIP�ȼ�Ϊ" + vip_level + "��Ҫִ��ʲô������\n" + ZJOBACTS2 + "�һ�VIP����:new_fanli vip" + ZJSEP + "��ѡ��ʯ:new_fanli gem" + ZJSEP + "��ѡ�书:new_fanli skill"ZJSEP + "֧�ֽ���:new_fanli sc\n");
          return 1;
     }
    
    if (arg == "sc")
    {
        object lunyu,card,book;
        
        if (me->query("cxpay/zhichi") || me->query("cxpay/gongxian") < 6)
        {
            return 1;
        }
        
        lunyu = new_bind("/clone/shizhe/lunyu");
        card = new_bind("/clone/baiyi/tencard");
        book = new_bind("/clone/vip/book/force100-book");
        
        me->set("cxpay/zhichi",1);
        
        lunyu->move(me);
        card->move(me);
        book->move(me);
        
        me->set("cxpay/zhichi",1);
        
        write("��л������Ϸ����������֧��,������������һ������,һ��ʮ���鿨Ƭ��һ��<<�ڹ��ܸ�һ>>��\n");
        return 1;
    }
     //�һ�VIP����
     if (arg[0..2] == "vip")
     {
          if (sscanf(arg, "%*s %d %s", choose_lvl, sign) == 3)
          {
               if (sign != "y")
               {
                    tell_object(me, "��ȡVIP����ʱ������������������ԡ�\n");
                    return 1;
               }

               lingqu_gift(vip_gitf[choose_lvl]["item"], me);    //������Ʒ����

               if (vip_gitf[choose_lvl]["skill_gem"])
               {
                    me->add("cxpay/skill_gem", vip_gitf[choose_lvl]["skill_gem"]);
                    tell_object(me, "������" + vip_gitf[choose_lvl]["skill_gem"] + "����ѡ�书/��ʯ���ᡣ\n");
               }
               log_file("cxpay/vip", ctime(time()) + me->query("name") + "(" + me->query("id") + ")��ȡ��" + choose_lvl + "��VIP������\n");
               me->set("cxpay/fanli_lingqu/" + choose_lvl, 1);

               return 1;
          }
          else if (sscanf(arg, "%*s %d", choose_lvl) == 2)
          {
               if (me->query("cxpay/fanli_lingqu/" + choose_lvl))
               {
                    tell_object(me, "���Ѿ���ȡ���õȼ��ķ����ˡ�\n");
                    return 1;
               }

               tell_object(me, ZJOBLONG + "��ȷ���һ�" + choose_lvl + "��VIP������\n" + ZJOBACTS2 + "ȷ��:new_fanli vip " + choose_lvl + " y\n");
               return 1;
          }
          else 
          {
               if (0 == vip_level) 
               {
                    tell_object(me, ZJOBLONG + "��Ŀǰ��VIP�ȼ�Ϊ0���޷��һ���\n");
                    return 1;
               }

               str += ZJOBLONG + "��Ŀǰ���Զһ���VIP����Ϊ��\n" + ZJOBACTS2;

               for (i = 1; i <= vip_level; i++)
               {
                    str += "�ȼ�" + chinese_number(i) + ":new_fanli vip " + i + ZJSEP;
               }

               tell_object(me, str + "\n");
               return 1;
          }
     }

     //��ѡ�书
     if (arg[0..4] == "skill")
     {
          if (sscanf(arg, "%*s %s %s", skill_id, sign) == 3)
          {
               if (sign != "y")
               {
                    tell_object(me, "��ѡ�书ʱ������������������ԡ�\n");
                    return 1;
               }

               me->add("cxpay/skill_gem", -1);
               me->set_skill(skill_id, 180);
               log_file("cxpay/skill", ctime(time()) + me->query("name") + "(" + me->query("id") + ")�һ���" + to_chinese(skill_id) + "��\n");
               tell_object(me, "��һ���" + to_chinese(skill_id) + "��\n");

               return 1;
          }
          else if (sscanf(arg, "%*s %s", skill_id) == 2)
          {
               if (me->query("cxpay/skill_gem") < 1)
               {
                    tell_object(me, "�����ѡ�书/��ʯ���������ˡ�\n");
                    return 1;
               }

               if (me->query_skill(skill_id))
               {
                    tell_object(me, ZJOBLONG + "���Ѿ�ѧ����" + to_chinese(skill_id) + "��ȷ��Ҫ�һ���(�һ��Ḳ��ԭ�ȼ�)\n" + ZJOBACTS2 + "ȷ��:new_fanli skill " + skill_id + " y\n");
                    return 1;
               }

               tell_object(me, ZJOBLONG + "��ȷ��Ҫ�һ�" + to_chinese(skill_id) + "��\n" + ZJOBACTS2 + "ȷ��:new_fanli skill " + skill_id + " y\n");
               return 1;
          }
          else
          {
               if (!sizeof(skill_list))
               {
                    tell_object(me, ZJOBLONG + "���ڻ�û�пɶһ����书��\n");
                    return 1;
               }

               str += ZJOBLONG + "Ŀǰ���Զһ����书�У�\n" + ZJOBACTS2;

               foreach (temp in skill_list)
               {
                    str += to_chinese(temp) + ":new_fanli skill " + temp + ZJSEP;
               }

               tell_object(me, str + "\n");
               return 1;
          }
     }

     //��ѡ��ʯ
     if (arg[0..2] == "gem")
     {
          if (sscanf(arg, "%*s %s %s", gem_file_name, sign) == 3)
          {
               if (sign != "y")
               {
                    tell_object(me, "��ѡ��ʯʱ������������������ԡ�\n");
                    return 1;
               }

               if (!objectp(gem = new(gem_file_name)))
               {
                    tell_object(me, "��ȡ��ѡ��ʯ��������ϵ����Ա����\n");
                    return 1;
               }

               log_file("cxpay/gem", ctime(time()) + me->query("name") + "(" + me->query("id") + ")��ȡ��" + gem->query("name") + "��\n");
               tell_object(me, "��һ���һ" + (gem->query_amount()?gem->query("base_unit"):gem->query("unit")) + gem->query("name") + "��\n");
               me->add("cxpay/skill_gem", -1);
               gem->move(me);

               return 1;
          }
          else if (sscanf(arg, "%*s %s", gem_file_name) == 2)
          {
               if (me->query("cxpay/skill_gem") < 1)
               {
                    tell_object(me, "�����ѡ�书/��ʯ���������ˡ�\n");
                    return 1;
               }

               tell_object(me, ZJOBLONG + "��ȷ��Ҫ�һ�" + load_object(gem_file_name)->query("name") + "��\n" + ZJOBACTS2 + "ȷ��:new_fanli gem " + gem_file_name + " y\n");
               return 1;
          }
          else
          {
               if (!sizeof(gem_list))
               {
                    tell_object(me, ZJOBLONG + "Ŀǰ��û�п��Զһ��ı�ʯ��\n");
                    return 1;
               }

               str += ZJOBLONG + "Ŀǰ���Զһ��ı�ʯ�У�\n" + ZJOBACTS2;
               foreach (temp in gem_list)
               {
                    str += load_object(temp)->query("name") + ":new_fanli gem " + temp + ZJSEP;
               }

               tell_object(me, str + "\n");
               return 1;
          }
     }

     return 1;
}


void lingqu_gift(mapping gift_list, object me)
{
     string temp;
     object gift;
     int i;

     foreach (temp in keys(gift_list))
     {
          if (!objectp(gift = new(temp)))
          {
               tell_object(me, "��ȡ" + temp + "ʱ����\n");
               continue;
          }

          if (gift->query_amount())
          {
               gift->set_amount(gift_list[temp]);
               tell_object(me, "������" + gift_list[temp] + gift->query("base_unit") + gift->query("name") + "��\n");
               gift->move(me);
          }
          else
          {
               i = 0;
               do {
                    if (0 == i)
                    {
                         gift->move(me);
                         i++;
                         continue;
                    }

                    if (!objectp(gift = new(temp)))
                    {
                         tell_object(me, "��ȡ" + temp + "ʱ����\n");
                         i++;
                         break;
                    }

                    gift->move(me);
                    i++;
               } while (i < gift_list[temp]);
               tell_object(me, "������" + i + gift->query("unit") + gift->query("name") + "\n");
          }
     }
}