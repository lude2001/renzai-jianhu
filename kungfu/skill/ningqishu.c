inherit SKILL;

string type() { return "knowledge"; }

int valid_enable(string usage) { return usage == "fufa"; }

int valid_learn(object me)
{
    if (me->query("family/family_name") != "武当派" && me->query("family/family_name") != "全真教")
        return notify_fail("非道教中人无法修行凝气术。\n");
    
	if ((int)me->query_skill("fufa", 1) < 100)
		return notify_fail("你的符法基础造诣太浅，无"
				   "法领会深奥的凝气术。\n");

	if ((int)me->query_skill("fufa", 1) < (int)me->query_skill("ningqishu", 1))
		return notify_fail("你的符法基础水平有限，无"
				   "法掌握更深奥的凝气术。\n");

	return 1;
}


string perform_action_file(string action)
{
	return __DIR__"ningqishu/" + action;
}