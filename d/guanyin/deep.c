// Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.
inherit ROOM;
void create()
{
        set("short", "石峰深处");
        set("long", @LONG
这些石峰，半由天生，半由人力，其中道路盘旋，竟隐含生克变化
之理，正如诸葛武侯的八阵图一般，除了尽人力之极致外，还加以天道
之威，当真是鬼斧神功，人所难测。
LONG
        );
        set("exits", ([ /* sizeof() == 4 */
  "southeast" : __DIR__"road3",
  "south" : __DIR__"road4",
  "west" : __DIR__"narrow",
]));

        set("outdoors", "fengyun");
        setup();
        replace_program(ROOM);
}
