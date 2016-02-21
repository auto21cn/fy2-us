
inherit ROOM;

void create()
{
	set("short", "上山路");
	set("long", @LONG
弯弯曲曲的泥土路，却很平坦。左右两边都是茂盛的松林，雨过
天晴时，泥土的香气和松树的芬芳混在一起，能使人心胸开朗，忘记
一切烦恼。不远的前方，有一块巨石和一个小亭子。
LONG
	);
	set("exits", ([
		"northdown" : __DIR__"road1",
		"southup" : __DIR__"rock",
		"west" : __DIR__"pine1",
		"east" : __DIR__"pine3",
	]));
	set("outdoors", "wudang");
	setup();
	replace_program(ROOM);
}
