
inherit ROOM;

void create()
{
	set("short", "小路");
	set("long", @LONG
这是一条弯曲的泥土路。路边杂草丛生，路上泥泞不堪。再往前走
就进入了一片原始森林，从没人走出过那里。
LONG
	);
	set("exits", ([
                "north" : "/u/guanwai/citygate",
                "south" : __DIR__"lroad2",
	]));
	setup();
replace_program(ROOM);

}
