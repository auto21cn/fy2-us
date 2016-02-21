
inherit ROOM;

void create()
{
	set("short", "上山路");
	set("long", @LONG
弯弯曲曲的泥土路，却很平坦。左右两边都是茂盛的松林，雨过
天晴时，泥土的香气和松树的芬芳混在一起，能使人心胸开朗，忘记
一切烦恼。在这里，从松林的缝隙间可见到武当观的红色围墙。
LONG
	);
	set("exits", ([ 
		"northdown" : __DIR__"rock",
		"southup" : __DIR__"wudang",
	]));
	set("outdoors", "wudang");
	setup();
	replace_program(ROOM);
}
