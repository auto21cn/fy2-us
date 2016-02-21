// Room: /d/chuenyu/dustyroad2.c

inherit ROOM;

void create()
{
        set("short", "三叉路口");
        set("long", @LONG
向北是通入山里的小路。东北方向是一个小小的住家，
住家的后面是一个很大的花园。花园里有很多小童在嬉耍。
向南是通往小镇的方向。
LONG
        );
        set("exits", ([ /* sizeof() == 3 */
  "northeast" : __DIR__"dustyroad3",
  "south" : __DIR__"dustyroad",
  "north" : __DIR__"sunnyroad",
]));
        set("outdoors", "chuenyu");

        setup();
        replace_program(ROOM);
}

