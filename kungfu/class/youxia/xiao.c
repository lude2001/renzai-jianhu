#include <ansi.h>
inherit NPC;
#include "youxia.h"

void create()
{
        set_name("���޼�", ( { "xiao wuji", "xiao" }) );
        set("title", HIB"���ڽ���"NOR);
        set("gender", "����" );
        set("age", 60);
        set("long","���²��������ڞ���ʦ���������ţ������������ϣ���®���ء���Ӷ�ʮ�أ����򡰺����Ԫ�����롰�����߽��������湦��
        ���롰���µ�һ���ˡ����ͽ��Ϊֿ�ѣ��������ա��������ա���ȭ�Ʊ������գ�����ʤ֮��
        �������߽���������˫���������ԡ������Ԫ�����߶����������޸�֮ˮ���Ծó֡���\n");

        set("int", 300);
        set("str", 250);
        set("con", 300);
        set("dex", 500);
        set("per",35);
        
        set("no_get",1);
        set("youxia_skill","hanxueqi");
        
        set_temp("apply/attack", 1000);
        set_temp("apply/defense", 1000);
        set_temp("apply/damage", 1000);
        set("qi",200000);
        set("max_qi", 200000);
        set("jing", 200000);
        set("max_jing", 200000);
        set("neili", 100000);
        set("max_neili", 100000);
        set("jiali", 300);
        set("combat_exp", 30000000);
        set("score", 250000);

        set_skill("force", 3000);
        set_skill("taixuan-gong", 3000);
        set_skill("dodge", 3000);
        set_skill("tiyunzong", 3000);
        set_skill("unarmed", 3000);
        set_skill("taiji-quan", 3000);
        set_skill("parry", 3000);
        set_skill("taoism", 2000);
        set_skill("literate", 1000);

        map_skill("force", "taixuan-gong");
        map_skill("dodge", "taixuan-gong");
        map_skill("unarmed", "taixuan-gong");
        map_skill("parry", "taixuan-gong");
        
        set("inquiry", ([
                "����" :  "��֪���䲻�ϣ���ͬ��ˮ����,����ǰ��\n",
                "����" : (:xue_skill:),
            ]));

        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("gold",1);
}