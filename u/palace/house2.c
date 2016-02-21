
inherit ROOM;

void create()
{
        set("short", "楼殿前");
        set("long", @LONG
楼殿前是一片阴郁的松林，风过松林，声如悲鸣！松林间几只小松
鼠不停地追逐跳跃，给阴郁的林间带来些生气。穿过雕花栏杆，只见长廊曲
折，通向一扇边门。往西是一条石路。
LONG
        );
        set("exits", ([ 
  "south" : __DIR__"huding",
  "north" : __DIR__"house",
]));
        set("objects", ([
        __DIR__"npc/huafei" : 1,
                        ]) );

        set("outdoors", "palace");

        setup();
        replace_program(ROOM);
}

