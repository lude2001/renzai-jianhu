inherit ROOM;
void create()
{
        set("short", "深潭边");
        set("long", @LONG
来到这里，豁然开朗。一条银色的瀑布奔流而下，砸在岩石上，溅起
一阵阵水花。由于地势的原因，这个深潭的水流依然很急。当年卫悲回就
是掉进这龙门急流中。至今下落不名，想必死在这里了。
LONG );
        set("valid_startroom",1);
        set("outdoors","龙门");
        set("class","合欢宗");
        set("exits", ([
                "east"  : __DIR__"hsxj2",
        ]));
        set("action_list", ([
		"跳入急流" : "tiao tan",
		]));
        setup();
}

void init()
{
        add_action("do_jump","tiao");
}

int do_jump(string arg)
{
          object ob;
          object me;
          object *obb;
          int i;

          me=this_player();
          if (!arg || arg!="tan")
                return notify_fail("你要跳到哪里去？\n");
          message_vision("只见$N力贯全身，朝着深潭跳了进去！\n",me);
          if (ob=present("xuehe che",environment(me)) && me->query_temp("xueheche"))
          {
                obb=all_inventory(environment(me));
                for(i=0; i<sizeof(obb); i++) {
                if (obb[i]->query("id")=="xuehe che") 
                        destruct(obb[i]);
                }

                me->set_temp("chong",1);
          }
          me->move(__DIR__"jiliu");
          return 1;
}


