
inherit ROOM;

void create()
{
	set("short", "����ɽ");
	set("long", @LONG
������ǰ��һ����ͨ��ɽ�塣һ������ܿ�Ҳ����ܶ���ɽ��
�ӱ������������š��������ɽʯд�ţ�����ɽ���������֡�
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "northup" : "/u/taoguan/road2",
  "eastdown" : "/u/taoguan/sroad",
]));
	set("outdoors", "taoguan");
	setup();
	replace_program(ROOM);
}