#include <ansi.h>
// �嶾���嶾�� wudu-jing
inherit SKILL; 
string type() { return "knowledge"; } 

int is_fmsk() { return 1; }
string family_name() { return "�嶾��"; }

int valid_learn(object me)
{        
        if (me->query_skill("wudu-qishu", 1) < 200)
                return notify_fail("���嶾��������㣬�޷���ϰ�嶾�塣\n");        
        
        if( me->query("family/family_name") != family_name() )
                return notify_fail("�嶾��ֻ���嶾�̵��ӷ�����ϰ��\n");

        if (me->query_skill("qianzhu-wandushou", 1) < 180)
                return notify_fail("��ǧ��������Ϊ���㣬�޷�������ϰ�嶾�塣\n");

        return 1;
}

int difficult_level()
{
        return 2000;
}