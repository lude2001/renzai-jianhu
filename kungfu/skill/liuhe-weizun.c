// literate.c

inherit SKILL;

string type() { return "knowledge"; }
string query_msg() { return "ÿ10������1�㱩����,����ͨ��ѧϰ���о�����"; }

int valid_learn(object me)
{
    return notify_fail("����Ϊ���޷�ͨ������;��ѧϰ��\n");

	return 1;
}

void skill_improved(object me)
{
    int s;
    s = me->query_skill("liuhe-weizun", 1);

    if (s%10==0){
	tell_object(me, HIW "��������ѧ��������"+HIY"�������ʡ�"+NOR+"����ˡ�\n");
    }

}
