
inherit ROOM;

void create()
{
	set("short", "洞内");
	set("long", @LONG
洞里黑暗潮湿，在北面有一丝阳光照进来。它给了你一线
希望。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "north" : "/u/taoguan/hole4",
  "south" : "/u/taoguan/hole",
]));
	setup();
        replace_program(ROOM);
}
