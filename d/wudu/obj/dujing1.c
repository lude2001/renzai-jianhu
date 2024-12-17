#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(NOR + CYN "��������ƪ��" NOR, ({ "du jing1", "jing1", "book1" }));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", CYN "����һ��������С�ᣬ�������������д���˸����ö�\n"
                            "�Ļ��������Ͷ�ҩ���䷽��������ö�(read jing1)һ����\n" NOR);
                set("value", 100);
                set("no_sell", "�ҡ��ҵ��졭���嶾�̵Ķ����㶼����������");
                set("material", "silk");
                set("skill", ([
                        "name"         : "poison",
                        "exp_required" : 500,
                        "jing_cost"    : 20,
                        "difficulty"   : 20,
                        "max_skill"    : 49,
                ]));
        }
}

void init()
{
        add_action("do_read", "read");
}

int do_read(string arg)
{
        if (arg == "jing1" || arg == "book1")
                return notify_fail(NOR + CYN "\n"
"                                  \n"
"         ��       ��              \n"
"                                  \n"
" ��Ы�ۣ��ϳ��ݡ������ӡ�����     \n"
" ��ȸ�������ǲݡ�ǧ��������     \n"
" �׶��죺�����ӡ�ǧ��������     \n"
" �ϳ�ɢ���ϳ��ݡ�������������     \n"
" ����ࣺ���ǲݡ�������������     \n"
"                        \n"
"     ��   ҩ   ��   �� \n"
"\n"
" ��ʥɢ����ȡ�ϳ�ɢ�������\n"
" �׶��졢��ȸ������Ы�۸�һ\n"
" �ݣ���ӽ��߶�Һ���ƣ�����\n"
" ���ɶ��ɡ��罫��ҩ�䷨��й\n"
" �ߵ�ɱ���⡣\n"
"\n\n" NOR);
}
