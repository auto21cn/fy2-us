
inherit ROOM;

void create()
{
	set("short", "原始丛林");
	set("long", @LONG
丛林中一片黑暗，黑暗中充满了各式各样的危险，每一种都可以
至命。若是在丛林中迷失了方向，饥渴就足以至命。
LONG
	);
	set("exits", ([
		"north" : __DIR__"forest7",
		"south" : __DIR__"forest5",
		"east" : __DIR__"forest",
		"west" : __DIR__"forest6",
	]));
	set("outdoors", "ghost");
	setup();
	replace_program(ROOM);
}
