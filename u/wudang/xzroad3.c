
inherit ROOM;

void create()
{
	set("short", "�ֵ�");
	set("long", @LONG
����ʯ���̳ɵĵ�·����ɨ�ø�Ǭ����������Сͯ�ڽֵ��ϻ���
׷����ˣ���ֵ������Ǻ�ש���ɵķ��ݣ���λ�������е����ڼ���ǰ
�������졣
LONG
	);
	set("exits", ([ 
		"north" : __DIR__"xzroad2",
		"south" : __DIR__"road1",
		"west" : __DIR__"xzhouse2",
		"east" : __DIR__"xzstore2",
	]));
	set("outdoors", "wudang");
	setup();
	replace_program(ROOM);
}