// taisu-jian.c ̫�ؽ��� ��Ĺ���ռ���ѧ
//���Բο���bodyreset Ϊ�������޴���
// by ����ҹ������������
#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>
#include <condition.h>
inherit F_DBASE;
inherit SKILL;
string *order = ( {""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});
int ke_qz(object me, object victim, object weapon, int damage);
mapping *action = (
{
([      "action" : "$Nһ��"+(order[random(13)])+"������б����"NOR"������б�ɣ�����$w�������$n��$l",
		"attack":	200,
		"parry":	200,
		"dodge":	200,
		"damage":	200,
		"force":	200,
"post_action": (: ke_qz :),
	"lvl" : 0,
"damage_type" : "����"
	 ]),
([      "action" : "$N��Ծ����"+(order[random(13)])+"���׺羭�졹"NOR"��$w��Ȼ�´�",
		"attack":	200,
		"parry":	200,
		"dodge":	200,
		"damage":	200,
		"force":	200,
"post_action": (: ke_qz :),
	"lvl" : 4,
"damage_type" : "����"
	 ]),
([      "action" : "$Nʹ��"+(order[random(13)])+"���˼����ġ�"NOR"���ӽ�ֱ���������ɵ�",
		"attack":	200,
		"parry":	200,
		"dodge":	200,
		"damage":	200,
		"force":	200,
	"lvl" : 9,
"post_action": (: ke_qz :),
"damage_type" : "����"
	 ]),
([      "action" : "$Nʹ"+(order[random(13)])+"����ǰ���¡�"NOR"һ�����϶��²�����ģ����ֺ�ա�����̵صĹ⾰",
		"attack":	200,
		"parry":	200,
		"dodge":	200,
		"damage":	200,
		"force":	200,
	"lvl" : 14,
"post_action": (: ke_qz :),
"damage_type" : "����"
	 ]),
([      "action" : "$N����$w���������ʻ���չ���ػ�����ֻ�ϵ�$n�ۻ����ң��벻֪�Ӻι���",
		"attack":	200,
		"parry":	200,
		"dodge":	200,
		"damage":	200,
		"force":	200,
	"lvl" : 19,
"post_action": (: ke_qz :),
"damage_type" : "����"
	 ]),
([      "action" : "$Nʹ��"+(order[random(13)])+"������С�á�"NOR"�������𣬽�����ָ�����������ƣ�ֱ��$n��$l",
		"attack":	200,
		"parry":	200,
		"dodge":	200,
		"damage":	200,
		"force":	200,
	"lvl" : 24,
"post_action": (: ke_qz :),
"damage_type" : "����"
	 ]),
([      "action" : "$N����$w��������һ�̣�������������ʹ��"+(order[random(13)])+"��ɨѩ��衹"NOR"��",
		"attack":	300,
		"parry":	300,
		"dodge":	300,
		"damage":	300,
		"force":	300,
	"lvl" : 29,
"post_action": (: ke_qz :),
"damage_type" : "����"
	 ]),
([      "action" : "$N���ƺ����ǰ��������$w����ӷ���ȴ��һ��"+(order[random(13)])+"�����ٰ�����"NOR"",
		"attack":	300,
		"parry":	300,
		"dodge":	300,
		"damage":	300,
		"force":	300,
	"lvl" : 34,
"post_action": (: ke_qz :),
"damage_type" : "����"
	 ]),
([      "action" : "$Nһ��"+(order[random(13)])+"�����¶��ġ�"NOR"��$w���������һ���󻡣�����$n��$l",
		"attack":	300,
		"parry":	300,
		"dodge":	300,
		"damage":	300,
		"force":	300,
	"lvl" : 39,
"post_action": (: ke_qz :),
"damage_type" : "����"
	 ]),
([      "action" : "$N����������ң�������Ϊ������$n��ȴ��һ��"+(order[random(13)])+"���رߵ��ס�"NOR"",
		"attack":	300,
		"parry":	300,
		"dodge":	300,
		"damage":	300,
		"force":	300,
	"lvl" : 44,
"post_action": (: ke_qz :),
"damage_type" : "����"
	 ]),
([      "action" : "$Nһ��"+(order[random(13)])+"��������Ʈ��"NOR"��$w����ػ�������Բ������$n��$l��ȥ",
		"attack":	300,
		"parry":	300,
		"dodge":	300,
		"damage":	300,
		"force":	300,
	"lvl" : 49,
"post_action": (: ke_qz :),
"damage_type" : "����"
	 ]),
([      "action" : "$Nһ��"+(order[random(13)])+"��С԰�վա�"NOR"������$wѸ����$n��������������",
		"attack":	300,
		"parry":	300,
		"dodge":	300,
		"damage":	300,
		"force":	300,
	"lvl" : 54,
"post_action": (: ke_qz :),
"damage_type" : "����"
	 ]),
([      "action" : "$Nʹ��"+(order[random(13)])+"������ҹ����"NOR"������$w�й�ֱ�룬����$n��$l",
		"attack":	300,
		"parry":	300,
		"dodge":	300,
		"damage":	300,
		"force":	300,
	"lvl" : 59,
"post_action": (: ke_qz :),
"damage_type" : "����"
	 ]),
([      "action" : "$N��������ҵͣ�һ��"+(order[random(13)])+"���������䡹"NOR"��$w�ڿ��л���һ���⻷������$n",
		"attack":	300,
		"parry":	300,
		"dodge":	300,
		"damage":	300,
		"force":	300,
	"lvl" : 64,
"post_action": (: ke_qz :),
"damage_type" : "����"
	 ]),
([      "action" : "$N����$w���¶��Ͼ��������������һ�㣬ȴ��"+(order[random(13)])+"�������ٳء�"NOR"",
		"attack":	400,
		"parry":	400,
		"dodge":	400,
		"damage":	400,
		"force":	400,
	"lvl" : 70,
"post_action": (: ke_qz :),
"damage_type" : "����"
	 ]),
([      "action" : "$N������״��һ��"+(order[random(13)])+"��ľ�����㡹"NOR"������$wֱ��$n��$l",
		"attack":	400,
		"parry":	400,
		"dodge":	400,
		"damage":	400,
		"force":	400,
	"lvl" : 76,
"post_action": (: ke_qz :),
"damage_type" : "����"
	 ]),
([      "action" : "$N���ֽ���һ�죬����$wƽƽ����$n��$l����һ��"+(order[random(13)])+"��˫���Իء�"NOR"",
		"attack":	300,
		"parry":	300,
		"dodge":	300,
		"damage":	300,
		"force":	300,
	"lvl" : 82,
"post_action": (: ke_qz :),
"damage_type" : "����"
	 ]),
([      "action" : "$N����$w�����̣�һ��"+(order[random(13)])+"�����Ƴ��ԡ�"NOR"��ֱָ$n��$l",
		"attack":	300,
		"parry":	300,
		"dodge":	300,
		"damage":	300,
		"force":	300,
	"lvl" : 88,
"post_action": (: ke_qz :),
"damage_type" : "����"
	 ]),
([      "action" : "$Nһ��"+(order[random(13)])+"�������չȡ�"NOR"��$w���������һ�ӣ���$n����˼��ĽǶȹ���",
		"attack":	400,
		"parry":	400,
		"dodge":	400,
		"damage":	400,
		"force":	400,
	"lvl" : 94,
"post_action": (: ke_qz :),
"damage_type" : "����"
	 ]),
([      "action" : "$Nʹ��"+(order[random(13)])+"���軨��·��"NOR"��һʱ����о���$w��Ӱ�ӣ���$n��֪��εֵ�",
		"attack":	400,
		"parry":	400,
		"dodge":	400,
		"damage":	400,
		"force":	400,
	"lvl" : 100,
"post_action": (: ke_qz :),
"damage_type" : "����"
	 ]),
([      "action" : "$Nһ��"+(order[random(13)])+"��İ·��ɣ��"NOR"��$w�������㣬����$n��$l",
		"attack":	400,
		"parry":	400,
		"dodge":	400,
		"damage":	400,
		"force":	400,
	"lvl" : 99,
"post_action": (: ke_qz :),
"damage_type" : "����"
	 ]),
([      "action" : "$NͻȻ�̶�������һ��"+(order[random(13)])+"������������"NOR"��$w���¶��ϴ���$n",
		"attack":	400,
		"parry":	400,
		"dodge":	400,
		"damage":	400,
		"force":	400,
	"lvl" : 106,
"post_action": (: ke_qz :),
"damage_type" : "����"
	 ]),
([      "action" : "$N���Ų�������$wͻȻ���Լ������´̳���ȴ��һ��"+(order[random(13)])+"�����Ľ�����"NOR"",
		"attack":	400,
		"parry":	400,
		"dodge":	400,
		"damage":	400,
		"force":	400,
	"lvl" : 112,
"post_action": (: ke_qz :),
"damage_type" : "����"
	 ]),
([      "action" : "$N������ˮ�滬��һ�㣬һ��"+(order[random(13)])+"��������ҹ��"NOR"��ƽƽ����$n��$l��ȥ",
		"attack":	500,
		"parry":	500,
		"dodge":	500,
		"damage":	500,
		"force":	500,
	"lvl" : 118,
"post_action": (: ke_qz :),
"damage_type" : "����"
	 ]),
([      "action" : "$Nһ��"+(order[random(13)])+"���������"NOR"������$w�̵�$n������",
		"attack":	500,
		"parry":	500,
		"dodge":	500,
		"damage":	500,
		"force":	500,
	"lvl" : 124,
"post_action": (: ke_qz :),
"damage_type" : "����"
	 ]),
([      "action" : "$Nһ��"+(order[random(13)])+"��ĵ�����᡹"NOR"��$w�Ƴ�������Ȧ��ƽƽ����$n��$l��ȥ",
		"attack":	500,
		"parry":	500,
		"dodge":	500,
		"damage":	500,
		"force":	500,
	"lvl" : 131,
"post_action": (: ke_qz :),
"damage_type" : "����"
	 ]),
([      "action" : "$N��������棬������ǰһ�ˣ�һ��"+(order[random(13)])+"����ҩ���项"NOR"��$w��$n��$l��ȥ",
		"attack":	500,
		"parry":	500,
		"dodge":	500,
		"damage":	500,
		"force":	500,
	"lvl" : 138,
"post_action": (: ke_qz :),
"damage_type" : "����"
	 ]),
([      "action" : "$Nһ��"+(order[random(13)])+"����ǰ���ࡹ"NOR"������Ծ������$wɨ��$n��$l",
		"attack":	600,
		"parry":	600,
		"dodge":	600,
		"damage":	600,
		"force":	600,
	"lvl" : 145,
"post_action": (: ke_qz :),
"damage_type" : "����"
	 ]),

([  "action" : "$N������Ȼ֮ɫ������һ��"+(order[random(13)])+"������Բԡ�"NOR"��$w����$n��$l",
		"attack":	600,
		"parry":	600,
		"dodge":	600,
		"damage":	600,
		"force":	600,
	"lvl" : 159,
"post_action": (: ke_qz :),
"damage_type" : "����"
	 ]),
([      "action":"$N����$w���϶��£�һ��"+(order[random(13)])+"����ǰ���¡�"NOR"��$w���������ʻ���չ���У����ػ�����ֻ�ϵ�$n�ۻ����ң��벻֪���н��Ӻδ�����",
		"attack":	200,
		"parry":	200,
		"dodge":	200,
		"damage":	200,
		"force":	200,
	"lvl" :  0,
"skill_name" : "��ǰ����",
"post_action": (: ke_qz :),
"damage_type":  "����"
	 ]),
([      "action":"$N$w΢�ڣ�һ��"+(order[random(13)])+"�����ٰ��"NOR"���������ѣ����˴�Լ���������¼����Ȼ���ҷ緶",
		"attack":	200,
		"parry":	200,
		"dodge":	200,
		"damage":	200,
		"force":	200,
	"lvl" : 9,
"skill_name" : "���ٰ���",
"post_action": (: ke_qz :),
"damage_type":  "����"
	 ]),
([      "action":"$Nһ��"+(order[random(13)])+"��ɨѩ��衹"NOR"��������ţ����ζ���������Ͷ���ƮƮ�г���֮�룬$w���������潣�𣬴���$n$l",
		"attack":	200,
		"parry":	200,
		"dodge":	200,
		"damage":	200,
		"force":	200,
	"lvl" : 15,
"skill_name" : "ɨѩ���",
"post_action": (: ke_qz :),
"damage_type":  "����"
	 ]),
([      "action": "$Nһ��"+(order[random(13)])+"������С�á�"NOR"������$w������������ָ�����������ƣ�������������$n$l������֮�֣�������˼",
		"attack":	200,
		"parry":	200,
		"dodge":	200,
		"damage":	200,
		"force":	200,
	"lvl" : 25,
"skill_name" : "����С��",
"post_action": (: ke_qz :),
"damage_type":  "����"
	 ]),
([      "action":"$N�Ų�΢��������̤������������һ��"+(order[random(13)])+"�����¶��ġ�"NOR"������Ѹ�ݣ��鶯��ã������������������ҷ������ף���ʽ���",
		"attack":	200,
		"parry":	200,
		"dodge":	200,
		"damage":	200,
		"force":	200,
	"lvl" : 33,
"skill_name" : "���¶���",
"post_action": (: ke_qz :),
"damage_type":  "����"
	 ]),
([      "action":"$N����΢�ڣ�һ��"+(order[random(13)])+"���رߵ��ס�"NOR"��$w����$n$l����һ��ȥ�ƿ����ǳ۵��������ҷ��˴�Լ��Ʈ���ޱ�",
		"attack":	300,
		"parry":	300,
		"dodge":	300,
		"damage":	300,
		"force":	300,
	"lvl" : 35,
"skill_name" : "�رߵ���",
"post_action": (: ke_qz :),
"damage_type":  "����"
	 ]),
([      "action":"$N$w���Ʈ���������̬ƮƮ���ɣ�������$n��$l�������㣬ȴ��һ��"+(order[random(13)])+"��С԰�վա�"NOR"",
		"attack":	300,
		"parry":	300,
		"dodge":	300,
		"damage":	300,
		"force":	300,
	"lvl" : 45,
"skill_name" : "С԰�վ�",
"post_action": (: ke_qz :),
"damage_type":  "����"
	 ]),
([      "action":"$N�������ܣ�һʽ"+(order[random(13)])+"������ҹ����"NOR"����̨�γ�����·��Խ��Խ��������ȴ�ް�������$wʹ�þ���Ѹ������ȥ����",
		"attack":	300,
		"parry":	300,
		"dodge":	300,
		"damage":	300,
		"force":	300,
	"lvl" : 55,
"skill_name" : "����ҹ��",
"post_action": (: ke_qz :),
"damage_type":  "����"
	 ]),
([      "action":"$N$w����������ʮ������⣬����һ��"+(order[random(13)])+"�����¿��ˡ�"NOR"��ת˲�佣���ѽ�$n�ϰ���������",
		"attack":	400,
		"parry":	400,
		"dodge":	400,
		"damage":	400,
		"force":	400,
	"lvl" : 60,
"skill_name" : "���¿���",
"post_action": (: ke_qz :),
"damage_type":  "����"
	 ]),
([      "action":"$N����һ����һʽ"+(order[random(13)])+"���ʱʻ�ü��"NOR"��$w΢΢�������ὣб��$n$l�������������ɰ���",
		"attack":	400,
		"parry":	400,
		"dodge":	400,
		"damage":	400,
		"force":	400,
	"lvl" : 70,
"skill_name" : "�ʱʻ�ü",
"post_action": (: ke_qz :),
"damage_type":  "����"
	 ]),
([      "action":"$N��ƮƮ���������ˣ�һ��"+(order[random(13)])+"�����İ�ͨ��"NOR"��$w���ط�ת���̣���������ʮ���¼��죬�������ø��ֵķ�����ָҲ����˼���",
		"attack":	500,
		"parry":	500,
		"dodge":	500,
		"damage":	500,
		"force":	500,
	"lvl" : 75,
"skill_name" : "���İ�ͨ",
"post_action": (: ke_qz :),
"damage_type":  "����"
	 ]),
([      "action":"$Nһ��$w����ʱ����������$w�������߰��������ߣ�һ��"+(order[random(13)])+"���������"NOR"��$n�����������ǰ�ӹ����Ѿ�$l��һ��",
		"attack":	600,
		"parry":	600,
		"dodge":	600,
		"damage":	600,
		"force":	600,
	"lvl" : 80,
"skill_name" : "�������",
"post_action": (: ke_qz :),
"damage_type":  "����"
	 ]),
});


int valid_enable(string usage)
{
	return (usage == "sword") || (usage == "parry")
	       ;
}

int valid_learn(object me)
{
//		if (!wizardp(me))
//		return notify_fail("��ʦͻȻ�Ӻڰ��г��˳�����������һ����������û���š�\n");	
	      if ( me->query("gender") != "Ů��" )
         return notify_fail("���ֲ�����Ů����ô����������̫�ؽ�����\n");
	if ((int)me->query_skill("taisu-force", 1) < 300 )	
		return notify_fail("���̫���ľ���򲻵����޷�ѧϰ̫�ؽ�����\n");
    if (me->query("family/family_name")!="��Ĺ��")
   return notify_fail("�㲻�ǹ�Ĺ�ɵ��ӣ��޷�ѧϰ̫�ؽ�����\n");		
	if ((int)me->query_skill("taisu-dodge", 1) < 300)
		return notify_fail("���̫�����粽���̫ǳ��\n");
	if ((int)me->query_skill("taisu-moon", 1) < 300)
		return notify_fail("���̫������ʽ���̫ǳ��\n");
	if ((int)me->query("int", 1) < 30)
		return notify_fail("̫�ؽ����˹�Ĺ�ɸ������û���㹻���Կ�����������\n");
	if (random(100)==1) me->add("score",-5);		
	return 1;
}

mapping query_action(object me, object weapon)
{
	int level;
	level = (int) me->query_skill("taisu-jian",1);

	
	
		if (random(level) > 300 && me->query("jiali") > 100 && me->query_temp("powerup") && random(15)==1 )
		{
			return ([      "action":HIG"$N�������飬�ж����������಻��������������������������ɣ����н��������ӵ�ȹ�����̬֮��"NOR,
			"attack":	600,
			"parry":	600,
			"dodge":	600,
			"damage":	600,
			"force":	600,
			"lvl" : 175,
               "post_action": (: ke_qz :),
               "damage_type":  "����"
			        ]);
		}
		if (random(level) > 300 && me->query("jiali") > 100 && me->query_temp("powerup") && random(15)==2 )
		{
			return ([      "action":HIY"$N�������ߣ�$w"+HIY"��һ��δ�ϣ������������г���ʱ�������󣬽��еֵ�ʱ����ת�ң����ƽ��ǽ��������ˣ������ⲻ������$n��֮������Ȼ��"NOR,
			"attack":	600,
			"parry":	600,
			"dodge":	600,
			"damage":	600,
			"force":	600,
			"lvl" : 175,
               "post_action": (: ke_qz :),
               "damage_type":  "����"
			        ]);
		}
	if (random(level) > 300 && me->query("jiali") > 100 && random(15)==3 )
	{
		return ([      "action":HIW"$N���˼�������������������$w"+HIW"Ʈ����ȥ��������������һ·̫�ؽ�������ʹ��Ӣ��ˬ�ʣ��������ˣ�"NOR,
		"attack":	500,
		"parry":	500,
		"dodge":	500,
		"damage":	500,
		"force":	500,
               "post_action": (: ke_qz :),
               "damage_type":  "����"
		        ]);
	}
	return action[random(sizeof(action))];
}

int practice_skill(object me)
{
	object weapon;
//	if (!wizardp(me))
//		return notify_fail("��ʦͻȻ�Ӻڰ��г��˳�����������һ����������û���š�\n");	
	if (!objectp(weapon = me->query_temp("weapon"))
	        || (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");
	if ((int)me->query("qi") < 45)
		return notify_fail("�������������̫�ؽ�����\n");
	if ((int)me->query("neili") < 15)
		return notify_fail("���������������̫�ؽ�����\n");
    if (me->query("family/family_name")!="��Ĺ��")
   return notify_fail("�㲻�ǹ�Ĺ�ɵ��ӣ��޷���ϰ̫�ؽ�����\n");	
	      if ( me->query("gender") != "Ů��" )
         return notify_fail("���ֲ�����Ů����ô����������̫�ؽ�����\n");
	me->receive_damage("qi", 26);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"taisu-jian/" + action;
}
int ke_qz(object me, object victim, object weapon, int damage)
{
	string str;
	int skill;
	object weapon2;
	weapon2 = victim->query_temp("weapon");
	skill = me->query_skill("taisu-jian",1);

	if(skill > 80 )
	{
		if (damage==RESULT_DODGE
		        && victim->query_skill_mapped("dodge") == "jinyan-gong"
		        && (random(skill)/2 + skill/2) > random(victim->query_skill("jinyan-gong",1))
		        && random(3)==0
		        && me->query_skill("taisu-force",1) > 50)
		{

			message_vision(HIW"��֪$N��Ϥ���㹦����������������Ź�������������$n����֮������ϵ�˿˿��ۣ�$n��$Pһ������������ˤ����\n"NOR, me,victim );
			if (!victim->is_busy()) victim->start_busy(3);
			if (victim->query("qi") > skill*2)
				victim->receive_damage("qi", random(skill)+skill);
			str = COMBAT_D->status_msg((int)victim->query("qi") * 100 /(int)victim->query("max_qi"));
			message_vision("( $N"+str+")\n", victim);
		}
		else if (damage==RESULT_PARRY
		         && ( objectp(weapon2 = victim->query_temp("weapon"))
		              && victim->query_skill_mapped("sword") == "quanzhen-jianfa" &&(string)weapon2->query("skill_type") == "sword")
		         && (random(skill)/2 + skill/2) > random(victim->query_skill("parry",1))
		         && random(2)==0
		         && me->query_skill("taisu-force",1) > 50)
		{

			message_vision(HIW"$nͻ���Լ�����"+weapon2->name()+HIW"��ͦ���죬����$N����"+weapon->name()+HIW"��˹�ȥ��һ��֮�£����������ضᡣ\n"NOR, me,victim );
			message_vision(HIW"˫�����ᣬֻ΢һ���֣�$NͻȻ�ſ�"+weapon->name()+HIW"��˫��ֱ�ۣ��ͻ�$nǰ�أ�ͬʱ"+weapon->name()+HIW"��������������˫��һ������·����������֮����\n"NOR, me,victim );
			if (random(me->query("bodyreset")) > random(victim->query("bodyreset")))
			{
				message_vision(HIW"$nֻ������"+weapon2->name()+HIW"�����ֺ��أ�����һ�У�\n"NOR, me,victim );
				weapon2->unequip();
				weapon2->move(environment(me));
			}
			weapon->unequip();
			me->add_temp("apply/attack", skill/4);
			me->add_temp("apply/damage", skill);
			COMBAT_D->do_attack(me, victim, me->query_temp("weapon"));
			me->add_temp("apply/attack", -skill/4);
			me->add_temp("apply/damage", -skill);
			weapon->wield();
			message_vision("\n$N��Ӧ��ݣ����ѳ���"+weapon->name()+"�������У�\n", me,victim );
			me->add("neili", -(me->query("jiali") +100) );
		}//��ĹΪȫ������ ����ȫ��
		else if (damage==RESULT_PARRY
		         && ( !objectp(weapon2 = victim->query_temp("weapon"))
		              && ((victim->query_skill_mapped("parry") == "quanzhen-jianfa" )
		                  || (victim->query_skill_mapped("force")== "xiantian-gong")
		                  || (victim->query_skill_mapped("dodge")== "jinyan-gong")
		                  || (victim->query_skill_mapped("sword")== "quanzhen-jianfa"))
		              && (random(skill)/2 + skill/2) > random(victim->query_skill("parry",1)) )
		         && random(2)==0
		         && me->query_skill("taisu-force",1) > 50)
		{

			message_vision(HIW"����$N�漴ͦ��һ�̣��ؽ��ȿ���׼��ֱ��$n���ƣ�����ȫ���书����������֮����$n���´󾪣���æ���֣��������ƣ�$N����������\n"NOR, me,victim );
			me->add_temp("apply/attack", skill/4);
			me->add_temp("apply/damage", skill);
			COMBAT_D->do_attack(me, victim, me->query_temp("weapon"));
			me->add_temp("apply/attack", -skill/4);
			me->add_temp("apply/damage", -skill);
			me->add("neili", -(me->query("jiali") +100) );
		}
	}
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	int level,damage2,ap,dp,sp;
	level  = (int) me->query_skill("taisu-jian",1);
	damage2 = (int)me->query_skill("taisu-jian",1);	
	ap = me->query("bodyreset");
	dp = victim->query("bodyreset");
	sp = victim->query_skill("parry",1);
    if( damage_bonus < 100 ) return 0;
	if ( me->query_skill("taisu-force",1) < 100 && me->query_skill("taisu-force",1) < 100)	 return 0;
	if ( me->query("jiali") < 1 || me->query("neili") < 100 || (me->query_skill_mapped("force") != "taisu-force" && me->query_skill_mapped("force") == "taisu-force")) return 0;	
	if (damage2<10) damage2=10;	

	if( random(ap) > dp/10
	    && level > 200
	    && random(8) == 0	)
	{
//		if (!victim->is_busy()) victim->start_busy(1+random(1));
		if (victim->query("neili") > 200) victim->add("neili",-200);

		if (victim->query("qi") > level*2)
		{
			victim->receive_wound("qi", damage2+damage_bonus/2,me);
			victim->receive_damage("qi", damage2+damage_bonus/2,me);
			me->add("neili", -100 );
		}
		return HIR"$nͻȻ˫Ŀֱ�ɣ����һ��������ˤ�����������˼��صİ��ˣ�\n"NOR;
	}

	if( random(level) > sp/10
		&& level > 200
	    && random(8)==2	)
	{
//		if (!victim->is_busy()) victim->start_busy(1+random(1));
		if (victim->query("neili") > 200) victim->add("neili",-200);
		if (victim->query("qi") > level*2)
		{
			victim->receive_wound("qi", damage2+damage_bonus,me);
			victim->receive_damage("qi", damage2+damage_bonus,me);
			me->add("neili", -100 );
		}
		return HIR"$nͻȻ������Ѫ�����һ��������ˤ�����������˼��صİ��ˣ�\n"NOR;
	}
}
int ob_hit(object ob, object me, int damage)
{
	string msg;
	int j,ap,dp,damage2;
	ap = (int) me->query_skill("taisu-jian",1);
	dp = (int) ob->query_skill("parry",1);
	damage2= (int) ob->query("neili",1)/10;
	if (damage <10)  damage=10; 	
		if (damage2> 5000)	damage2=5000;
		if (damage2 < 0 ) damage2=0;
	if (random(6)==4 && random(ap)>dp/10 && me->query("neili") > 100 && (me->query_skill_mapped("force") == "taisu-force" || me->query_skill_mapped("force") == "taisu-force"))
	{
		j = -(damage+random(damage));  

		msg = HIC"$N"+HIC+"�������ߣ��ж����������಻����һ��δ�ϣ������� !$n˫��һ����֪���룡\n" +NOR;
		if (random(2)==0)
		{
			msg += HIY"$N"+HIY+"Ŀ��һ����һ��������ӳ� !$n һ�����ģ����������˼�ö��\n" +NOR;
			ob->apply_condition("yf_poison",20);
		}
		message_vision(msg, me, ob);
		if (!ob->is_busy()) ob->start_busy(2);
		me->add("neili", -100 );
		return j;
	}	
}

int diffcult_level() { return 300; }