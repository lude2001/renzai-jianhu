inherit ITEM;
void create()
{
        set_name("�̲�", ({ "grass" , "�̲�"}) );
        set_weight(500);
       // set_max_encumbrance(8000);
        set("no_sun", 1);
        set("no_shown", 1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "�������ε��̲ݣ��ƺ����м���¶����Ҷ��������΢�⣬���������\n�ݴ����ǲ�����ʲô�����������棨������裩��\n");
                set("value", 1);
        }
        setup();
}
int is_container() { return 1; }