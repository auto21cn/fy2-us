
inherit ROOM;

void create()
{
	set("short", "石英岩石阶");
	set("long", @LONG
你正走在一道长长的石英岩阶梯上, 阶梯的两侧种植著一排高耸
的松树。抬头望望东北边那座高耸挺拔的山峰, 在云雾飘渺的山顶上
矗立著一座雄伟的白色楼阁。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "northup" : "/u/taoguan/road4",
  "southdown" : "/u/taoguan/road2",
]));
	set("outdoors", "taoguan");
	setup();
	replace_program(ROOM);
}
