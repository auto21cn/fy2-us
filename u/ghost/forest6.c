
inherit ROOM;

void create()
{
	set("short", "ԭʼ����");
	set("long", @LONG
������һƬ�ڰ����ڰ��г����˸�ʽ������Σ�գ�ÿһ�ֶ�����
�����������ڴ�������ʧ�˷��򣬼��ʾ�����������
LONG
	);
	set("exits", ([
		"north" : __DIR__"forest5",
		"south" : __DIR__"forest1",
		"east" : __DIR__"forest6",
		"west" : __DIR__"forest7",
	]));
	set("outdoors", "ghost");
	setup();
	replace_program(ROOM);
}