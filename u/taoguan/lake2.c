
inherit ROOM;

void create()
{
	set("short", "三清湖");
	set("long", @LONG
湖水清澈透明，不时可以看到几尾鱼跳上水面。湖水尽头
是一个大瀑布。在这里可以听到瀑布从山上直冲而下，发出的
轰轰雷声。湖边稀稀落落地站着几个道人。
LONG
	);
	set("exits", ([ /* sizeof() == 3 */
  		"west" : "/u/taoguan/grassland2",
  		"south" : "/u/taoguan/lake1",
]));
        set("objects", ([ /* sizeof() == 2 */
  		"/u/taoguan/npc/reg_taoist" : 3,
]));
        set("resource/water",1);
	set("outdoors", "taoguan");
	setup();
}

void init()
{
        add_action("do_fillwater", "fillwater");
        add_action("do_swim", "swim");
}

int do_swim(string arg)
{
   return 1;
}

int do_fillwater(string arg)
{
        object *list, ob;
        int i, can_fillwater;
        string dir;

        if( !arg || arg=="" ) return 0;

        if( arg=="skin" || arg=="wineskin" ) {
                list = all_inventory(this_player());
                i = sizeof(list);
                can_fillwater = 0;
                while (i--) {
                  if (((string)list[i]->query("liquid/type") == "alcohol")
 || ((string)list[i]->query("liquid/type") == "water")         ) {
                        ob = list[i];
                        can_fillwater = 1;
                        ob->set("liquid", ([
                                "type": "water",
                                "name": "清水",
                                "remaining": 30,
                                "drunk_apply": 6,
                        ]) );
                        write("你从湖里装满了清水! \n");
                        return 1;
                   }
                }
                if (can_fillwater ==0) {
                        write("你没有装水的东西啊....\n");
                        return 1;
                }
        }
        else {
                write("你要往什么东西里灌水？");
        }
        return 1;
}
