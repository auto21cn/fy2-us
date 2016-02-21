
inherit ROOM;

void create()
{
	set("short", "山坳");
	set("long", @LONG
这里是一处山坳，往南就是风云城，一条蜿蜒的小径往北展开．
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "westup" : "/u/taoguan/road1",
  "eastdown" : "/d/laowu/road1",
]));
	set("outdoors", "taoguan");
	setup();
	replace_program(ROOM);
}
