inherit "/clone/vip/book/force100-book";

void create()
{
    ::create();
    set("no_sell",1);
    set("no_give",1);
    set("no_drop",1);
    set("bind_obj",1);
    set("name",this_object()->query("name") + "[��]");
}
