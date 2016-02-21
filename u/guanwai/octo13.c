
inherit ROOM;

void create()
{
	object box, matter;
        set("short", "八角街");
        set("long", @LONG
城市赤如皮革，有光滑美丽的一面，也有粗糙丑陋的一面。这段八角街
上垃圾粪便狼藉。成群结队的年老乞丐，穿着破旧褴褛的衣服，剃光头打赤
足，匍匐在尘土中，等待着行人香客的施舍。
LONG
        );
        set("exits", ([ 
  "east" : __DIR__"octo14",
  "west" : __DIR__"octo12",
]));
        set("outdoors", "guanwai");
        set("objects", ([
                __DIR__"obj/trash" : 1,
		__DIR__"obj/junkblade" : 2,
        ]) );
        setup();


}

