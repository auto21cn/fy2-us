inherit ROOM;
// Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.

void create()
{
        set("short", "梅林小路");
        set("long", @LONG
一条踏出的小路盘旋曲折。路边的梅树下一朵朵无名小花份外妖窈。
花有兰有紫，有些还有浇灌过的痕迹。繁密的梅枝间透下点点日光，
枝条摇摆，忽明忽暗。
LONG
        );
        set("exits", ([ /* sizeof() == 4 */
  "west" : "/d/manglin/edge3",
  "east" : __DIR__"road2",
]));
        set("outdoors", "wanmei");
        set("item_desc", ([
                "无名小花": "
                        路边的野花好美呀．．．采（ｐｉｃｋ）一朵吧！\n",
                "小花": "
                        路边的野花好美呀．．．采（ｐｉｃｋ）一朵吧！\n"

        ]) );
        setup();
}
void init()
{
add_action("do_pick","pick");
}

int do_pick()
{
	object flower;
message_vision("$N弯下腰，采了一朵路边的野花。\n",this_player());
	flower = new(__DIR__"obj/flower");
	flower->move(this_player());
return 1;
}
