// literate.c

inherit SKILL;

string type() { return "knowledge"; }
string query_msg() { return "每10级提升1点暴击率,不能通过学习和研究提升"; }

int valid_learn(object me)
{
    return notify_fail("六合为尊无法通过特殊途径学习。\n");

	return 1;
}

void skill_improved(object me)
{
    int s;
    s = me->query_skill("liuhe-weizun", 1);

    if (s%10==0){
	tell_object(me, HIW "由於你的勤学苦读，你的"+HIY"【暴击率】"+NOR+"提高了。\n");
    }

}
