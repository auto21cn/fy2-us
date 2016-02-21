inherit ROOM;

void create()
{
        set("short", "襄阳广场");
        set("long", @LONG
这里是襄阳城的中心广场.
进入石洞，只见佳木茏葱，奇花烂熳，一带清流，从花木深处
泻于石隙之下。俯而视之，但见清溪泻玉，石笋穿云，白石为栏，
环抱池沼，石桥三港，兽面吞吐。
LONG
        );
        set("exits", ([
  "westdown" : __DIR__"palace_palace",
]));
        set("objects", ([
               __DIR__"npc/liling" : 1,
       ]) );
        set("valid_startroom", 1);
        setup();
        replace_program(ROOM);
}
