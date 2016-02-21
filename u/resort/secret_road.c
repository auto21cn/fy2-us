
inherit ROOM;

void create()
{
        set("short", "密道");
        set("long", @LONG
道边高达丈许的灌木丛形成了天然的屏障，再加上地势渐低，
无人可以猜到此路倒底通向何方。前面居然出现了一个山洞。
LONG
        );
        set("exits", ([ 
  "east" : __DIR__"smallroad4",
  "west" : __DIR__"cave_tunnel",
]));
        set("outdoors", "resort");

        setup();
        replace_program(ROOM);
}

